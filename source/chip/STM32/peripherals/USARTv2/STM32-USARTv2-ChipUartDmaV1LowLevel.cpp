/**
 * \file
 * \brief ChipUartDmaV1LowLevel class implementation for USARTv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipUartDmaV1LowLevel.hpp"

#ifdef CONFIG_CHIP_STM32_DMAV1

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

ChipUartDmaLowLevel::~ChipUartDmaLowLevel()
{

}

void ChipUartDmaLowLevel::interruptHandler()
{
	auto& uart = parameters_.getUart();
	uint32_t isr;
	uint32_t maskedIsr;

	// loop while there are enabled interrupt sources waiting to be served
	while (isr = uart.ISR,
			(maskedIsr = (isr & ((uart.CR1 & USART_ISR_TC) |
					((uart.CR1 & USART_CR1_PEIE) ? USART_ISR_PE : 0) |
					((uart.CR3 & USART_CR3_EIE) ? (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE) : 0)))) != 0)
	{
		const auto isrErrorFlags = maskedIsr & (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE | USART_ISR_PE);
		if (isrErrorFlags != 0)	// receive errors
		{
			parameters_.enableDmaReceiver(false);

			uart.ICR = isrErrorFlags;	// clear served error flags
			uartBase_->receiveErrorEvent(decodeErrors(isr));
		}
		else if ((maskedIsr & USART_ISR_TC) != 0)		// transmit complete
		{
			parameters_.enableTcInterrupt(false);
			uartBase_->transmitCompleteEvent();
		}
	}
}

std::pair<int, uint32_t> ChipUartDmaLowLevel::start(devices::UartBase& uartBase, const uint32_t baudRate,
		const uint8_t characterLength, const devices::UartParity parity, const bool _2StopBits)
{
	{
		const auto ret = ChipUartLowLevel::start(uartBase, baudRate, characterLength, parity, _2StopBits);
		if (ret.first != 0)
			return ret;
	}

	const auto realCharacterLength = characterLength + (parity != devices::UartParity::none);
	const ChipDmaLowLevel::DataSize dataSize = (realCharacterLength == maxCharacterLength) ?
			ChipDmaLowLevel::DataSize::halfWord : ChipDmaLowLevel::DataSize::byte;

	{
		auto ret = txChipUartDmaTransfer_.start(*this, dataSize, false);
		if (ret != 0)
			return {ret, {}};

		ret = rxChipUartDmaTransfer_.start(*this, dataSize, true);
		if (ret != 0)
			return {ret, {}};
	}

	parameters_.disableDmaOnReceptionError(true);

	return {{}, {}};
}

int ChipUartDmaLowLevel::startRead(void* const buffer, const size_t size)
{
	if (buffer == nullptr || size == 0)
		return EINVAL;

	if (isStarted() == false)
		return EBADF;

	if (isReadInProgress() == true)
		return EBUSY;

	if (parameters_.getCharacterLength() > 8 && size % 2 != 0)
		return EINVAL;

	readLength_ = size;

	parameters_.enableDmaReceiver(true);
	const auto ret = rxChipUartDmaTransfer_.startTransfer(reinterpret_cast<uintptr_t>(&(parameters_.getUart().RDR)),
			reinterpret_cast<uintptr_t>(buffer), readLength_);
	if (ret != 0)
		return ret;

	parameters_.enableEInterrupt(true);
	parameters_.enablePeInterrupt(true);

	return 0;
}

int ChipUartDmaLowLevel::startWrite(const void* const buffer, const size_t size)
{
	if (buffer == nullptr || size == 0)
		return EINVAL;

	if (isStarted() == false)
		return EBADF;

	if (isWriteInProgress() == true)
		return EBUSY;

	if (parameters_.getCharacterLength() > 8 && size % 2 != 0)
		return EINVAL;

	writeLength_ = size;

	parameters_.enableDmaTransmiter(true);
	const auto ret = txChipUartDmaTransfer_.startTransfer(reinterpret_cast<uintptr_t>(buffer),
			reinterpret_cast<uintptr_t>(&(parameters_.getUart().TDR)), writeLength_);
	if (ret != 0)
		return ret;

	parameters_.enableTcInterrupt(false);

	if ((parameters_.getUart().ISR & USART_ISR_TC) != 0)
		uartBase_->transmitStartEvent();

	return 0;
}

int ChipUartDmaLowLevel::stop()
{
	if (isStarted() == false)
		return EBADF;

	if (isReadInProgress() == true || isWriteInProgress() == true)
		return EBUSY;

	parameters_.resetPeripheral();
	parameters_.enablePeripheralClock(false);
	uartBase_ = nullptr;
	return 0;
}

size_t ChipUartDmaLowLevel::stopRead()
{
	if (isReadInProgress() == false)
		return 0;

	parameters_.enableEInterrupt(false);
	parameters_.enablePeInterrupt(false);
	parameters_.enableRxneInterrupt(false);

	const auto bytesRead = rxChipUartDmaTransfer_.stopTransfer();
	readLength_ = {};
	return bytesRead;
}

size_t ChipUartDmaLowLevel::stopWrite()
{
	if (isWriteInProgress() == false)
		return 0;

	parameters_.enableTxeInterrupt(false);
	parameters_.enableTcInterrupt(true);

	const auto bytesWritten = txChipUartDmaTransfer_.stopTransfer();
	writeLength_ = {};
	return bytesWritten;
}

void ChipUartDmaLowLevel::txDmaTransferComplete()
{
	const auto bytesWritten = writeLength_;
	stopWrite();
	parameters_.enableDmaTransmiter(false);
	uartBase_->writeCompleteEvent(bytesWritten);
}

void ChipUartDmaLowLevel::txDmaTransferError()
{
	parameters_.enableDmaTransmiter(false);

	devices::UartBase::ErrorSet errorSet {};
	errorSet[devices::UartBase::transmitDmaError] = true;
	uartBase_->receiveErrorEvent(errorSet);
}

void ChipUartDmaLowLevel::rxDmaTransferComplete()
{
	const auto bytesRead = readLength_;
	stopRead();
	parameters_.enableDmaReceiver(false);
	uartBase_->readCompleteEvent(bytesRead);
}

void ChipUartDmaLowLevel::rxDmaTransferError()
{
	parameters_.enableDmaReceiver(false);

	devices::UartBase::ErrorSet errorSet {};
	errorSet[devices::UartBase::receiveDmaError] = true;
	uartBase_->receiveErrorEvent(errorSet);
}

}	// namespace chip

}	// namespace distortos

#endif	// CONFIG_CHIP_STM32_DMAV1
