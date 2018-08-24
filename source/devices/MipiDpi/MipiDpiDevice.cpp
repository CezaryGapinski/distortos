/**
 * \file
 * \brief MipiDpiDevice class implementation
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/devices/display/DisplayPlaneOperation.hpp"
#include "distortos/devices/MipiDpi/MipiDpiDevice.hpp"
#include "distortos/devices/MipiDpi/MipiDpiLowLevel.hpp"

#include "distortos/internal/CHECK_FUNCTION_CONTEXT.hpp"

#include "distortos/Semaphore.hpp"
#include "estd/ScopeGuard.hpp"

#include <mutex>

namespace distortos
{

namespace devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

MipiDpiDevice::~MipiDpiDevice()
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)
		return;

	const std::lock_guard<Mutex> lockGuard {mutex_};

	mipiDpi_.stop();
}

int MipiDpiDevice::close()
{
	const std::lock_guard<Mutex> lockGuard {mutex_};

	if (isOpened_ == false)	// device is not open anymore?
		return EBADF;

	const auto ret = mipiDpi_.stop();
	if (ret != 0)
		return ret;

	isOpened_ = false;
	isError_ = false;
	return 0;
}

int MipiDpiDevice::open(const VideoMode& videoMode)
{
	const std::lock_guard<Mutex> lockGuard {mutex_};

	if (isOpened_ == true)	// device is already opened?
		return EMFILE;

	const auto ret = mipiDpi_.start(*this, videoMode);
	if (ret != 0)
		return ret;

	isOpened_ = true;
	return 0;
}

int MipiDpiDevice::waitForVSyncEvent()
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)	// device is not open anymore?
		return EBADF;

	Semaphore semaphore {0};
	vSyncSemaphore_ = &semaphore;

	const auto transmitSemaphoreScopeGuard = estd::makeScopeGuard(
			[this]()
			{
				vSyncSemaphore_ = {};
			});

	const auto ret = semaphore.wait();
	if (ret != 0)
		return ret;

	return 0;
}

int MipiDpiDevice::executeTransaction(const DisplayPlaneOperationsRange planes)
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)
		return EBADF;

	if (isError_ == true)
		return EIO;

	if (inProgress_ == true)
		return EBUSY;

	for (size_t i {0}; i < planes.size(); ++i)
	{
		auto& plane = planes.begin()[i].getPlane();
		if (plane.isEnabled() == true)
		{
			const auto result = mipiDpi_.update(plane);
			if (result != 0)
				return result;

			plane.notifyUpdate();

		}
		else
		{
			const auto result = mipiDpi_.disable(plane);
			if (result != 0)
				return result;
		}
	}

	mipiDpi_.flush();
	inProgress_ = true;

	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------+
| private functions
+---------------------------------------------------------------------------------------------------------------------*/

void MipiDpiDevice::VSyncEvent()
{
	inProgress_ = false;

	const auto vBlankSemaphore = vSyncSemaphore_;
	if (vBlankSemaphore != nullptr)
	{
		vBlankSemaphore->post();
		vSyncSemaphore_ = {};
	}
}

void MipiDpiDevice::errorEvent(ErrorSet)
{
	isError_ = true;
}

}	// namespace devices

}	// namespace distortos
