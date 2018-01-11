/**
 * \file
 * \brief Definitions of low-level DMA channel drivers for DMAv1 in STM32
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

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

ChipDmaLowLevel dma1Channel1 {ChipDmaLowLevel::dma1Channel1Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

ChipDmaLowLevel dma1Channel2 {ChipDmaLowLevel::dma1Channel2Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

ChipDmaLowLevel dma1Channel3 {ChipDmaLowLevel::dma1Channel3Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

ChipDmaLowLevel dma1Channel4 {ChipDmaLowLevel::dma1Channel4Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

ChipDmaLowLevel dma1Channel5 {ChipDmaLowLevel::dma1Channel5Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

ChipDmaLowLevel dma1Channel6 {ChipDmaLowLevel::dma1Channel6Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

ChipDmaLowLevel dma1Channel7 {ChipDmaLowLevel::dma1Channel7Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

ChipDmaLowLevel dma2Channel1 {ChipDmaLowLevel::dma2Channel1Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

ChipDmaLowLevel dma2Channel2 {ChipDmaLowLevel::dma2Channel2Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

ChipDmaLowLevel dma2Channel3 {ChipDmaLowLevel::dma2Channel3Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

ChipDmaLowLevel dma2Channel4 {ChipDmaLowLevel::dma2Channel4Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

ChipDmaLowLevel dma2Channel5 {ChipDmaLowLevel::dma2Channel5Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

ChipDmaLowLevel dma2Channel6 {ChipDmaLowLevel::dma2Channel6Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

ChipDmaLowLevel dma2Channel7 {ChipDmaLowLevel::dma2Channel7Parameters};

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

}	// namespace chip

}	// namespace distortos
