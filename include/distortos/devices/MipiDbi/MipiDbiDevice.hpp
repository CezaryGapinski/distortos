/**
 * \file
 * \brief MipiDbiDevice class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBIDEVICE_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBIDEVICE_HPP_

#include "distortos/devices/MipiDbi/MipiDbiLowLevel.hpp"
#include "distortos/devices/MipiDbi/MipiUserCommandSet.hpp"

#include "distortos/Mutex.hpp"

namespace distortos
{

namespace devices
{

/**
 * MipiDbiDevice class is a MIPI DBI Device implementation.
 *
 * \ingroup devices
 */

class MipiDbiDevice
{
public:

	/// start range for User Command Set
	constexpr static uint8_t userCommandSetStartRange {0xb0};

	/**
	 * \brief MipiDbiDevice's constructor
	 *
	 * \param [in] mipiDbi is a reference to low-level MIPI DBI driver to which this MIPI DPI interface is connected
	 */

	constexpr MipiDbiDevice(MipiDbiLowLevel& mipiDbi) :
			mutex_{Mutex::Protocol::priorityInheritance},
			mipiDbi_{mipiDbi},
			isOpened_{}
	{

	}

	/**
	 * \brief MipiDbiDevice's destructor
	 */

	~MipiDbiDevice();

	/**
	 * \brief Closes MipiDbiDevice device.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - error codes returned by SpiDevice::close();
	 */

	int close();

	/**
	 * \brief Opens MipiDbiDevice device.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - EMFILE - this device is already opened;
	 * - error codes returned by MipiDbiLowLevel::open();
	 */

	int open();

protected:

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
	 * - error codes returned by MipiDbiLowLevel::write();
	 */

	int writeDcsCmd(MipiUserCommandSet command, const void* buffer, size_t size);

	/**
	 * \brief Writes command from Manufacturer Command Set.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to write
	 * \param [in] buffer is the buffer with command parameters
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - error codes returned by MipiDbiLowLevel::write();
	 */

	int writeMcsCmd(uint8_t command, const void* buffer, size_t size);

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
	 * - error codes returned by MipiDbiLowLevel::read();
	 */

	int readDcsCmd(MipiUserCommandSet command, void* buffer, size_t size);

	/**
	 * \brief Reads data for Manufacturer Command Set.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to get parameter
	 * \param [out] buffer is the buffer into which the parameter will be read
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - error codes returned by MipiDbiLowLevel::read();
	 */

	int readMcsCmd(uint8_t command, void* buffer, size_t size);

private:

	/// mutex used to serialize access to this object
	Mutex mutex_;

	/// internal MIPI DBI slave device
	MipiDbiLowLevel& mipiDbi_;

	/// indicates device open status
	bool isOpened_;

};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBIDEVICE_HPP_
