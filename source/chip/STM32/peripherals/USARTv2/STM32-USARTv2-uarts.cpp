/**
 * \file
 * \brief Definitions of low-level UART drivers for USARTv2 in STM32
 *
 * \author Copyright (C) 2016-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/uarts.hpp"
#include "distortos/chip/ChipUartInterruptLowLevel.hpp"

#ifdef CONFIG_CHIP_STM32_DMAV1
#include "distortos/chip/dmaChannels.hpp"
#include "distortos/chip/ChipUartDmaV1LowLevel.hpp"
#endif	// CONFIG_CHIP_STM32_DMAV1

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_DMA_ENABLE

ChipUartDmaTransfer usart1DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART1_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART1_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart1DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART1_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART1_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart1 {ChipUartLowLevel::usart1Parameters, usart1DmaTx, usart1DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART1_DMA_ENABLE

ChipUartInterruptLowLevel usart1 {ChipUartLowLevel::usart1Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART1_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_DMA_ENABLE

ChipUartDmaTransfer usart2DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART2_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART2_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart2DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART2_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART2_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart2 {ChipUartLowLevel::usart2Parameters, usart2DmaTx, usart2DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART2_DMA_ENABLE

ChipUartInterruptLowLevel usart2 {ChipUartLowLevel::usart2Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART2_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_DMA_ENABLE

ChipUartDmaTransfer usart3DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART3_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART3_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart3DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART3_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART3_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart3 {ChipUartLowLevel::usart3Parameters, usart3DmaTx, usart3DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART3_DMA_ENABLE

ChipUartInterruptLowLevel usart3 {ChipUartLowLevel::usart3Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART3_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_DMA_ENABLE

ChipUartDmaTransfer uart4DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART4_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART4_TX_DMA_CHANNEL)};

ChipUartDmaTransfer uart4DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART4_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART4_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel uart4 {ChipUartLowLevel::uart4Parameters, uart4DmaTx, uart4DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART4_DMA_ENABLE

ChipUartInterruptLowLevel uart4 {ChipUartLowLevel::uart4Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART4_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_DMA_ENABLE

ChipUartDmaTransfer usart4DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART4_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART4_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart4DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART4_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART4_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart4 {ChipUartLowLevel::usart4Parameters, usart4DmaTx, usart4DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART4_DMA_ENABLE

ChipUartInterruptLowLevel usart4 {ChipUartLowLevel::usart4Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART4_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_DMA_ENABLE

ChipUartDmaTransfer uart5DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART5_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART5_TX_DMA_CHANNEL)};

ChipUartDmaTransfer uart5DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART5_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART5_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel uart5 {ChipUartLowLevel::uart5Parameters, uart5DmaTx, uart5DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART5_DMA_ENABLE

ChipUartInterruptLowLevel uart5 {ChipUartLowLevel::uart5Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART5_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_DMA_ENABLE

ChipUartDmaTransfer usart5DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART5_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART5_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart5DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART5_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART5_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart5 {ChipUartLowLevel::usart5Parameters, usart5DmaTx, usart5DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART5_DMA_ENABLE

ChipUartInterruptLowLevel usart5 {ChipUartLowLevel::usart5Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART5_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_DMA_ENABLE

ChipUartDmaTransfer usart6DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART6_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART6_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart6DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART6_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART6_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart6 {ChipUartLowLevel::usart6Parameters, usart6DmaTx, usart6DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART6_DMA_ENABLE

ChipUartInterruptLowLevel usart6 {ChipUartLowLevel::usart6Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART6_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_DMA_ENABLE

ChipUartDmaTransfer uart7DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART7_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART7_TX_DMA_CHANNEL)};

ChipUartDmaTransfer uart7DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART7_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART7_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel uart7 {ChipUartLowLevel::uart7Parameters, uart7DmaTx, uart7DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART7_DMA_ENABLE

ChipUartInterruptLowLevel uart7 {ChipUartLowLevel::uart7Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART7_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_DMA_ENABLE

ChipUartDmaTransfer usart7DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART7_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART7_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart7DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART7_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART7_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart7 {ChipUartLowLevel::usart7Parameters, usart7DmaTx, usart7DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART7_DMA_ENABLE

ChipUartInterruptLowLevel usart7 {ChipUartLowLevel::usart7Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART7_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_DMA_ENABLE

ChipUartDmaTransfer uart8DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART8_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART8_TX_DMA_CHANNEL)};

ChipUartDmaTransfer uart8DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_UART8_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_UART8_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel uart8 {ChipUartLowLevel::uart8Parameters, uart8DmaTx, uart8DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_UART8_DMA_ENABLE

ChipUartInterruptLowLevel uart8 {ChipUartLowLevel::uart8Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_UART8_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_DMA_ENABLE

ChipUartDmaTransfer usart8DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART8_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART8_TX_DMA_CHANNEL)};

ChipUartDmaTransfer usart8DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV2_USART8_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV2_USART8_RX_DMA_CHANNEL)};

ChipUartDmaLowLevel usart8 {ChipUartLowLevel::usart8Parameters, usart8DmaTx, usart8DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV2_USART8_DMA_ENABLE

ChipUartInterruptLowLevel usart8 {ChipUartLowLevel::usart8Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV2_USART8_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

/**
 * \brief USART1 interrupt handler
 */

extern "C" void USART1_IRQHandler()
{
	usart1.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

/**
 * \brief USART2 interrupt handler
 */

extern "C" void USART2_IRQHandler()
{
	usart2.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#if defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART8_COMBINED_INTERRUPT)

#if defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || \
		defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE) || \
		defined(CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE)

/**
 * \brief USART3 - USART8 interrupt handler
 */

extern "C" void USART3_8_IRQHandler()
{
#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE
	usart3.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
	usart4.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
	usart5.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE
	usart6.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE
	usart7.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE
	usart8.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE
}

#endif	// defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE)

#elif defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART6_COMBINED_INTERRUPT)

#if defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || \
		defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE)

/**
 * \brief USART3 - USART6 interrupt handler
 */

extern "C" void USART3_6_IRQHandler()
{
#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE
	usart3.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
	usart4.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
	usart5.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE
	usart6.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE
}

#endif	// defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE)

#else	// !defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART8_COMBINED_INTERRUPT) &&
		// !defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART6_COMBINED_INTERRUPT)

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

/**
 * \brief USART3 interrupt handler
 */

extern "C" void USART3_IRQHandler()
{
	usart3.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#if defined(CONFIG_CHIP_STM32_USARTV2_USART4_USART5_COMBINED_INTERRUPT)

#if defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE)

/**
 * \brief USART4 - USART5 interrupt handler
 */

extern "C" void USART4_5_IRQHandler()
{
#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
	usart4.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
	usart5.interruptHandler();
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
}

#endif	// defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE)

#else	// !defined(CONFIG_CHIP_STM32_USARTV2_USART4_USART5_COMBINED_INTERRUPT)

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

/**
 * \brief USART4 interrupt handler
 */

extern "C" void USART4_IRQHandler()
{
	usart4.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

/**
 * \brief USART5 interrupt handler
 */

extern "C" void USART5_IRQHandler()
{
	usart5.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#endif	// !defined(CONFIG_CHIP_STM32_USARTV2_USART4_USART5_COMBINED_INTERRUPT)

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

/**
 * \brief UART4 interrupt handler
 */

extern "C" void UART4_IRQHandler()
{
	uart4.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

/**
 * \brief UART5 interrupt handler
 */

extern "C" void UART5_IRQHandler()
{
	uart5.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

/**
 * \brief USART6 interrupt handler
 */

extern "C" void USART6_IRQHandler()
{
	usart6.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

/**
 * \brief UART7 interrupt handler
 */

extern "C" void UART7_IRQHandler()
{
	uart7.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

/**
 * \brief USART7 interrupt handler
 */

extern "C" void USART7_IRQHandler()
{
	usart7.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

/**
 * \brief UART8 interrupt handler
 */

extern "C" void UART8_IRQHandler()
{
	uart8.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

/**
 * \brief USART8 interrupt handler
 */

extern "C" void USART8_IRQHandler()
{
	usart8.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

#endif	// !defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART8_COMBINED_INTERRUPT) &&
		// !defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART6_COMBINED_INTERRUPT)

}	// namespace chip

}	// namespace distortos
