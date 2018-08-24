/**
 * \file
 * \brief Framebuffer class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAY_FRAMEBUFFER_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAY_FRAMEBUFFER_HPP_

#include "distortos/devices/display/PixelFormat.hpp"
#include "distortos/devices/display/RgbColorsRange.hpp"

namespace distortos
{

namespace devices
{

/**
 * Framebuffer class is a class with Display Framebuffer
 *
 * \ingroup devices
 */

class Framebuffer
{
public:

	/**
	 * \brief Framebuffer's constructor
	 *
	 * \param [in] buffer is a pointer to memory area buffer associated with this Framebuffer
	 * \param [in] pixelFormat is a PixelFormat of this Framebuffer
	 * \param [in] xSize is a x size in bytes of this Framebuffer
	 * \param [in] ySize is a y size in bytes of this Framebuffer
	 * \param [in] colorLookUpTable is a buffer with color look up RGB888 table for PixelFormat::l8, PixelFormat::al44,
	 * PixelFormat::al88
	 */

	constexpr explicit Framebuffer(const void* const buffer, const PixelFormat pixelFormat, const uint32_t xSize,
			const uint32_t ySize, const RgbColorsRange colorLookUpTable = {}) :
		pixelFormat_{pixelFormat},
		xSize_{xSize},
		ySize_{ySize},
		buffer_{buffer},
		colorLookUpTable_{colorLookUpTable}
	{

	}

	/**
	 * return x size in bytes
	 */

	uint32_t getXsize() const
	{
		return xSize_;
	}

	/**
	 * return x size in bytes
	 */

	uint32_t getYsize() const
	{
		return ySize_;
	}

	/**
	 * return pixel format
	 */

	PixelFormat getPixelFormat() const
	{
		return pixelFormat_;
	}

	/**
	 * return pointer to buffer
	 */

	const void* getBuffer() const
	{
		return buffer_;
	}

	/**
	 * \return pointer to color look-up table for PixelFormat::l8, PixelFormat::al44 or PixelFormat::al88
	 */

	const RgbColorsRange getColorLookUpTable() const
	{
		return colorLookUpTable_;
	}

	/**
	 * \brief Gets pixel size in bytes for specified PixelFormat
	 *
	 * \param [in] pixelFormat is a selected pixel format
	 *
	 * \return pixel size in bytes for specified PixelFormat
	 */

	static uint8_t getPixelFormatSize(const PixelFormat pixelFormat)
	{
		switch (pixelFormat)
		{
			case PixelFormat::argb8888:
				return 4;
				break;
			case PixelFormat::rgb888:
				return 3;
				break;
			case PixelFormat::rgb565:
			case PixelFormat::argb1555:
			case PixelFormat::argb4444:
				return 2;
				break;
			case PixelFormat::l8:
			case PixelFormat::al44:
			case PixelFormat::al88:
			default:
				return 1;
				break;
		}
	}

private:

	/// Framebuffer pixel format
	PixelFormat pixelFormat_;

	/// x size of Framebuffer in bytes
	uint32_t xSize_;

	/// y size of Framebuffer in bytes
	uint32_t ySize_;

	/// allocated buffer with size equal to xSize_ * ySize_
	const void* buffer_;

	/// color look-up table for PixelFormat::l8, PixelFormat::al44 or PixelFormat::al88
	RgbColorsRange colorLookUpTable_;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_DISPLAY_FRAMEBUFFER_HPP_
