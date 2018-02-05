/**
 * \file
 * \brief ChipUartDmaV1LowLevel class header for USARTv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTDMAV1TLOWLEVEL_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTDMAV1TLOWLEVEL_HPP_

#include "distortos/distortosConfiguration.h"

#ifdef CONFIG_CHIP_STM32_DMAV1

#include "distortos/chip/ChipUartDmaV1Transfer.hpp"
#include "distortos/chip/ChipUartLowLevel.hpp"

namespace distortos
{

namespace chip
{

class ChipUartDmaTransfer;

/**
 * ChipUartDmaLowLevel class is a low-level UART driver in DMA mode for USARTv2 in STM32
 *
 * \ingroup devices
 */

class ChipUartDmaLowLevel : public ChipUartLowLevel
{
public:

	/**
	 * \brief ChipUartDmaLowLevel constructor
	 *
	 * \param [in] parameters is a reference to object with peripheral parameters
	 * \param [in] txChipUartDmaTransfer is a reference to object with transmit in DMA mode
	 * \param [in] rxChipUartDmaTransfer is a reference to object with receiving in DMA mode
	 */

	constexpr explicit ChipUartDmaLowLevel(const Parameters& parameters, ChipUartDmaTransfer& txChipUartDmaTransfer,
			ChipUartDmaTransfer& rxChipUartDmaTransfer) :
			ChipUartLowLevel{parameters},
			txChipUartDmaTransfer_{txChipUartDmaTransfer},
			rxChipUartDmaTransfer_{rxChipUartDmaTransfer},
			readLength_{},
			writeLength_{}
	{

	}

	/**
	 * \brief ChipUartDmaLowLevel destructor
	 *
	 * Does nothing if driver is already stopped. If it's not, performs forced stop of operation.
	 */

	~ChipUartDmaLowLevel() override;

	/**
	 * \brief Interrupt handler
	 *
	 * \note this must not be called by user code
	 */

	void interruptHandler();

	/**
	 * \brief Starts low-level UART driver.
	 *
	 * Not all combinations of data format are supported. The general rules are:
	 * - if parity control is disabled, character length must not be \a minCharacterLength,
	 * - if parity control is enabled, character length must not be 9.
	 *
	 * \param [in] uartBase is a reference to UartBase object that will be associated with this one
	 * \param [in] baudRate is the desired baud rate, bps
	 * \param [in] characterLength selects character length, bits, [minCharacterLength; maxCharacterLength]
	 * \param [in] parity selects parity
	 * \param [in] _2StopBits selects whether 1 (false) or 2 (true) stop bits are used
	 *
	 * \return pair with return code (0 on success, error code otherwise) and real baud rate; error codes:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - selected baud rate and/or format are invalid;
	 */

	std::pair<int, uint32_t> start(devices::UartBase& uartBase, uint32_t baudRate, uint8_t characterLength,
			devices::UartParity parity, bool _2StopBits) override;

	/**
	 * \brief Starts asynchronous read operation.
	 *
	 * This function returns immediately. When the operation is finished (expected number of bytes were read),
	 * UartBase::readCompleteEvent() will be executed. For any detected error during reception,
	 * UartBase::receiveErrorEvent() will be executed. Note that overrun error may be reported even if it happened when
	 * no read operation was in progress.
	 *
	 * \param [out] buffer is the buffer to which the data will be written
	 * \param [in] size is the size of \a buffer, bytes, must be even if selected character length is greater than 8
	 * bits
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - read is in progress;
	 * - EINVAL - \a buffer and/or \a size are invalid;
	 */

	int startRead(void* buffer, size_t size) override;

	/**
	 * \brief Starts asynchronous write operation.
	 *
	 * This function returns immediately. If no transmission is active, UartBase::transmitStartEvent() will be executed.
	 * When the operation is finished (expected number of bytes were written), UartBase::writeCompleteEvent() will be
	 * executed. When the transmission physically ends, UartBase::transmitCompleteEvent() will be executed.
	 *
	 * \param [in] buffer is the buffer with data that will be transmitted
	 * \param [in] size is the size of \a buffer, bytes, must be even if selected character length is greater than 8
	 * bits
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - write is in progress;
	 * - EINVAL - \a buffer and/or \a size are invalid;
	 */

	int startWrite(const void* buffer, size_t size) override;

	/**
	 * \brief Stops low-level UART driver.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - read and/or write are in progress;
	 */

	int stop() override;

	/**
	 * \brief Stops asynchronous read operation.
	 *
	 * This function returns immediately. After this call UartBase::readCompleteEvent() will not be executed.
	 *
	 * \return number of bytes already read by low-level UART driver (and written to read buffer)
	 */

	size_t stopRead() override;

	/**
	 * \brief Stops asynchronous write operation.
	 *
	 * This function returns immediately. After this call UartBase::writeCompleteEvent() will not be executed.
	 * UartBase::transmitCompleteEvent() will not be suppressed.
	 *
	 * \return number of bytes already written by low-level UART driver (and read from write buffer)
	 */

	size_t stopWrite() override;

	/**
	 * \brief Function called after transmit "Transfer complete" event
	 *
	 * Called by UART-DMA transfer driver when the transfer is finished to makes thinks specific to this driver.
	 *
	 */

	void txDmaTransferComplete();

	/**
	 * \brief Function called after transmit "Transfer error" event
	 *
	 * Called by UART-DMA transfer driver when the transfer error occurs to makes thinks specific to this driver.
	 *
	 */

	void txDmaTransferError();

	/**
	 * \brief Function called after receive "Transfer complete" event
	 *
	 * Called by UART-DMA transfer driver when the transfer is finished to makes thinks specific to this driver.
	 *
	 */

	void rxDmaTransferComplete();

	/**
	 * \brief Function called after receive "Transfer error" event
	 *
	 * Called by UART-DMA transfer driver when the transfer error occurs to makes thinks specific to this driver.
	 *
	 */

	void rxDmaTransferError();

private:

	/**
	 * \return true if read operation is in progress, false otherwise
	 */

	bool isReadInProgress() const
	{
		return readLength_ != 0;
	}

	/**
	 * \return true if write operation is in progress, false otherwise
	 */

	bool isWriteInProgress() const
	{
		return writeLength_ != 0;
	}

	/// reference to ChipUartDmaTransfer object associated with this one
	ChipUartDmaTransfer& txChipUartDmaTransfer_;

	/// reference to ChipUartDmaTransfer object associated with this one
	ChipUartDmaTransfer& rxChipUartDmaTransfer_;

	/// read transfer length
	volatile size_t readLength_;

	/// write transfer length
	volatile size_t writeLength_;
};

}	// namespace chip

}	// namespace distortos

#endif	// CONFIG_CHIP_STM32_DMAV1

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTDMAV1TLOWLEVEL_HPP_
