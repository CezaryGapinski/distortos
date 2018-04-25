/**
 * \file
 * \brief Declarations of low-level UART drivers for USARTv1 in STM32
 *
 * \author Copyright (C) 2016-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_USARTV1_INCLUDE_DISTORTOS_CHIP_UARTS_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_USARTV1_INCLUDE_DISTORTOS_CHIP_UARTS_HPP_

#include "distortos/distortosConfiguration.h"

namespace distortos
{

namespace chip
{

class ChipUartInterruptLowLevel;

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

/// UART low-level driver for USART1
extern ChipUartInterruptLowLevel usart1;

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

/// UART low-level driver for USART2
extern ChipUartInterruptLowLevel usart2;

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

/// UART low-level driver for USART3
extern ChipUartInterruptLowLevel usart3;

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

/// UART low-level driver for UART4
extern ChipUartInterruptLowLevel uart4;

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

/// UART low-level driver for UART5
extern ChipUartInterruptLowLevel uart5;

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

/// UART low-level driver for USART6
extern ChipUartInterruptLowLevel usart6;

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

/// UART low-level driver for UART7
extern ChipUartInterruptLowLevel uart7;

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

/// UART low-level driver for UART8
extern ChipUartInterruptLowLevel uart8;

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

/// UART low-level driver for UART9
extern ChipUartInterruptLowLevel uart9;

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

/// UART low-level driver for UART10
extern ChipUartInterruptLowLevel uart10;

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_USARTV1_INCLUDE_DISTORTOS_CHIP_UARTS_HPP_
