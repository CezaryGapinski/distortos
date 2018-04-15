/**
 * \file
 * \brief Low-level peripheral initializer for DMAv2 in STM32
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
 * \brief Low-level peripheral initializer for DMAv2 in STM32
 *
 * This function is called before constructors for global and static objects via BIND_LOW_LEVEL_INITIALIZER().
 */

void dmaLowLevelInitializer()
{
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE
	NVIC_SetPriority(DMA1_Stream0_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream0_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE
	NVIC_SetPriority(DMA1_Stream1_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream1_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE
	NVIC_SetPriority(DMA1_Stream2_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream2_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE
	NVIC_SetPriority(DMA1_Stream3_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE
	NVIC_SetPriority(DMA1_Stream4_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream4_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE
	NVIC_SetPriority(DMA1_Stream5_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream5_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE
	NVIC_SetPriority(DMA1_Stream6_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE
	NVIC_SetPriority(DMA1_Stream7_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA1_Stream7_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE
	NVIC_SetPriority(DMA2_Stream0_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE
	NVIC_SetPriority(DMA2_Stream1_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream1_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE
	NVIC_SetPriority(DMA2_Stream2_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE
	NVIC_SetPriority(DMA2_Stream3_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE
	NVIC_SetPriority(DMA2_Stream4_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream4_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE
	NVIC_SetPriority(DMA2_Stream5_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream5_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE
	NVIC_SetPriority(DMA2_Stream6_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream6_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE
#ifdef	CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE
	NVIC_SetPriority(DMA2_Stream7_IRQn, interruptPriority);
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE
}

BIND_LOW_LEVEL_INITIALIZER(50, dmaLowLevelInitializer);

}	// namespace

}	// namespace chip

}	// namespace distortos
