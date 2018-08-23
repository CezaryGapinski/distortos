/**
 * \file
 * \brief MipiDbiLowLevel class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBILOWLEVEL_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBILOWLEVEL_HPP_

#include <bitset>

namespace distortos
{

namespace devices
{

/**
 * MipiDbiLowLevel class is an interface which can serve as a base for low-level MIPI DBI devices
 *
 * \ingroup devices
 */

class MipiDbiLowLevel
{
public:

	/**
	 * \brief MipiDbiLowLevel's destructor
	 */

	virtual ~MipiDbiLowLevel() = 0;

	/**
	 * \brief Closes MipiDbi low-level driver.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - error codes returned by SpiDevice::close();
	 */

	virtual int close() = 0;

	/**
	 * \brief Opens MipiDbi low-level driver.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - error codes returned by SpiDevice::open();
	 */

	virtual int open() = 0;

	/**
	 * \brief Writes command with parameters to MIPI DBI low-level driver.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to write
	 * \param [in] buffer is the buffer with command parameters
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a address and/or \a buffer and/or \a size are not valid;
	 * - EIO - error during communication;
	 */

	virtual int write(uint8_t command, const void* buffer, size_t size) = 0;

	/**
	 * \brief Reads data from MIPI DBI low-level driver.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to get parameter
	 * \param [out] buffer is the buffer into which the parameter will be read
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a address and/or \a buffer and/or \a size are not valid;
	 * - EIO - error during communication;
	 */

	virtual int read(uint8_t command, void* buffer, size_t size) = 0;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBILOWLEVEL_HPP_
