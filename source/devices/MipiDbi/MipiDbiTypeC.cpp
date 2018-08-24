/**
 * \file
 * \brief MipiDbiTypeC class implementation
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/devices/MipiDbi/MipiDbiTypeC.hpp"

#include "distortos/devices/communication/SpiDeviceProxy.hpp"
#include "distortos/devices/communication/SpiDeviceSelectGuard.hpp"
#include "distortos/devices/communication/SpiMasterOperation.hpp"
#include "distortos/devices/communication/SpiMasterProxy.hpp"

#include "distortos/devices/io/OutputPin.hpp"

#include "distortos/internal/CHECK_FUNCTION_CONTEXT.hpp"


namespace distortos
{

namespace devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

MipiDbiTypeC::~MipiDbiTypeC()
{

}

int MipiDbiTypeC::close()
{
	return spiDevice_.close();
}

int MipiDbiTypeC::open()
{
	return spiDevice_.open();
}

int MipiDbiTypeC::write(const uint8_t command, const void* buffer, const size_t size)
{
	const SpiDeviceProxy spiDeviceProxy {spiDevice_};

	{
		SpiMasterOperation operation {{&command, nullptr, sizeof(command)}};
		// write command
		dataCommandPin_.set(false);
		const auto ret = executeTransaction(spiDeviceProxy, SpiMasterOperationsRange{operation});
		if (ret.first)
			return ret.first;
	}

	// command without parameters
	if (buffer == nullptr || size == 0)
		return 0;

	// write parameters
	dataCommandPin_.set(true);
	const auto commandBuf = static_cast<const uint8_t*>(buffer);
	for (size_t i = 0; i < size; i++)
	{
		SpiMasterOperation operation {{&commandBuf[i], nullptr, sizeof(commandBuf[i])}};
		const auto ret = executeTransaction(spiDeviceProxy, SpiMasterOperationsRange{operation});
		if (ret.first)
			return ret.first;
	}

	return 0;
}

int MipiDbiTypeC::read(const uint8_t command, void* const buffer, const size_t size)
{
	if (buffer == nullptr || size == 0)
		return 0;

	const SpiDeviceProxy spiDeviceProxy {spiDevice_};

	{
		SpiMasterOperation operation {{&command, nullptr, sizeof(command)}};
		// write command
		dataCommandPin_.set(false);
		const auto ret = executeTransaction(spiDeviceProxy, SpiMasterOperationsRange{operation});
		if (ret.first)
			return ret.first;
	}

	{
		// read parameters
		dataCommandPin_.set(true);
		SpiMasterOperation operation {{nullptr, buffer, size}};
		const auto ret = executeTransaction(spiDeviceProxy, SpiMasterOperationsRange{operation});
		return ret.first;
	}

}

/*---------------------------------------------------------------------------------------------------------------------+
| private functions
+---------------------------------------------------------------------------------------------------------------------*/

std::pair<int, size_t> MipiDbiTypeC::executeTransaction(const SpiDeviceProxy& spiDeviceProxy,
		const SpiMasterOperationsRange operationsRange) const
{
	SpiMasterProxy spiMasterProxy {spiDeviceProxy};
	{
		const auto ret = spiMasterProxy.configure(SpiMode::_0, clockFrequency_, 8, false, {});
		if (ret.first != 0)
			return {ret.first, {}};
	}

	const SpiDeviceSelectGuard spiDeviceSelectGuard {spiMasterProxy};
	return spiMasterProxy.executeTransaction(operationsRange);
}

}	// namespace devices

}	// namespace distortos
