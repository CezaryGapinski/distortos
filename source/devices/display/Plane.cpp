/**
 * \file
 * \brief Plane class implementation
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/devices/display/Plane.hpp"

#include "distortos/devices/display/Framebuffer.hpp"

namespace distortos
{

namespace devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

Plane::~Plane()
{

}

void Plane::swapFramebuffer(const Framebuffer& framebuffer)
{
	framebuffer_ = framebuffer;
	newFramebuffer_ = true;
}

void Plane::position(const int16_t xDisplay, const int16_t yDisplay)
{
	xDisplay_ = xDisplay;
	yDisplay_ = yDisplay;
}

}	// namespace devices

}	// namespace distortos
