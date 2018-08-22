/**
 * \file
 * \brief RgbColor struct header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAY_RGBCOLOR_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAY_RGBCOLOR_HPP_

#include <cstdint>

namespace distortos
{

namespace devices
{

/**
 * RgbColor struct is a struct with values in RGB color model
 *
 * \ingroup devices
 */

struct RgbColor
{
	/// red value
	uint8_t red;

	/// green value
	uint8_t green;

	/// blue value
	uint8_t blue;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_DISPLAY_RGBCOLOR_HPP_
