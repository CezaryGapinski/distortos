/**
 * \file
 * \brief Definitions of low-level DMA Stream drivers for DMAv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipDmaLowLevel.hpp"

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

ChipDmaLowLevel dma1Stream0 {ChipDmaLowLevel::dma1Stream0Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

ChipDmaLowLevel dma1Stream1 {ChipDmaLowLevel::dma1Stream1Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

ChipDmaLowLevel dma1Stream2 {ChipDmaLowLevel::dma1Stream2Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

ChipDmaLowLevel dma1Stream3 {ChipDmaLowLevel::dma1Stream3Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

ChipDmaLowLevel dma1Stream4 {ChipDmaLowLevel::dma1Stream4Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

ChipDmaLowLevel dma1Stream5 {ChipDmaLowLevel::dma1Stream5Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

ChipDmaLowLevel dma1Stream6 {ChipDmaLowLevel::dma1Stream6Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

ChipDmaLowLevel dma1Stream7 {ChipDmaLowLevel::dma1Stream7Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

ChipDmaLowLevel dma2Stream0 {ChipDmaLowLevel::dma2Stream0Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

ChipDmaLowLevel dma2Stream1 {ChipDmaLowLevel::dma2Stream1Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

ChipDmaLowLevel dma2Stream2 {ChipDmaLowLevel::dma2Stream2Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

ChipDmaLowLevel dma2Stream3 {ChipDmaLowLevel::dma2Stream3Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

ChipDmaLowLevel dma2Stream4 {ChipDmaLowLevel::dma2Stream4Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

ChipDmaLowLevel dma2Stream5 {ChipDmaLowLevel::dma2Stream5Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

ChipDmaLowLevel dma2Stream6 {ChipDmaLowLevel::dma2Stream6Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

ChipDmaLowLevel dma2Stream7 {ChipDmaLowLevel::dma2Stream7Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

/**
 * \brief DMA1 Stream 0 interrupt handler
 */

extern "C" void DMA1_Stream0_IRQHandler()
{
	dma1Stream0.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

/**
 * \brief DMA1 Stream 1 interrupt handler
 */

extern "C" void DMA1_Stream1_IRQHandler()
{
	dma1Stream1.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

/**
 * \brief DMA1 Stream 2 interrupt handler
 */

extern "C" void DMA1_Stream2_IRQHandler()
{
	dma1Stream2.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

/**
 * \brief DMA1 Stream 3 interrupt handler
 */

extern "C" void DMA1_Stream3_IRQHandler()
{
	dma1Stream3.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

/**
 * \brief DMA1 Stream 4 interrupt handler
 */

extern "C" void DMA1_Stream4_IRQHandler()
{
	dma1Stream4.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

/**
 * \brief DMA1 Stream 5 interrupt handler
 */

extern "C" void DMA1_Stream5_IRQHandler()
{
	dma1Stream5.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

/**
 * \brief DMA1 Stream 6 interrupt handler
 */

extern "C" void DMA1_Stream6_IRQHandler()
{
	dma1Stream6.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

/**
 * \brief DMA1 Stream 7 interrupt handler
 */

extern "C" void DMA1_Stream7_IRQHandler()
{
	dma1Stream7.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

/**
 * \brief DMA2 Stream 0 interrupt handler
 */

extern "C" void DMA2_Stream0_IRQHandler()
{
	dma2Stream0.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

/**
 * \brief DMA2 Stream 1 interrupt handler
 */

extern "C" void DMA2_Stream1_IRQHandler()
{
	dma2Stream1.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

/**
 * \brief DMA2 Stream 2 interrupt handler
 */

extern "C" void DMA2_Stream2_IRQHandler()
{
	dma2Stream2.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

/**
 * \brief DMA2 Stream 3 interrupt handler
 */

extern "C" void DMA2_Stream3_IRQHandler()
{
	dma2Stream3.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

/**
 * \brief DMA2 Stream 4 interrupt handler
 */

extern "C" void DMA2_Stream4_IRQHandler()
{
	dma2Stream4.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

/**
 * \brief DMA2 Stream 5 interrupt handler
 */

extern "C" void DMA2_Stream5_IRQHandler()
{
	dma2Stream5.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

/**
 * \brief DMA2 Stream 6 interrupt handler
 */

extern "C" void DMA2_Stream6_IRQHandler()
{
	dma2Stream6.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

/**
 * \brief DMA2 Stream 7 interrupt handler
 */

extern "C" void DMA2_Stream7_IRQHandler()
{
	dma2Stream7.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

}	// namespace chip

}	// namespace distortos
