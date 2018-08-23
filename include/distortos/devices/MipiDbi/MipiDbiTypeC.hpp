/**
 * \file
 * \brief MipiDbi class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBITYPEC_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBITYPEC_HPP_

#include "distortos/devices/MipiDbi/MipiDbiLowLevel.hpp"
#include "distortos/devices/communication/SpiDevice.hpp"

namespace distortos
{

namespace devices
{

/**
 * MipiDbiTypeC class is a implementation of MPI DBI interface connected via SPI.
 *
 * \ingroup devices
 */

class MipiDbiTypeC : public MipiDbiLowLevel
{
public:

	/**
	 * \brief MipiDbiTypeC's constructor for MIPI DBI Type C in 4 line mode (Option 3)
	 *
	 * \param [in] spiMaster is a reference to SPI master to which this MIPI DBI is connected
	 * \param [in] slaveSelectPin is a reference to slave select pin of this MIPI DBI
	 * \param [in] dataCommandPin is a reference to D/CX pin(select command or data)
	 * \param [in] clockFrequency is the desired clock frequency of MIPI DBI, Hz, default - 5 MHz
	 */

	constexpr MipiDbiTypeC(SpiMaster& spiMaster, OutputPin& slaveSelectPin, OutputPin& dataCommandPin,
			const uint32_t clockFrequency = 5000000) :
			spiDevice_{spiMaster, slaveSelectPin},
			dataCommandPin_{dataCommandPin},
			clockFrequency_{clockFrequency}
	{

	}

	/**
	 * \brief MipiDbiTypeC's destructor
	 */

	~MipiDbiTypeC() override;

	/**
	 * \brief Closes MIPI DBI.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - error codes returned by SpiDevice::close();
	 */

	int close() override;

	/**
	 * \brief Opens MIPI DBI.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - error codes returned by SpiDevice::open();
	 */

	int open() override;

	/**
	 * \brief Writes command with parameters to MIPI DBI device.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to write
	 * \param [in] buffer is the buffer with command parameters
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return pair with return code (0 on success, error code otherwise) and number of programmed bytes (valid even
	 * when error code is returned); error codes:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a buffer and/or \a size are not valid;
	 * - error codes returned by SpiMasterProxy::executeTransaction();
	 */

	int write(uint8_t command, const void* buffer, size_t size) override;

	/**
	 * \brief Reads data from MIPI DBI device.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \param [in] command is the command to get parameter
	 * \param [out] buffer is the buffer into which the parameter will be read
	 * \param [in] size is the size of \a buffer, bytes
	 *
	 * \return pair with return code (0 on success, error code otherwise) and number of read bytes (valid even when
	 * error code is returned); error codes:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a buffer and/or \a size are not valid;
	 * - error codes returned by SpiMasterProxy::executeTransaction();
	 */

	int read(uint8_t command, void* buffer, size_t size) override;

private:

	/**
	 * \brief Executes series of operations as a single atomic transaction.
	 *
	 * \param [in] operationsRange is the range of operations that will be executed
	 *
	 * \return pair with return code (0 on success, error code otherwise) and number of successfully completed
	 * operations from \a operationsRange; error codes:
	 * - error codes returned by SpiMasterProxy::configure();
	 * - error codes returned by SpiMasterProxy::executeTransaction();
	 */

	std::pair<int, size_t> executeTransaction(const SpiDeviceProxy& spiDeviceProxy,
			SpiMasterOperationsRange operationsRange) const;

	/// internal SPI slave device
	SpiDevice spiDevice_;

	/// reference to D/CX pin of this MIPI DBI device
	OutputPin& dataCommandPin_;

	/// desired clock frequency of MIPI DBI, Hz
	uint32_t clockFrequency_;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIDBITYPEC_HPP_
