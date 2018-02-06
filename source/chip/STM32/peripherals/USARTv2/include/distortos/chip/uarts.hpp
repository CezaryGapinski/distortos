/**
 * \file
 * \brief Declarations of low-level UART drivers for USARTv2 in STM32
 *
 * \author Copyright (C) 2016-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_UARTS_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_UARTS_HPP_

#include "distortos/distortosConfiguration.h"

namespace distortos
{

namespace chip
{

class ChipUartInterruptLowLevel;
class ChipUartDmaLowLevel;

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_DMA_ENABLE

/// UART low-level driver in DMA mode for USART1
extern ChipUartDmaLowLevel usart1;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART1_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART1
extern ChipUartInterruptLowLevel usart1;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART1_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_DMA_ENABLE

/// UART low-level driver in DMA mode for USART2
extern ChipUartDmaLowLevel usart2;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART2_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART2
extern ChipUartInterruptLowLevel usart2;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART2_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_DMA_ENABLE

/// UART low-level driver in DMA mode for USART3
extern ChipUartDmaLowLevel usart3;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART3_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART3
extern ChipUartInterruptLowLevel usart3;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART3_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_DMA_ENABLE

/// UART low-level driver in DMA mode for UART4
extern ChipUartDmaLowLevel uart4;

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART4_DMA_ENABLE

/// UART low-level driver in interrupt mode for UART4
extern ChipUartInterruptLowLevel uart4;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART4_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_DMA_ENABLE

/// UART low-level driver in DMA mode for USART4
extern ChipUartDmaLowLevel usart4;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART4_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART4
extern ChipUartInterruptLowLevel usart4;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART4_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_DMA_ENABLE

/// UART low-level driver in DMA mode for UART5
extern ChipUartDmaLowLevel uart5;

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART5_DMA_ENABLE

/// UART low-level driver in interrupt mode for UART5
extern ChipUartInterruptLowLevel uart5;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART5_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_DMA_ENABLE

/// UART low-level driver in DMA mode for USART5
extern ChipUartDmaLowLevel usart5;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART5_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART5
extern ChipUartInterruptLowLevel usart5;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART5_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_DMA_ENABLE

/// UART low-level driver in DMA mode for USART6
extern ChipUartDmaLowLevel usart6;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART6_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART6
extern ChipUartInterruptLowLevel usart6;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART6_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_DMA_ENABLE

/// UART low-level driver in DMA mode for UART7
extern ChipUartDmaLowLevel uart7;

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART7_DMA_ENABLE

/// UART low-level driver in interrupt mode for UART7
extern ChipUartInterruptLowLevel uart7;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART7_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_DMA_ENABLE

/// UART low-level driver in DMA mode for USART7
extern ChipUartDmaLowLevel usart7;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART7_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART7
extern ChipUartInterruptLowLevel usart7;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART7_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_DMA_ENABLE

/// UART low-level driver in DMA mode for UART8
extern ChipUartDmaLowLevel uart8;

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART8_DMA_ENABLE

/// UART low-level driver in interrupt mode for UART8
extern ChipUartInterruptLowLevel uart8;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART8_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_DMA_ENABLE

/// UART low-level driver in DMA mode for USART8
extern ChipUartDmaLowLevel usart8;

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART8_DMA_ENABLE

/// UART low-level driver in interrupt mode for USART8
extern ChipUartInterruptLowLevel usart8;

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART8_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_UARTS_HPP_
