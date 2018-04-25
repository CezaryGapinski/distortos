/**
 * \file
 * \brief ChipUartInterruptLowLevel class implementation for USARTv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipUartInterruptLowLevel.hpp"

namespace distortos
{

namespace chip
{

ChipUartInterruptLowLevel::~ChipUartInterruptLowLevel()
{

}

void ChipUartInterruptLowLevel::interruptHandler()
{
	auto& uart = parameters_.getUart();
	const auto characterLength = parameters_.getCharacterLength();
	uint32_t sr;
	uint32_t maskedSr;
	// loop while there are enabled interrupt sources waiting to be served
	while (sr = uart.SR, (maskedSr = sr & uart.CR1 & (USART_SR_RXNE | USART_SR_TXE | USART_SR_TC)) != 0)
	{
		if ((maskedSr & USART_SR_RXNE) != 0)		// read & receive errors
		{
			const uint16_t characterMask = (1 << characterLength) - 1;
			const uint16_t character = uart.DR & characterMask;
			const auto readBuffer = readBuffer_;
			auto readPosition = readPosition_;
			readBuffer[readPosition++] = character;
			if (characterLength > 8)
				readBuffer[readPosition++] = character >> 8;
			readPosition_ = readPosition;
			if ((sr & (USART_SR_FE | USART_SR_NE | USART_SR_ORE | USART_SR_PE)) != 0)
				uartBase_->receiveErrorEvent(decodeErrors(sr));
			if (readPosition == readSize_)
				uartBase_->readCompleteEvent(stopRead());
		}
		else if ((maskedSr & USART_SR_TXE) != 0)	// write
		{
			const auto writeBuffer = writeBuffer_;
			auto writePosition = writePosition_;
			const uint16_t characterLow = writeBuffer[writePosition++];
			const uint16_t characterHigh = characterLength > 8 ? writeBuffer[writePosition++] : 0;
			writePosition_ = writePosition;
			uart.DR = characterLow | characterHigh << 8;
			if (writePosition == writeSize_)
				uartBase_->writeCompleteEvent(stopWrite());
		}
		else if ((maskedSr & USART_SR_TC) != 0)		// transmit complete
		{
			parameters_.enableTcInterrupt(false);
			uartBase_->transmitCompleteEvent();
		}
	}
}

int ChipUartInterruptLowLevel::startRead(void* const buffer, const size_t size)
{
	if (buffer == nullptr || size == 0)
		return EINVAL;

	if (isStarted() == false)
		return EBADF;

	if (isReadInProgress() == true)
		return EBUSY;

	if (parameters_.getCharacterLength() > 8 && size % 2 != 0)
		return EINVAL;

	readBuffer_ = static_cast<uint8_t*>(buffer);
	readSize_ = size;
	readPosition_ = 0;
	parameters_.enableRxneInterrupt(true);
	return 0;
}

int ChipUartInterruptLowLevel::startWrite(const void* const buffer, const size_t size)
{
	if (buffer == nullptr || size == 0)
		return EINVAL;

	if (isStarted() == false)
		return EBADF;

	if (isWriteInProgress() == true)
		return EBUSY;

	if (parameters_.getCharacterLength() > 8 && size % 2 != 0)
		return EINVAL;

	writeBuffer_ = static_cast<const uint8_t*>(buffer);
	writeSize_ = size;
	writePosition_ = 0;
	parameters_.enableTcInterrupt(false);

	if ((parameters_.getUart().SR & USART_SR_TC) != 0)
		uartBase_->transmitStartEvent();

	parameters_.enableTxeInterrupt(true);
	return 0;
}

int ChipUartInterruptLowLevel::stop()
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

size_t ChipUartInterruptLowLevel::stopRead()
{
	if (isReadInProgress() == false)
		return 0;

	parameters_.enableRxneInterrupt(false);
	const auto bytesRead = readPosition_;
	readPosition_ = {};
	readSize_ = {};
	readBuffer_ = {};
	return bytesRead;
}

size_t ChipUartInterruptLowLevel::stopWrite()
{
	if (isWriteInProgress() == false)
		return 0;

	parameters_.enableTxeInterrupt(false);
	parameters_.enableTcInterrupt(true);
	const auto bytesWritten = writePosition_;
	writePosition_ = {};
	writeSize_ = {};
	writeBuffer_ = {};
	return bytesWritten;
}

}	// namespace chip

}	// namespace distortos
