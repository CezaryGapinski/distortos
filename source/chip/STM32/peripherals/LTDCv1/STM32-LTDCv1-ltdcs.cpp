/**
 * \file
 * \brief Definition of low-level LTDC drivers for LTDCv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ltdcs.hpp"

#include "include/distortos/chip/ChipMipiDpiLowLevel.hpp"

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_LTDCV1_ENABLE

ChipMipiDpiLowLevel ltdc {};

#endif	// def CONFIG_CHIP_STM32_LTDCV1_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_LTDCV1_ENABLE

/**
 * \brief LTDC interrupt handler
 */

extern "C" void LTDC_IRQHandler()
{
	ltdc.interruptHandler();
}

/**
 * \brief LTDC error interrupt handler
 */

extern "C" void LTDC_ER_IRQHandler()
{
	ltdc.interruptHandler();
}

#endif	// def CONFIG_CHIP_STM32_LTDCV1_ENABLE

}	// namespace chip

}	// namespace distortos
