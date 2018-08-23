/**
 * \file
 * \brief Ili9341 class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAYDRIVER_ILI9341_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAYDRIVER_ILI9341_HPP_

#include "distortos/devices/MipiDbi/MipiDbiDevice.hpp"
#include "distortos/devices/MipiDbi/MipiUserCommandSet.hpp"
#include "distortos/devices/DisplayDriver/Ili9341ManufacturerCommandSet.hpp"

namespace distortos
{

namespace devices
{

/**
 * Ili9341 class is a MIPI DBI Device implementation for ili9341 Display Panel.
 *
 * \ingroup devices
 */

class Ili9341 : public MipiDbiDevice
{
public:

	/**
	 * \brief Ili9341's constructor
	 *
	 * \param [in] mipiDbi is a reference to MIPI DBI driver to which this display is connected
	 */

	constexpr Ili9341(MipiDbiLowLevel& mipiDbi) :
			MipiDbiDevice{mipiDbi}
	{

	}

	/**
	 * \brief Ili9341's destructor
	 */

	~Ili9341();

	/**
	 * \brief Writes command from MIPI DBI Command Set.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to write
	 * \param [in] buffer is the buffer with command parameters
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a command and/or \a buffer and/or \a size are not valid;
	 * - EIO - error during communication;
	 */

	int writeCmd(MipiUserCommandSet command, const void* buffer, size_t size);

	/**
	 * \brief Writes command from Ili9341 Manufacturer Command Set.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to write
	 * \param [in] buffer is the buffer with command parameters
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a command and/or \a buffer and/or \a size are not valid;
	 * - EIO - error during communication;
	 */

	int writeCmd(Ili9341ManufacturerCommandSet command, const void* buffer, size_t size);

	/**
	 * \brief Reads data for MIPI DBI Command Set.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to get parameter
	 * \param [out] buffer is the buffer into which the parameter will be read
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a command and/or \a buffer and/or \a size are not valid;
	 * - EIO - error during communication;
	 */

	int readCmd(MipiUserCommandSet command, void* buffer, size_t size);

	/**
	 * \brief Reads data for Ili9341 Manufacturer Command Set.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to get parameter
	 * \param [out] buffer is the buffer into which the parameter will be read
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a command and/or \a buffer and/or \a size are not valid;
	 * - EIO - error during communication;
	 */

	int readCmd(Ili9341ManufacturerCommandSet command, void* buffer, size_t size);
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_DISPLAYDRIVER_MIPIILI9341DBI_HPP_
