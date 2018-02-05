/**
 * \file
 * \brief ChipUartLowLevel class implementation for USARTv2 in STM32
 *
 * \author Copyright (C) 2016-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipUartLowLevel.hpp"

#ifndef DISTORTOS_BITBANDING_SUPPORTED

#include "distortos/InterruptMaskingLock.hpp"

#endif	// !def DISTORTOS_BITBANDING_SUPPORTED

#include <cerrno>

#if !defined(USART_CR1_M0)
#define USART_CR1_M0						USART_CR1_M
#endif	// !defined(USART_CR1_M0)
#if !defined(USART_CR1_M0_Pos)
#define USART_CR1_M0_Pos					__builtin_ctzl(USART_CR1_M0)
#endif	// !defined(USART_CR1_M0_Pos)
#if defined(CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT) && !defined(USART_CR1_M1_Pos)
#define USART_CR1_M1_Pos					__builtin_ctzl(USART_CR1_M1)
#endif	// defined(CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT) && !defined(USART_CR1_M1_Pos)

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| public static objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef DISTORTOS_BITBANDING_SUPPORTED

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart1Parameters {USART1_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB2ENR, USART1EN), STM32_BITBAND_ADDRESS(RCC, APB2RSTR, USART1RST)};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart2Parameters {USART2_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR1, USART2EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR1, USART2RST)};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart3Parameters {USART3_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR1, USART3EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR1, USART3RST)};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::uart4Parameters {UART4_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR1, UART4EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR1, UART4RST)};
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::uart5Parameters {UART5_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR1, UART5EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR1, UART5RST)};
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#else	// !def DISTORTOS_BITBANDING_SUPPORTED

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart1Parameters {USART1_BASE, offsetof(RCC_TypeDef, APB2ENR),
		RCC_APB2ENR_USART1EN, offsetof(RCC_TypeDef, APB2RSTR), RCC_APB2RSTR_USART1RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart2Parameters {USART2_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_USART2EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_USART2RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart3Parameters {USART3_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_USART3EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_USART3RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::uart4Parameters {UART4_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_UART4EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_UART4RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart4Parameters {USART4_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_USART4EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_USART4RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::uart5Parameters {UART5_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_UART5EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_UART5RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart5Parameters {USART5_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_USART5EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_USART5RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart6Parameters {USART6_BASE, offsetof(RCC_TypeDef, APB2ENR),
		RCC_APB2ENR_USART6EN, offsetof(RCC_TypeDef, APB2RSTR), RCC_APB2RSTR_USART6RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::uart7Parameters {UART7_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_UART7EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_UART7RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart7Parameters {USART7_BASE, offsetof(RCC_TypeDef, APB2ENR),
		RCC_APB2ENR_USART7EN, offsetof(RCC_TypeDef, APB2RSTR), RCC_APB2RSTR_USART7RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::uart8Parameters {UART8_BASE, offsetof(RCC_TypeDef, APB1ENR),
		RCC_APB1ENR_UART8EN, offsetof(RCC_TypeDef, APB1RSTR), RCC_APB1RSTR_UART8RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE
const ChipUartLowLevel::Parameters ChipUartLowLevel::usart8Parameters {USART8_BASE, offsetof(RCC_TypeDef, APB2ENR),
		RCC_APB2ENR_USART8EN, offsetof(RCC_TypeDef, APB2RSTR), RCC_APB2RSTR_USART8RST};
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

#endif	// !def DISTORTOS_BITBANDING_SUPPORTED

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

void ChipUartLowLevel::Parameters::enablePeripheralClock(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(rccEnBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& rccEn = *reinterpret_cast<volatile uint32_t*>(RCC_BASE + rccEnOffset_);
	const InterruptMaskingLock interruptMaskingLock;
	rccEn = (rccEn & ~rccEnBitmask_) | (enable == true ? rccEnBitmask_ : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::enableRxneInterrupt(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(rxneieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR1 = (uart.CR1 & ~USART_CR1_RXNEIE) | (enable == true ? USART_CR1_RXNEIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::enableTcInterrupt(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(tcieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR1 = (uart.CR1 & ~USART_CR1_TCIE) | (enable == true ? USART_CR1_TCIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::resetPeripheral() const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(rccRstBbAddress_) = 1;
	*reinterpret_cast<volatile unsigned long*>(rccRstBbAddress_) = 0;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& rccRst = *reinterpret_cast<volatile uint32_t*>(RCC_BASE + rccRstOffset_);
	const InterruptMaskingLock interruptMaskingLock;
	rccRst |= rccRstBitmask_;
	rccRst &= ~rccRstBitmask_;
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::enableTxeInterrupt(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(txeieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR1 = (uart.CR1 & ~USART_CR1_TXEIE) | (enable == true ? USART_CR1_TXEIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::enablePeInterrupt(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(peieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR1 = (uart.CR1 & ~USART_CR1_PEIE) | (enable == true ? USART_CR1_PEIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::enableEInterrupt(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(eieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR3 = (uart.CR3 & ~USART_CR3_EIE) | (enable == true ? USART_CR3_EIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::disableDmaOnReceptionError(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(ddreBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR3 = (uart.CR3 & ~USART_CR3_DDRE) | (enable == true ? USART_CR3_DDRE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
}

void ChipUartLowLevel::Parameters::enableDmaTransmiter(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(dmatBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR3 = (uart.CR3 & ~USART_CR3_DMAT) | (enable == true ? USART_CR3_DMAT : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORT
}

void ChipUartLowLevel::Parameters::enableDmaReceiver(const bool enable) const
{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
	*reinterpret_cast<volatile unsigned long*>(dmarBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
	auto& uart = getUart();
	const InterruptMaskingLock interruptMaskingLock;
	uart.CR3 = (uart.CR3 & ~USART_CR3_DMAR) | (enable == true ? USART_CR3_DMAR : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORT
}

uint8_t ChipUartLowLevel::Parameters::getCharacterLength() const
{
	const auto cr1 = getUart().CR1;
	const auto realCharacterLength =
#ifdef CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT
			(cr1 & USART_CR1_M1) != 0 ? 7 :
#endif	// def CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT
			(cr1 & USART_CR1_M0) != 0 ? 9 : 8;
	const auto parityControlEnabled = (cr1 & USART_CR1_PCE) != 0;
	return realCharacterLength - parityControlEnabled;
}

bool ChipUartLowLevel::Parameters::isDmaTrasmitterEnabled() const
{
	return getUart().CR3 & USART_CR3_DMAT;
}

bool ChipUartLowLevel::Parameters::isDmaReceiverEnabled() const
{
	return getUart().CR3 & USART_CR3_DMAR;
}


ChipUartLowLevel::~ChipUartLowLevel()
{
	if (isStarted() == false)
		return;

	parameters_.resetPeripheral();
	parameters_.enablePeripheralClock(false);
}

std::pair<int, uint32_t> ChipUartLowLevel::start(devices::UartBase& uartBase, const uint32_t baudRate,
		const uint8_t characterLength, const devices::UartParity parity, const bool _2StopBits)
{
	if (isStarted() == true)
		return {EBADF, {}};

	const auto peripheralFrequency = parameters_.getPeripheralFrequency();
	const auto divider = (peripheralFrequency + baudRate / 2) / baudRate;
	const auto over8 = divider < 16;
	const auto mantissa = divider / (over8 == false ? 16 : 8);
	const auto fraction = divider % (over8 == false ? 16 : 8);

	if (mantissa == 0 || mantissa > (USART_BRR_DIV_MANTISSA >> USART_BRR_DIV_MANTISSA_Pos))
		return {EINVAL, {}};

	const auto realCharacterLength = characterLength + (parity != devices::UartParity::none);
	if (realCharacterLength < minCharacterLength + 1 || realCharacterLength > maxCharacterLength)
		return {EINVAL, {}};

	parameters_.enablePeripheralClock(true);
	parameters_.resetPeripheral();

	uartBase_ = &uartBase;
	auto& uart = parameters_.getUart();
	uart.BRR = mantissa << USART_BRR_DIV_MANTISSA_Pos | fraction << USART_BRR_DIV_FRACTION_Pos;
	uart.CR2 = _2StopBits << (USART_CR2_STOP_Pos + 1);
	uart.CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | over8 << USART_CR1_OVER8_Pos |
			(realCharacterLength == maxCharacterLength) << USART_CR1_M0_Pos |
#ifdef CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT
			(realCharacterLength == minCharacterLength + 1) << USART_CR1_M1_Pos |
#endif	// def CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT
			(parity != devices::UartParity::none) << USART_CR1_PCE_Pos |
			(parity == devices::UartParity::odd) << USART_CR1_PS_Pos;
	return {{}, peripheralFrequency / divider};
}

devices::UartBase::ErrorSet decodeErrors(const uint32_t isr)
{
	devices::UartBase::ErrorSet errorSet {};
	errorSet[devices::UartBase::framingError] = (isr & USART_ISR_FE) != 0;
	errorSet[devices::UartBase::noiseError] = (isr & USART_ISR_NE) != 0;
	errorSet[devices::UartBase::overrunError] = (isr & USART_ISR_ORE) != 0;
	errorSet[devices::UartBase::parityError] = (isr & USART_ISR_PE) != 0;
	return errorSet;
}

}	// namespace chip

}	// namespace distortos
