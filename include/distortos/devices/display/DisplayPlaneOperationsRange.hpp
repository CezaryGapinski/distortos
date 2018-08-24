/**
 * \file
 * \brief DisplayPlaneOperationsRange type alias header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAY_DISPLAYPLANEOPERATIONSRANGE_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAY_DISPLAYPLANEOPERATIONSRANGE_HPP_

#include "estd/ContiguousRange.hpp"

namespace distortos
{

namespace devices
{

class DisplayPlaneOperation;

/**
 * DisplayPlaneOperationsRange is an alias for ContiguousRange of DisplayPlaneOperation elements
 *
 * \ingroup devices
 */

using DisplayPlaneOperationsRange = estd::ContiguousRange<DisplayPlaneOperation>;

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDPI_DISPLAYPLANEOPERATIONSRANGE_HPP_
