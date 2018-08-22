/**
 * \file
 * \brief PixelFormat enum class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDPI_PIXELFORMAT_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDPI_PIXELFORMAT_HPP_

#include <cstdint>

namespace distortos
{

namespace devices
{

/**
 * Pixel Format
 *
 * \ingroup devices
 */

enum class PixelFormat : uint8_t
{
	/// ARGB8888
	argb8888,
	/// RGB888
	rgb888,
	/// RGB565
	rgb565,
	/// ARGB1555
	argb1555,
	/// ARGB4444
	argb4444,
	/// L8
	l8,
	/// AL44
	al44,
	/// AL88
	al88,
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDPI_PIXELFORMAT_HPP_
