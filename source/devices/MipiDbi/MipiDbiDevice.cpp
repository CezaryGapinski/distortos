/**
 * \file
 * \brief MipiDbiDevice class implementation
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/devices/MipiDbi/MipiDbiDevice.hpp"

#include "distortos/internal/CHECK_FUNCTION_CONTEXT.hpp"

#include "estd/ScopeGuard.hpp"

#include <mutex>

namespace distortos
{

namespace devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

MipiDbiDevice::~MipiDbiDevice()
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)
		return;

	const std::lock_guard<Mutex> lockGuard {mutex_};

	mipiDbi_.close();
}

int MipiDbiDevice::close()
{
	const std::lock_guard<Mutex> lockGuard {mutex_};

	if (isOpened_ == false)	// device is not open anymore?
		return EBADF;

	const auto ret = mipiDbi_.close();
	if (ret != 0)
		return ret;

	isOpened_ = false;
	return 0;
}

int MipiDbiDevice::open()
{
	const std::lock_guard<Mutex> lockGuard {mutex_};

	if (isOpened_ == true)	// device is already opened?
		return EMFILE;

	const auto ret = mipiDbi_.open();
	if (ret != 0)
		return ret;

	isOpened_ = true;
	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------+
| protected functions
+---------------------------------------------------------------------------------------------------------------------*/

int MipiDbiDevice::writeDcsCmd(const MipiUserCommandSet command, const void* buffer, const size_t size)
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)	// device is not open anymore?
		return EBADF;

	return mipiDbi_.write(static_cast<uint8_t>(command), buffer, size);
}

int MipiDbiDevice::readDcsCmd(const MipiUserCommandSet command, void* const buffer, const size_t size)
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)	// device is not open anymore?
		return EBADF;

	return mipiDbi_.read(static_cast<uint8_t>(command), buffer, size);
}

int MipiDbiDevice::writeMcsCmd(const uint8_t command, const void* buffer, const size_t size)
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)	// device is not open anymore?
		return EBADF;

	if (command < userCommandSetStartRange)
		return EINVAL;

	return mipiDbi_.write(command, buffer, size);
}

int MipiDbiDevice::readMcsCmd(const uint8_t command, void* const buffer, const size_t size)
{
	CHECK_FUNCTION_CONTEXT();

	if (isOpened_ == false)	// device is not open anymore?
		return EBADF;

	if (command < userCommandSetStartRange)
		return EINVAL;

	return mipiDbi_.read(command, buffer, size);
}

}	// namespace devices

}	// namespace distortos
