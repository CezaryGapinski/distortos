/**
 * \file
 * \brief Declarations of low-level DMA drivers for DMAv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_DMASTREAMS_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_DMASTREAMS_HPP_

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

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

/// DMA low-level driver for DMA1 Stream 0
extern ChipDmaLowLevel dma1Stream0;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

/// DMA low-level driver for DMA1 Stream 1
extern ChipDmaLowLevel dma1Stream1;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

/// DMA low-level driver for DMA1 Stream 2
extern ChipDmaLowLevel dma1Stream2;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

/// DMA low-level driver for DMA1 Stream 3
extern ChipDmaLowLevel dma1Stream3;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

/// DMA low-level driver for DMA1 Stream 4
extern ChipDmaLowLevel dma1Stream4;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

/// DMA low-level driver for DMA1 Stream 5
extern ChipDmaLowLevel dma1Stream5;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

/// DMA low-level driver for DMA1 Stream 6
extern ChipDmaLowLevel dma1Stream6;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

/// DMA low-level driver for DMA1 Stream 7
extern ChipDmaLowLevel dma1Stream7;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

/// DMA low-level driver for DMA2 Stream 0
extern ChipDmaLowLevel dma2Stream0;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

/// DMA low-level driver for DMA2 Stream 1
extern ChipDmaLowLevel dma2Stream1;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

/// DMA low-level driver for DMA2 Stream 2
extern ChipDmaLowLevel dma2Stream2;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

/// DMA low-level driver for DMA2 Stream 3
extern ChipDmaLowLevel dma2Stream3;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

/// DMA low-level driver for DMA2 Stream 4
extern ChipDmaLowLevel dma2Stream4;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

/// DMA low-level driver for DMA2 Stream 5
extern ChipDmaLowLevel dma2Stream5;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

/// DMA low-level driver for DMA2 Stream 6
extern ChipDmaLowLevel dma2Stream6;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

/// DMA low-level driver for DMA2 Stream 7
extern ChipDmaLowLevel dma2Stream7;

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_DMASTREAMS_HPP_
