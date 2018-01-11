/**
 * \file
 * \brief Declarations of low-level DMA drivers for DMAv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_DMAV1_INCLUDE_DISTORTOS_CHIP_DMACHANNELS_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_DMAV1_INCLUDE_DISTORTOS_CHIP_DMACHANNELS_HPP_

#include "distortos/chip/ChipDmaLowLevel.hpp"

#include "distortos/distortosConfiguration.h"

#include <tuple>

namespace distortos
{

namespace chip
{

class ChipDmaLowLevel;

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

/// DMA low-level driver for DMA1 Channel 1
extern ChipDmaLowLevel dma1Channel1;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

/// DMA low-level driver for DMA1 Channel 2
extern ChipDmaLowLevel dma1Channel2;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

/// DMA low-level driver for DMA1 Channel 3
extern ChipDmaLowLevel dma1Channel3;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

/// DMA low-level driver for DMA1 Channel 4
extern ChipDmaLowLevel dma1Channel4;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

/// DMA low-level driver for DMA1 Channel 5
extern ChipDmaLowLevel dma1Channel5;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

/// DMA low-level driver for DMA1 Channel 6
extern ChipDmaLowLevel dma1Channel6;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

/// DMA low-level driver for DMA1 Channel 7
extern ChipDmaLowLevel dma1Channel7;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

/// DMA low-level driver for DMA2 Channel 1
extern ChipDmaLowLevel dma2Channel1;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

/// DMA low-level driver for DMA2 Channel 2
extern ChipDmaLowLevel dma2Channel2;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

/// DMA low-level driver for DMA2 Channel 3
extern ChipDmaLowLevel dma2Channel3;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

/// DMA low-level driver for DMA2 Channel 4
extern ChipDmaLowLevel dma2Channel4;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

/// DMA low-level driver for DMA2 Channel 5
extern ChipDmaLowLevel dma2Channel5;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

/// DMA low-level driver for DMA2 Channel 6
extern ChipDmaLowLevel dma2Channel6;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

/// DMA low-level driver for DMA2 Channel 7
extern ChipDmaLowLevel dma2Channel7;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_DMAV1_INCLUDE_DISTORTOS_CHIP_DMACHANNELS_HPP_
