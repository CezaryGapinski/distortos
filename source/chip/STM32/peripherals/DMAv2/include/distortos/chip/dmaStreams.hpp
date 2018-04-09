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

#if defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE)

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local types
+---------------------------------------------------------------------------------------------------------------------*/

/// tuple of DMA streams parameters
using Parameters = std::tuple<uint8_t, uint8_t, ChipDmaLowLevel&>;

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// constexpr array with DMA module, stream and low-level driver associations
static constexpr Parameters dmaStreamsArray[] =
{
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE
		Parameters{1, 0, dma1Stream0},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE
		Parameters{1, 1, dma1Stream1},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE
		Parameters{1, 2, dma1Stream2},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE
		Parameters{1, 3, dma1Stream3},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE
		Parameters{1, 4, dma1Stream4},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE
		Parameters{1, 5, dma1Stream5},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE
		Parameters{1, 6, dma1Stream6},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE
		Parameters{1, 7, dma1Stream7},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE
		Parameters{2, 0, dma2Stream0},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE
		Parameters{2, 1, dma2Stream1},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE
		Parameters{2, 2, dma2Stream2},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE
		Parameters{2, 3, dma2Stream3},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE
		Parameters{2, 4, dma2Stream4},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE
		Parameters{2, 5, dma2Stream5},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE
		Parameters{2, 6, dma2Stream6},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE
		Parameters{2, 7, dma2Stream7},
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE
};

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Implementation of function template to get index of array of three element tuples if first and second tuple
 * element match to function arguments
 *
 * \param [in] begin is pointer to first element of array
 * \param [in] actual is pointer to actual element of array
 * \param [in] end is pointer to last element of array
 * \param [in] first is first tuple element
 * \param [in] second is second tuple element
 *
 * \return index of array or index to last element if association not found
 */

template <class T>
constexpr size_t arrayElementIndexImplementation(T* begin, T *actual, T *end, uint8_t first, uint8_t second)
{
	return std::get<0>(*actual) == first && std::get<1>(*actual) == second
			? actual - begin : actual + 1 == end ? end - actual :
			arrayElementIndexImplementation(begin, actual + 1, end, first, second);
}

/**
 * \brief Gets index of array of three element tuples if first and second tuple element match to function arguments
 *
 * \param [in] array is reference to array of three element tuples
 * \param [in] first is first tuple element
 * \param [in] second is second tuple element
 *
 * \return index of array
 */

template <class T, std::size_t N>
constexpr size_t arrayElementIndex(T(&array)[N], uint8_t first, uint8_t second)
{
	return arrayElementIndexImplementation(array, array, array + N, first, second);
}

}

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Gets in compile time low-level DMA driver for module and stream
 *
 * \param [in] module is DMA module identifier
 * \param [in] stream is DMA stream identifier
 *
 * \return low-level DMA driver, if not found last one from dmaStreamsArray will be returned
 */

constexpr ChipDmaLowLevel& getDmaLowLevel(const uint8_t module, const uint8_t stream)
{
	return std::get<2>(dmaStreamsArray[arrayElementIndex(dmaStreamsArray, module, stream)]);
}

#endif	// defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE)

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_DMASTREAMS_HPP_
