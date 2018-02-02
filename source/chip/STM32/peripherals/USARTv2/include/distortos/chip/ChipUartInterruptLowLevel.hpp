/**
 * \file
 * \brief ChipUartInterruptLowLevel class header for USARTv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTINTERRUPTLOWLEVEL_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTINTERRUPTLOWLEVEL_HPP_

#include "distortos/chip/ChipUartLowLevel.hpp"

#include "distortos/distortosConfiguration.h"

namespace distortos
{

namespace chip
{

/**
 * ChipUartInterruptLowLevel class is a low-level UART driver in interrupt mode for USARTv2 in STM32
 *
 * \ingroup devices
 */

class ChipUartInterruptLowLevel : public ChipUartLowLevel
{
public:

	/**
	 * \brief ChipUartInterruptLowLevel constructor
	 *
	 * \param [in] parameters is a reference to object with peripheral parameters
	 */

	constexpr explicit ChipUartInterruptLowLevel(const Parameters& parameters) :
			ChipUartLowLevel{parameters},
			readBuffer_{},
			readSize_{},
			readPosition_{},
			writeBuffer_{},
			writeSize_{},
			writePosition_{}
	{

	}

	/**
	 * \brief ChipUartInterruptLowLevel destructor
	 *
	 * Does nothing if driver is already stopped. If it's not, performs forced stop of operation.
	 */

	~ChipUartInterruptLowLevel() override;

	/**
	 * \brief Interrupt handler
	 *
	 * \note this must not be called by user code
	 */

	void interruptHandler();

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

private:

	/**
	 * \return true if read operation is in progress, false otherwise
	 */

	bool isReadInProgress() const
	{
		return readBuffer_ != nullptr;
	}

	/**
	 * \return true if write operation is in progress, false otherwise
	 */

	bool isWriteInProgress() const
	{
		return writeBuffer_ != nullptr;
	}

	/// buffer to which the data is being written
	uint8_t* volatile readBuffer_;

	/// size of \a readBuffer_, bytes
	volatile size_t readSize_;

	/// current position in \a readBuffer_
	volatile size_t readPosition_;

	/// buffer with data that is being transmitted
	const uint8_t* volatile writeBuffer_;

	/// size of \a writeBuffer_, bytes
	volatile size_t writeSize_;

	/// current position in \a writeBuffer_
	volatile size_t writePosition_;
};

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTINTERRUPTLOWLEVEL_HPP_
