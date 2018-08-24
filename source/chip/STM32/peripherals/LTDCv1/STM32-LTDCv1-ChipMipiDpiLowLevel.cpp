/**
 * \file
 * \brief ChipMipiDpiLowLevel class implementation for LTDCv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipMipiDpiLowLevel.hpp"

#include "distortos/chip/CMSIS-proxy.h"

#include "distortos/devices/MipiDpi/MipiDpiBase.hpp"

#include "distortos/InterruptMaskingLock.hpp"

#include <cerrno>

namespace distortos
{

namespace chip
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// Background Color BLACK value for BCCR register
constexpr uint32_t bccBackgroundBlack {0x000000};

/// Alpha MAX = 1.0 for CACR layer register
constexpr uint8_t alphaMax {0xff};

/// Blend Factor 1 - Pixel Alpha x Constant Alpha value for BFCR layer register
constexpr uint16_t bf1PixelAlphaXConstantAlpha {0x600};

/// Blend Factor 2 - 1 - Pixel Alpha x Constant Alpha value for BFCR layer register
constexpr uint16_t bf2PixelAlphaXConstantAlpha {0x007};

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Decode value of LTDC_ISR register to devices::MipiDpiBase::ErrorSet
 *
 * \param [in] isr is the value of LTDC_ISR register that will be decoded
 *
 * \return devices::MipiDpiBase::ErrorSet with errors decoded from \a isr
 */

devices::MipiDpiBase::ErrorSet decodeErrors(const uint32_t isr)
{
	devices::MipiDpiBase::ErrorSet errorSet {};
	errorSet[devices::MipiDpiBase::fifoUnderrun] = (isr & LTDC_ISR_FUIF) != 0;
	errorSet[devices::MipiDpiBase::busError] = (isr & LTDC_ISR_TERRIF) != 0;
	return errorSet;
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| public types
+---------------------------------------------------------------------------------------------------------------------*/

/// parameters for construction of MIPI DPI low-level drivers
class ChipMipiDpiLowLevel::Parameters
{
public:

	/**
	 * \brief Enables or disables peripheral clock in RCC.
	 *
	 * \param [in] enable selects whether the clock will be enabled (true) or disabled (false)
	 */

	void enablePeripheralClock(const bool enable) const
	{
		auto& rccEn = *reinterpret_cast<volatile uint32_t*>(RCC_BASE + offsetof(RCC_TypeDef, APB2ENR));
		const InterruptMaskingLock interruptMaskingLock;
		rccEn = (rccEn & ~RCC_APB2ENR_LTDCEN) | (enable == true ? RCC_APB2ENR_LTDCEN : 0);
	}

	/**
	 * \brief Resets all peripheral's registers via RCC
	 *
	 * \note Peripheral clock must be enabled in RCC for this operation to work.
	 */

	void resetPeripheral() const
	{
		auto& rccRst = *reinterpret_cast<volatile uint32_t*>(RCC_BASE + offsetof(RCC_TypeDef, APB2RSTR));
		const InterruptMaskingLock interruptMaskingLock;
		rccRst |= RCC_APB2RSTR_LTDCRST;
		rccRst &= ~RCC_APB2RSTR_LTDCRST;
	}

	/**
	 * \return reference to LTDC_TypeDef object
	 */

	LTDC_TypeDef& getLtdc() const
	{
		return *reinterpret_cast<LTDC_TypeDef*>(LTDC_BASE);
	}

	/**
	 * \return reference to primary layer LTDC_Layer_TypeDef object
	 */

	LTDC_Layer_TypeDef& getPrimaryLayer() const
	{
		return *reinterpret_cast<LTDC_Layer_TypeDef*>(LTDC_Layer1_BASE);
	}

	/**
	 * \return reference to secondary layer LTDC_Layer_TypeDef object
	 */

	LTDC_Layer_TypeDef& getSecondaryLayer() const
	{
		return *reinterpret_cast<LTDC_Layer_TypeDef*>(LTDC_Layer2_BASE);
	}
};

/*---------------------------------------------------------------------------------------------------------------------+
| public static objects
+---------------------------------------------------------------------------------------------------------------------*/
const ChipMipiDpiLowLevel::Parameters ChipMipiDpiLowLevel::parameters_;

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

ChipMipiDpiLowLevel::~ChipMipiDpiLowLevel()
{
	if (isStarted() == false)
		return;

	parameters_.resetPeripheral();
	parameters_.enablePeripheralClock(false);
}

void ChipMipiDpiLowLevel::interruptHandler()
{
	auto& ltdc = parameters_.getLtdc();

	if (ltdc.ISR & LTDC_ISR_LIF)
	{
		ltdc.ICR = LTDC_ICR_CLIF;
		mipiDpiBase_->VSyncEvent();
	}

	uint32_t isrErrorFlags = ltdc.ISR & (LTDC_ISR_FUIF | LTDC_ISR_TERRIF);
	if (isrErrorFlags != 0)
	{
		ltdc.ICR = isrErrorFlags;	// clear served error flags
		mipiDpiBase_->errorEvent(decodeErrors(isrErrorFlags));
	}
}

int ChipMipiDpiLowLevel::update(const devices::Plane& plane)
{
	if (isStarted() == false)
		return EBADF;

	const auto type = plane.getType();
	if (type != devices::Plane::Type::primary && type != devices::Plane::Type::overlay)
		return EINVAL;

	const auto framebuffer = plane.getFramebuffer();
	const auto coordinates = plane.getCoordinatesOnDisplay();
	auto x0 = coordinates.first;
	auto x1 = coordinates.first + framebuffer.getXsize() - 1;
	auto y0 = coordinates.second;
	auto y1 = coordinates.second + framebuffer.getYsize() - 1;

	// partial display disabled
	if (x0 < 0 || y0 < 0)
		return EINVAL;

	decltype(parameters_.getPrimaryLayer()) layer = (type == devices::Plane::Type::primary) ?
			parameters_.getPrimaryLayer() : parameters_.getSecondaryLayer();

	auto ltdc = parameters_.getLtdc();

	const auto bpcr = ltdc.BPCR;
	const auto ahbp = (bpcr & LTDC_BPCR_AHBP) >> 16;
	const auto avbp = bpcr & LTDC_BPCR_AVBP;

	const auto awcr = ltdc.AWCR;
	decltype(x1) maxX1 = ((awcr & LTDC_AWCR_AAW) >> 16) - ahbp - 1;
	decltype(y1) maxY1 = (awcr & LTDC_AWCR_AAH) - avbp - 1;

	// partial display disabled
	if (x1 > maxX1 || y1 > maxY1)
		return EINVAL;

	uint32_t val = ((x1 + 1 + ahbp) << 16) + (x0 + 1 + ahbp);
	layer.WHPCR = val;

	val = ((y1 + 1 + avbp) << 16) + (y0 + 1 + avbp);
	layer.WVPCR = val;

	const auto pixelFormat = framebuffer.getPixelFormat();
	const auto format = decodePixelFormat(pixelFormat);
	if (format.first == EINVAL)
		return EINVAL;
	layer.PFCR = format.second;

	const auto pixelSize = devices::Framebuffer::getPixelFormatSize(pixelFormat);

	const auto pitchInBytes = pixelSize * (x1 - x0 + 1);
	const auto lineLength = pixelSize * (x1 - x0 + 1) + 3;
	val = (pitchInBytes << 16) | lineLength;
	layer.CFBLR = val;

	layer.CACR = alphaMax;

	val = bf1PixelAlphaXConstantAlpha | bf2PixelAlphaXConstantAlpha;
	layer.BFCR = val;

	val = y1 - y0 + 1;
	layer.CFBLNR = val;

	layer.CFBAR = reinterpret_cast<uint32_t>(framebuffer.getBuffer());

	val = LTDC_LxCR_LEN;

	if ((pixelFormat == devices::PixelFormat::al44 || pixelFormat == devices::PixelFormat::al88 ||
			pixelFormat == devices::PixelFormat::l8))
	{
		if (plane.isNewFramebuffer() == true)
		{
			if (setClutTable(framebuffer.getColorLookUpTable(), type, pixelFormat) != 0)
				return EINVAL;
		}

		val |= LTDC_LxCR_CLUTEN;
	}

	layer.CR = val;

	return 0;
}

int ChipMipiDpiLowLevel::disable(const devices::Plane& plane)
{
	if (isStarted() == false)
		return EBADF;

	const auto type = plane.getType();
	if (type != devices::Plane::Type::primary && type != devices::Plane::Type::overlay)
		return EINVAL;

	decltype(parameters_.getPrimaryLayer()) layer = (type == devices::Plane::Type::primary) ?
			parameters_.getPrimaryLayer() : parameters_.getSecondaryLayer();

	layer.CR = 0;
	return 0;
}

void ChipMipiDpiLowLevel::flush()
{
	if (isStarted() == false)
		return;

	auto& ltdc = parameters_.getLtdc();
	ltdc.SRCR = LTDC_SRCR_VBR;
}

int ChipMipiDpiLowLevel::start(devices::MipiDpiBase& displayBase, const devices::VideoMode& videoMode)
{
	if (isStarted() == true)
		return EBADF;

	mipiDpiBase_ = &displayBase;
	parameters_.enablePeripheralClock(true);
	parameters_.resetPeripheral();
	auto& ltdc = parameters_.getLtdc();

	if (setVideoMode(videoMode))
		return EINVAL;

	ltdc.BCCR = bccBackgroundBlack;
	ltdc.IER = LTDC_IER_LIE | LTDC_IER_FUIE | LTDC_IER_TERRIE;

	// immediately commit the planes
	ltdc.SRCR = LTDC_SRCR_IMR;
	ltdc.GCR |= LTDC_GCR_LTDCEN;

	return 0;
}

int ChipMipiDpiLowLevel::stop()
{
	if (isStarted() == false)
		return EBADF;

	parameters_.resetPeripheral();
	parameters_.enablePeripheralClock(false);
	mipiDpiBase_ = nullptr;
	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------+
| private functions
+---------------------------------------------------------------------------------------------------------------------*/

int ChipMipiDpiLowLevel::setVideoMode(const devices::VideoMode& videoMode)
{
	// convert video timings to ltdc timings
	const auto hsync = videoMode.hSyncLength ? videoMode.hSyncLength - 1 : 0;
	const auto vsync = videoMode.vSyncLength ? videoMode.vSyncLength - 1 : 0;
	const auto accumHbp = hsync + videoMode.hBackPorch;
	const auto accumVbp = vsync + videoMode.vBackPorch;
	const auto accumActW = accumHbp + videoMode.hActive;
	const auto accumActH = accumVbp + videoMode.vActive;
	const auto totalWidth = accumActW + videoMode.hFrontPorch_;
	const auto totalHeight = accumActH + videoMode.vFrontPorch;
	const auto signalsBits = videoMode.signalBits;

	uint32_t flags = 0;

	if (signalsBits[devices::VideoMode::SignalBitsSet::SignalBits::hSyncPolarity])
		flags |= LTDC_GCR_HSPOL;

	if (signalsBits[devices::VideoMode::SignalBitsSet::SignalBits::vSyncPolarity])
		flags |= LTDC_GCR_VSPOL;

	if (signalsBits[devices::VideoMode::SignalBitsSet::SignalBits::dataEnablePolarity])
		flags |= LTDC_GCR_VSPOL;

	if (signalsBits[devices::VideoMode::SignalBitsSet::SignalBits::pixelDataEdge])
		flags |= LTDC_GCR_PCPOL;

	auto& ltdc = parameters_.getLtdc();

	ltdc.GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_VSPOL | LTDC_GCR_PCPOL);
	ltdc.GCR |= flags;

	// sets synchronization size
	auto val = (hsync << 16) | vsync;
	ltdc.SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
	ltdc.SSCR |= val;

	// sets accumulated back porch
	val = (accumHbp << 16) | accumVbp;
	ltdc.BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
	ltdc.BPCR |= val;

	// sets accumulated active width and height
	val = (accumActW << 16) | accumActH;
	ltdc.AWCR &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
	ltdc.AWCR |= val;

	// sets total width & height
	val = (totalWidth << 16) | totalHeight;
	ltdc.TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
	ltdc.TWCR |= val;

	ltdc.LIPCR = accumActH + 1;

	return 0;
}

std::pair<int, uint8_t> ChipMipiDpiLowLevel::decodePixelFormat(const devices::PixelFormat pixelFormat)
{
	static const std::pair<devices::PixelFormat, uint8_t> associations[]
	{
			{devices::PixelFormat::argb8888, 0x00},
			{devices::PixelFormat::rgb888, 0x01},
			{devices::PixelFormat::rgb565, 0x02},
			{devices::PixelFormat::argb1555, 0x03},
			{devices::PixelFormat::argb4444, 0x04},
			{devices::PixelFormat::l8, 0x05},
			{devices::PixelFormat::al44, 0x06},
			{devices::PixelFormat::al88, 0x07},
	};

	for (auto& association : associations)
		if (association.first == pixelFormat)
		{
			return {{}, association.second};
		}

	return {EINVAL, {}};
}

int ChipMipiDpiLowLevel::setClutTable(const devices::RgbColorsRange lut, const devices::Plane::Type type,
		const devices::PixelFormat pixelFormat)
{
	static const std::pair<devices::PixelFormat, uint16_t> associations[]
	{
			{devices::PixelFormat::al44, 16},
			{devices::PixelFormat::al88, 256},
			{devices::PixelFormat::l8, 256},
	};

	for (auto& association : associations)
		if (association.first == pixelFormat && association.second == lut.size())
		{
			decltype(parameters_.getPrimaryLayer()) layer = (type == devices::Plane::Type::primary) ?
					parameters_.getPrimaryLayer() : parameters_.getSecondaryLayer();

			auto i = 0;
			for (const auto param : lut)
			{
				const auto position = (pixelFormat == devices::PixelFormat::al44) ? i * 0x11 : i;
				layer.CLUTWR = (position << 24) | ((param.red << 16) & 0xff0000) | (param.green << 8 & 0xff00) |
					(param.blue & 0xff);
				i++;
			}
			return 0;
		}

	return EINVAL;
}

}	// namespace chip

}	// namespace distortos
