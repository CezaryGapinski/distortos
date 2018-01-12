/**
 * \file
 * \brief Declarations of low-level DMA channel drivers for DMAv1 in STM32
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

/// DMA low-level driver for DMA1 channel 1
extern ChipDmaLowLevel dma1Channel1;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

/// DMA low-level driver for DMA1 channel 2
extern ChipDmaLowLevel dma1Channel2;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

/// DMA low-level driver for DMA1 channel 3
extern ChipDmaLowLevel dma1Channel3;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

/// DMA low-level driver for DMA1 channel 4
extern ChipDmaLowLevel dma1Channel4;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

/// DMA low-level driver for DMA1 channel 5
extern ChipDmaLowLevel dma1Channel5;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

/// DMA low-level driver for DMA1 channel 6
extern ChipDmaLowLevel dma1Channel6;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

/// DMA low-level driver for DMA1 channel 7
extern ChipDmaLowLevel dma1Channel7;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

/// DMA low-level driver for DMA2 channel 1
extern ChipDmaLowLevel dma2Channel1;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

/// DMA low-level driver for DMA2 channel 2
extern ChipDmaLowLevel dma2Channel2;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

/// DMA low-level driver for DMA2 channel 3
extern ChipDmaLowLevel dma2Channel3;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

/// DMA low-level driver for DMA2 channel 4
extern ChipDmaLowLevel dma2Channel4;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

/// DMA low-level driver for DMA2 channel 5
extern ChipDmaLowLevel dma2Channel5;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

/// DMA low-level driver for DMA2 channel 6
extern ChipDmaLowLevel dma2Channel6;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

/// DMA low-level driver for DMA2 channel 7
extern ChipDmaLowLevel dma2Channel7;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

#if defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE)

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local types
+---------------------------------------------------------------------------------------------------------------------*/

/// tuple of DMA channels parameters
using Parameters = std::tuple<uint8_t, uint8_t, ChipDmaLowLevel&>;

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// constexpr array with DMA module, channel and low-level driver associations
static constexpr Parameters dmaChannelsArray[] =
{
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE
		Parameters{1, 1, dma1Channel1},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE
		Parameters{1, 2, dma1Channel2},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE
		Parameters{1, 3, dma1Channel3},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE
		Parameters{1, 4, dma1Channel4},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE
		Parameters{1, 5, dma1Channel5},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE
		Parameters{1, 6, dma1Channel6},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE
		Parameters{1, 7, dma1Channel7},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE
		Parameters{2, 1, dma2Channel1},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE
		Parameters{2, 2, dma2Channel2},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE
		Parameters{2, 3, dma2Channel3},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE
		Parameters{2, 4, dma2Channel4},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE
		Parameters{2, 5, dma2Channel5},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE
		Parameters{2, 6, dma2Channel6},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE
		Parameters{2, 7, dma2Channel7},
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE
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
constexpr size_t arrayElementIndexImplementation(const T* begin, const T *actual, const T *end, const uint8_t first,
		const uint8_t second)
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
constexpr size_t arrayElementIndex(const T(&array)[N], const uint8_t first, const uint8_t second)
{
	return arrayElementIndexImplementation(array, array, array + N, first, second);
}

}

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Gets in compile time low-level DMA driver for module and channel
 *
 * \param [in] module is DMA module identifier
 * \param [in] channel is DMA channel identifier
 *
 * \return low-level DMA driver, if not found last one from dmaChannelsArray is returned
 */

constexpr ChipDmaLowLevel& getDmaLowLevel(const uint8_t module, const uint8_t channel)
{
	return std::get<2>(dmaChannelsArray[arrayElementIndex(dmaChannelsArray, module, channel)]);
}

#endif	// defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE)

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_DMAV1_INCLUDE_DISTORTOS_CHIP_DMACHANNELS_HPP_
