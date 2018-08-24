/**
 * \file
 * \brief Low-level peripheral initializer for LTDCv1 in STM32
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

/// priority of USART interrupts
#if defined(CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI)
constexpr uint8_t interruptPriority {CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI};
#else	// !defined(CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI)
constexpr uint8_t interruptPriority {};
#endif	// !defined(CONFIG_ARCHITECTURE_ARMV7_M_KERNEL_BASEPRI)

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Low-level peripheral initializer for LTDCv1 in STM32
 *
 * This function is called before constructors for global and static objects via BIND_LOW_LEVEL_INITIALIZER().
 */

void ltdcLowLevelInitializer()
{
#ifdef CONFIG_CHIP_STM32_LTDCV1_ENABLE
	NVIC_SetPriority(LTDC_IRQn, interruptPriority);
	NVIC_EnableIRQ(LTDC_IRQn);

	NVIC_SetPriority(LTDC_ER_IRQn, interruptPriority);
	NVIC_EnableIRQ(LTDC_ER_IRQn);
#endif	// def CONFIG_CHIP_STM32_LTDCV1_ENABLE
}

BIND_LOW_LEVEL_INITIALIZER(50, ltdcLowLevelInitializer);

}	// namespace

}	// namespace chip

}	// namespace distortos
