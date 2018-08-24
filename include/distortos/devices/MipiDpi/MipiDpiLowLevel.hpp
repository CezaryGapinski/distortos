/**
 * \file
 * \brief MipiDpiLowLevel class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPILOWLEVEL_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPILOWLEVEL_HPP_

#include "distortos/devices/display/Plane.hpp"

namespace distortos
{

namespace devices
{

class MipiDpiBase;
class VideoMode;

/**
 * MipiDpiLowLevel class is an interface for low-level MIPI DPI driver
 *
 * \ingroup devices
 */

class MipiDpiLowLevel
{
public:

	/**
	 * \brief MipiDpiLowLevel's destructor
	 */

	virtual ~MipiDpiLowLevel() = 0;

	/**
	 * \brief Starts low-level MIPI DPI driver.
	 *
	 * \param [in] mipiDpiBase is a reference to MipiDpiBase object that will be associated with this one
	 * \param [in] videoMode is a reference to the desired video mode configuration
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - read and/or write are in progress;
	 * - EINVAL - selected video mode is invalid;
	 */

	virtual int start(MipiDpiBase& mipiDpiBase, const VideoMode& videoMode) = 0;

	/**
	 * \brief Stops low-level MIPI DPI driver.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - read and/or write are in progress;
	 */

	virtual int stop() = 0;

	/**
	 * \brief Updates state of Display Plane.
	 *
	 * \param [in] plane is a reference to Plane associated with this update
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EINVAL - position parameters are invalid;
	 */

	virtual int update(const Plane& plane) = 0;

	/**
	 * \brief Disables specified plane.
	 *
	 * \param [in] plane is a reference to Plane to disable
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 */

	virtual int disable(const Plane& plane) = 0;

	/**
	 * \brief Flushes planes changes in next vertical blanking period.
	 */

	virtual void flush() = 0;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPILOWLEVEL_HPP_
