/**
 * \file
 * \brief ChipMipiDpiLowLevel class header for LTDCv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_LTDCV1_INCLUDE_DISTORTOS_CHIP_CHIPMIPIDPILOWLEVEL_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_LTDCV1_INCLUDE_DISTORTOS_CHIP_CHIPMIPIDPILOWLEVEL_HPP_

#include "distortos/devices/display/VideoMode.hpp"
#include "distortos/devices/display/RgbColor.hpp"
#include "distortos/devices/display/Framebuffer.hpp"

#include "distortos/devices/MipiDpi/MipiDpiLowLevel.hpp"

#include "distortos/distortosConfiguration.h"

namespace distortos
{

namespace chip
{

/**
 * ChipMipiDpiLowLevel class is a low-level LTDC driver for LTDCv1 in STM32
 *
 * \ingroup devices
 */

class ChipMipiDpiLowLevel : public devices::MipiDpiLowLevel
{
public:

	class Parameters;

	/// parameters for construction of Display low-level driver
	static const Parameters parameters_;

	/**
	 * \brief ChipMipiDpiLowLevel's constructor
	 *
	 */

	constexpr explicit ChipMipiDpiLowLevel() :
			mipiDpiBase_{}
	{

	}

	/**
	 * \brief ChipMipiDpiLowLevel's destructor
	 *
	 * Does nothing if driver is already stopped. If it's not, performs forced stop of operation.
	 */

	~ChipMipiDpiLowLevel() override;

	/**
	 * \brief Interrupt handler
	 *
	 * \note this must not be called by user code
	 */

	void interruptHandler();

	/**
	 * \brief Update and enable plane settings for specified parameters if driver is started.
	 *
	 * \param [in] plane is a reference to Plane associated with this update
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EINVAL - incorrect input parameters;
	 */

	int update(const devices::Plane& plane) override;

	/**
	 * \brief Disables specified plane.
	 *
	 * \param [in] plane is a reference to Plane to disable
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 */

	int disable(const devices::Plane& plane) override;

	/**
	 * \brief Flushes all planes in next vertical blanking period to hardware if driver is started.
	 *
	 */

	void flush() override;

	/**
	 * \brief Starts low-level LTDC driver.
	 *
	 * \param [in] displayBase is a reference to DisplayBase object that will be associated with this one
	 * \param [in] videoMode is a reference to the desired video mode configuration
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - read and/or write are in progress;
	 * - EINVAL - selected video mode is invalid;
	 */

	int start(devices::MipiDpiBase& displayBase, const devices::VideoMode& videoMode) override;

	/**
	 * \brief Stops low-level LTDC driver.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - read and/or write are in progress;
	 */

	int stop() override;

private:

	/**
	 * \brief Configure LTDC driver video mode base on VideoMode.
	 *
	 * \param [in] videoMode is a reference to the desired video mode configuration
	 *
	 * \return 0 on success, error code otherwise:
	 * - EINVAL - selected video mode is invalid;
	 */

	int setVideoMode(const devices::VideoMode& videoMode);

	/**
	 * \brief Decodes Display Plane pixel format to driver specific format
	 *
	 * \param [in] pixelFormat is desired pixel format
	 *
	 * \return pair with return code (0 on success, error code otherwise) and register value; error codes:
	 * - EINVAL - selected baud rate and/or format are invalid;
	 */

	std::pair<int, uint8_t> decodePixelFormat(devices::PixelFormat pixelFormat);

	/**
	 * \brief configure Color Look-Up Table
	 *
	 * \param [in] lut is a Color Look-Up Table
	 * \param [in] type is a type of Plane
	 * \param [in] pixelFromat is specified PixelFormat
	 *
	 * \return 0 on success, error code otherwise:
	 * - EINVAL - selected video mode is invalid;
	 */

	int setClutTable(const devices::RgbColorsRange lut, devices::Plane::Type type, devices::PixelFormat pixelFormat);

	/**
	 * \return true if driver is started, false otherwise
	 */

	bool isStarted() const
	{
		return mipiDpiBase_ != nullptr;
	}

	/// pointer to MipiDpiBase object associated with this one
	devices::MipiDpiBase* mipiDpiBase_;
};

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_LTDCV1_INCLUDE_DISTORTOS_CHIP_CHIPMIPIDPILOWLEVEL_HPP_
