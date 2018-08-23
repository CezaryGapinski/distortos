/**
 * \file
 * \brief Declarations of low-level LTDC drivers for LTDCv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_LTDCV1_INCLUDE_DISTORTOS_CHIP_LTDCS_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_LTDCV1_INCLUDE_DISTORTOS_CHIP_LTDCS_HPP_

#include "distortos/distortosConfiguration.h"

namespace distortos
{

namespace chip
{

class ChipMipiDpiLowLevel;

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_LTDCV1_ENABLE

/// LTDC low-level driver
extern ChipMipiDpiLowLevel ltdc;

#endif	// def CONFIG_CHIP_STM32_LTDCV1_ENABLE

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_LTDCV1_INCLUDE_DISTORTOS_CHIP_LTDCS_HPP_
