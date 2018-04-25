/**
 * \file
 * \brief ChipUartLowLevel class implementation for USARTv1 in STM32
 *
 * \author Copyright (C) 2016-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipUartLowLevel.hpp"

#include <cerrno>

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| public static objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::usart1Parameters {USART1_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB2ENR, USART1EN), STM32_BITBAND_ADDRESS(RCC, APB2RSTR, USART1RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::usart2Parameters {USART2_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR, USART2EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR, USART2RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::usart3Parameters {USART3_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR, USART3EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR, USART3RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::uart4Parameters {UART4_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR, UART4EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR, UART4RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::uart5Parameters {UART5_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR, UART5EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR, UART5RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::usart6Parameters {USART6_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB2ENR, USART6EN), STM32_BITBAND_ADDRESS(RCC, APB2RSTR, USART6RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::uart7Parameters {UART7_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR, UART7EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR, UART7RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::uart8Parameters {UART8_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB1ENR, UART8EN), STM32_BITBAND_ADDRESS(RCC, APB1RSTR, UART8RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::uart9Parameters {UART9_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB2ENR, UART9EN), STM32_BITBAND_ADDRESS(RCC, APB2RSTR, UART9RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

const ChipUartLowLevel::Parameters ChipUartLowLevel::uart10Parameters {UART10_BASE,
		STM32_BITBAND_ADDRESS(RCC, APB2ENR, UART10EN), STM32_BITBAND_ADDRESS(RCC, APB2RSTR, UART10RST)};

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

uint8_t ChipUartLowLevel::Parameters::getCharacterLength() const
{
	const auto cr1 = getUart().CR1;
	const uint8_t realCharacterLength = 8 + ((cr1 & USART_CR1_M) != 0);
	const auto parityControlEnabled = (cr1 & USART_CR1_PCE) != 0;
	return realCharacterLength - parityControlEnabled;
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
#ifdef CONFIG_CHIP_STM32_USARTV1_HAS_CR1_OVER8_BIT
	const auto over8 = divider < 16;
#else	// !def CONFIG_CHIP_STM32_USARTV1_HAS_CR1_OVER8_BIT
	constexpr bool over8 {false};
#endif	// !def CONFIG_CHIP_STM32_USARTV1_HAS_CR1_OVER8_BIT
	const auto mantissa = divider / (over8 == false ? 16 : 8);
	const auto fraction = divider % (over8 == false ? 16 : 8);

	if (mantissa == 0 || mantissa > (USART_BRR_DIV_Mantissa >> USART_BRR_DIV_Mantissa_Pos))
		return {EINVAL, {}};

	const auto realCharacterLength = characterLength + (parity != devices::UartParity::none);
	if (realCharacterLength < minCharacterLength + 1 || realCharacterLength > maxCharacterLength)
		return {EINVAL, {}};

	parameters_.enablePeripheralClock(true);
	parameters_.resetPeripheral();

	uartBase_ = &uartBase;
	auto& uart = parameters_.getUart();
	uart.BRR = mantissa << USART_BRR_DIV_Mantissa_Pos | fraction << USART_BRR_DIV_Fraction_Pos;
	uart.CR2 = _2StopBits << (USART_CR2_STOP_Pos + 1);
	uart.CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE |
#ifdef CONFIG_CHIP_STM32_USARTV1_HAS_CR1_OVER8_BIT
			over8 << USART_CR1_OVER8_Pos |
#endif	// def CONFIG_CHIP_STM32_USARTV1_HAS_CR1_OVER8_BIT
			(realCharacterLength == maxCharacterLength) << USART_CR1_M_Pos |
			(parity != devices::UartParity::none) << USART_CR1_PCE_Pos |
			(parity == devices::UartParity::odd) << USART_CR1_PS_Pos;
	return {{}, peripheralFrequency / divider};
}

devices::UartBase::ErrorSet decodeErrors(const uint32_t sr)
{
	devices::UartBase::ErrorSet errorSet {};
	errorSet[devices::UartBase::framingError] = (sr & USART_SR_FE) != 0;
	errorSet[devices::UartBase::noiseError] = (sr & USART_SR_NE) != 0;
	errorSet[devices::UartBase::overrunError] = (sr & USART_SR_ORE) != 0;
	errorSet[devices::UartBase::parityError] = (sr & USART_SR_PE) != 0;
	return errorSet;
}

}	// namespace chip

}	// namespace distortos
