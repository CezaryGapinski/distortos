/**
 * \file
 * \brief Definitions of low-level UART drivers for USARTv1 in STM32
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

#ifdef CONFIG_CHIP_STM32_DMAV2
#include "distortos/chip/dmaStreams.hpp"
#include "distortos/chip/ChipUartDmaV2LowLevel.hpp"
#endif	// CONFIG_CHIP_STM32_DMAV2

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART1_DMA_ENABLE

ChipUartDmaTransfer usart1DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART1_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART1_TX_DMA_STREAM)};

ChipUartDmaTransfer usart1DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART1_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART1_RX_DMA_STREAM)};

ChipUartDmaLowLevel usart1 {ChipUartLowLevel::usart1Parameters, usart1DmaTx, usart1DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_USART1_DMA_ENABLE

ChipUartInterruptLowLevel usart1 {ChipUartLowLevel::usart1Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_USART1_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART2_DMA_ENABLE

ChipUartDmaTransfer usart2DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART2_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART2_TX_DMA_STREAM)};

ChipUartDmaTransfer usart2DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART2_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART2_RX_DMA_STREAM)};

ChipUartDmaLowLevel usart2 {ChipUartLowLevel::usart2Parameters, usart2DmaTx, usart2DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_USART2_DMA_ENABLE

ChipUartInterruptLowLevel usart2 {ChipUartLowLevel::usart2Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_USART2_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART3_DMA_ENABLE

ChipUartDmaTransfer usart3DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART3_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART3_TX_DMA_STREAM)};

ChipUartDmaTransfer usart3DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART3_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART3_RX_DMA_STREAM)};

ChipUartDmaLowLevel usart3 {ChipUartLowLevel::usart3Parameters, usart3DmaTx, usart3DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_USART3_DMA_ENABLE

ChipUartInterruptLowLevel usart3 {ChipUartLowLevel::usart3Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_USART3_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART4_DMA_ENABLE

ChipUartDmaTransfer uart4DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART4_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART4_TX_DMA_STREAM)};

ChipUartDmaTransfer uart4DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART4_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART4_RX_DMA_STREAM)};

ChipUartDmaLowLevel uart4 {ChipUartLowLevel::uart4Parameters, uart4DmaTx, uart4DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_UART4_DMA_ENABLE

ChipUartInterruptLowLevel uart4 {ChipUartLowLevel::uart4Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_UART4_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART5_DMA_ENABLE

ChipUartDmaTransfer uart5DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART5_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART5_TX_DMA_STREAM)};

ChipUartDmaTransfer uart5DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART5_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART5_RX_DMA_STREAM)};

ChipUartDmaLowLevel uart5 {ChipUartLowLevel::uart5Parameters, uart5DmaTx, uart5DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_UART5_DMA_ENABLE

ChipUartInterruptLowLevel uart5 {ChipUartLowLevel::uart5Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_UART5_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART6_DMA_ENABLE

ChipUartDmaTransfer usart6DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART6_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART6_TX_DMA_STREAM)};

ChipUartDmaTransfer usart6DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_USART6_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_USART6_RX_DMA_STREAM)};

ChipUartDmaLowLevel usart6 {ChipUartLowLevel::usart6Parameters, usart6DmaTx, usart6DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_USART6_DMA_ENABLE

ChipUartInterruptLowLevel usart6 {ChipUartLowLevel::usart6Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_USART6_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART7_DMA_ENABLE

ChipUartDmaTransfer uart7DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART7_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART7_TX_DMA_STREAM)};

ChipUartDmaTransfer uart7DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART7_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART7_RX_DMA_STREAM)};

ChipUartDmaLowLevel uart7 {ChipUartLowLevel::uart7Parameters, uart7DmaTx, uart7DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_UART7_DMA_ENABLE

ChipUartInterruptLowLevel uart7 {ChipUartLowLevel::uart7Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_UART7_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART8_DMA_ENABLE

ChipUartDmaTransfer uart8DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART8_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART8_TX_DMA_STREAM)};

ChipUartDmaTransfer uart8DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART8_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART8_RX_DMA_STREAM)};

ChipUartDmaLowLevel uart8 {ChipUartLowLevel::uart8Parameters, uart8DmaTx, uart8DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_UART8_DMA_ENABLE

ChipUartInterruptLowLevel uart8 {ChipUartLowLevel::uart8Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_UART8_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART9_DMA_ENABLE

ChipUartDmaTransfer uart9DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART9_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART9_TX_DMA_STREAM)};

ChipUartDmaTransfer uart9DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART9_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART9_RX_DMA_STREAM)};

ChipUartDmaLowLevel uart9 {ChipUartLowLevel::uart9Parameters, uart9DmaTx, uart9DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_UART9_DMA_ENABLE

ChipUartInterruptLowLevel uart9 {ChipUartLowLevel::uart9Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_UART9_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART10_DMA_ENABLE

ChipUartDmaTransfer uart10DmaTx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART10_TX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART10_TX_DMA_STREAM)};

ChipUartDmaTransfer uart10DmaRx {getDmaLowLevel(CONFIG_CHIP_STM32_USARTV1_UART10_RX_DMA_MODULE,
		CONFIG_CHIP_STM32_USARTV1_UART10_RX_DMA_STREAM)};

ChipUartDmaLowLevel uart10 {ChipUartLowLevel::uart10Parameters, uart10DmaTx, uart10DmaRx};

#else	// def !CONFIG_CHIP_STM32_USARTV1_UART10_DMA_ENABLE

ChipUartInterruptLowLevel uart10 {ChipUartLowLevel::uart10Parameters};

#endif	// def !CONFIG_CHIP_STM32_USARTV1_UART10_DMA_ENABLE

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

/**
 * \brief USART1 interrupt handler
 */

extern "C" void USART1_IRQHandler()
{
	usart1.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

/**
 * \brief USART2 interrupt handler
 */

extern "C" void USART2_IRQHandler()
{
	usart2.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

/**
 * \brief USART3 interrupt handler
 */

extern "C" void USART3_IRQHandler()
{
	usart3.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

/**
 * \brief UART4 interrupt handler
 */

extern "C" void UART4_IRQHandler()
{
	uart4.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

/**
 * \brief UART5 interrupt handler
 */

extern "C" void UART5_IRQHandler()
{
	uart5.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

/**
 * \brief USART6 interrupt handler
 */

extern "C" void USART6_IRQHandler()
{
	usart6.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

/**
 * \brief UART7 interrupt handler
 */

extern "C" void UART7_IRQHandler()
{
	uart7.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

/**
 * \brief UART8 interrupt handler
 */

extern "C" void UART8_IRQHandler()
{
	uart8.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

/**
 * \brief UART9 interrupt handler
 */

extern "C" void UART9_IRQHandler()
{
	uart9.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART9_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

/**
 * \brief UART10 interrupt handler
 */

extern "C" void UART10_IRQHandler()
{
	uart10.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_USARTV1_UART10_ENABLE

}	// namespace chip

}	// namespace distortos
