/**
 * \file
 * \brief MipiDpiDevice class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPIDEVICE_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPIDEVICE_HPP_

#include "distortos/devices/display/DisplayPlaneOperation.hpp"
#include "distortos/devices/display/DisplayPlaneOperationsRange.hpp"

#include "distortos/devices/MipiDpi/MipiDpiBase.hpp"

#include "distortos/Mutex.hpp"

namespace distortos
{

class Semaphore;

namespace devices
{

class VideoMode;
class MipiDpiLowLevel;

/**
 * MipiDpiDevice class is a device for MIPI DPI interface
 *
 * \ingroup devices
 */

class MipiDpiDevice : private MipiDpiBase
{
public:

	/**
	 * \brief MipiDpiDevice's constructor
	 *
	 * \param [in] mipiDpi is a reference to low-level implementation of MipiDpiLowLevel interface
	 */

	constexpr explicit MipiDpiDevice(MipiDpiLowLevel& mipiDpi) :
			mutex_{Mutex::Protocol::priorityInheritance},
			mipiDpi_{mipiDpi},
			vSyncSemaphore_{},
			isOpened_{},
			inProgress_{},
			isError_{}
	{

	}

	/**
	 * \brief MipiDpiDevice's destructor
	 *
	 * \warning This function must not be called from interrupt context!
	 */

	~MipiDpiDevice() override;

	/**
	 * \brief Closes MipiDpiDevice.
	 *
	 * Does nothing if any user still has this device opened. Otherwise all transfers and low-level driver are stopped.
	 * If any write transfer is still in progress, this function will wait for physical end of transmission before
	 * shutting the device down.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is already completely closed;
	 * - error codes returned by MipiDpiLowLevel::stop();
	 */

	int close();

	/**
	 * \brief Opens MIPI DPI low-level driver.
	 *
	 * Does nothing if any user already has this device opened. Otherwise low-level driver is started.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] videoMode is desired video mode for this driver
	 *
	 * \return 0 on success, error code otherwise:
	 * - EMFILE - this device is already opened;
	 * - error codes returned by MipiDpiLowLevel::start();
	 */

	int open(const VideoMode& videoMode);

	/**
	 * \brief Notifies waiting thread about V Sync event.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is already completely closed;
	 * - error codes returned by Semaphore::wait();
	 */

	int waitForVSyncEvent();

	/**
	 * \brief Executes series of operations as a single atomic transaction.
	 *
	 * Functions returns immediately. The transaction is finished when next V Sync event occurs.
	 *
	 * \param [in] operationRange is the range of planes that will be displayed depending on their parameters
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is already completely closed;
	 * - EIO - failure detected by low-level MIPI DPI driver, device must be closed;
	 * - EBUSY - previous transaction is not finished yet;
	 * - error codes returned by MipiDpiLowLevel::update();
	 * - error codes returned by MipiDpiLowLevel::disable();
	 */

	int executeTransaction(DisplayPlaneOperationsRange operationsRange);

private:

	/**
	 * \brief "V Sync" event
	 *
	 * Called by low-level MIPI DPI driver when V Sync event occurs and the transfer is physically finished.
	 */

	void VSyncEvent() override;

	/**
	 * \brief "error" event
	 *
	 * Called by low-level MIPI DPI driver when an error occurs.
	 *
	 * \param [in] errorSet is the set of error bits
	 */

	void errorEvent(ErrorSet errorSet) override;

	/// mutex used to serialize access to this object
	Mutex mutex_;

	/// reference to low-level implementation of MipiDpiLowLevel interface
	MipiDpiLowLevel& mipiDpi_;

	/// pointer to semaphore used for V Sync event notifications
	Semaphore* volatile vSyncSemaphore_;

	/// indicates device open status
	bool isOpened_;

	/// indicates whether previous transaction is in progress
	volatile bool inProgress_;

	/// indicates error occurrences
	volatile bool isError_;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPIDEVICE_HPP_
