/**
 * \file
 * \brief Low-level peripheral initializer for DMAv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/CMSIS-proxy.h"

#include "distortos/BIND_LOW_LEVEL_INITIALIZER.h"

namespace distortos
{

namespace chip
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// priority of DMA interrupts
#if defined(CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI)
constexpr uint8_t interruptPriority {CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI};
#else	// !defined(CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI)
constexpr uint8_t interruptPriority {};
#endif	// !defined(CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI)

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Low-level peripheral initializer for DMAv1 in STM32
 *
 * This function is called before constructors for global and static objects via BIND_LOW_LEVEL_INITIALIZER().
 */

void dmaLowLevelInitializer()
{
#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE
	NVIC_SetPriority(DMA1_Channel1_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_CHANNEL3_COMBINED_INTERRUPT

#if defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE)
	NVIC_SetPriority(DMA1_Channel2_3_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
#endif	// defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE)

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_CHANNEL3_COMBINED_INTERRUPT

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_CHANNEL5_CHANNEL6_CHANNEL7_COMBINED_INTERRUPT

#if defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE) || \
		defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE) || defined(CCONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE)
	NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);

#endif	// defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE) || defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE) || defined(CCONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE)

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_CHANNEL5_CHANNEL6_CHANNEL7_COMBINED_INTERRUPT
}

BIND_LOW_LEVEL_INITIALIZER(50, dmaLowLevelInitializer);

}	// namespace

}	// namespace chip

}	// namespace distortos
