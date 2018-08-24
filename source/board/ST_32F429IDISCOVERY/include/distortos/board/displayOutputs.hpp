/**
 * \file
 * \brief Declaration of displayOutputs for ST,32F429IDISCOVERY
 *
 * \author Copyright (C) 2014-2018 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \warning
 * Automatically generated file - do not edit!
 */

#ifndef SOURCE_BOARD_ST_32F429IDISCOVERY_INCLUDE_DISTORTOS_BOARD_DISPLAYOUTPUTS_HPP_
#define SOURCE_BOARD_ST_32F429IDISCOVERY_INCLUDE_DISTORTOS_BOARD_DISPLAYOUTPUTS_HPP_

#include "distortos/distortosConfiguration.h"

#include <cstddef>

#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLED	1
#else	// !def CONFIG_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLED	0
#endif	// !def CONFIG_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLE

#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_RDX_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_RDX_ENABLED	1
#else	// !def CONFIG_BOARD_DISPLAYOUTPUTS_RDX_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_RDX_ENABLED	0
#endif	// !def CONFIG_BOARD_DISPLAYOUTPUTS_RDX_ENABLE

#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_TE_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_TE_ENABLED	1
#else	// !def CONFIG_BOARD_DISPLAYOUTPUTS_TE_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_TE_ENABLED	0
#endif	// !def CONFIG_BOARD_DISPLAYOUTPUTS_TE_ENABLE

#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLED	1
#else	// !def CONFIG_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLE
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLED	0
#endif	// !def CONFIG_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLE

/// count of displayOutputs on the board
#define DISTORTOS_BOARD_DISPLAYOUTPUTS_COUNT	(DISTORTOS_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLED + \
		DISTORTOS_BOARD_DISPLAYOUTPUTS_RDX_ENABLED + \
		DISTORTOS_BOARD_DISPLAYOUTPUTS_TE_ENABLED + \
		DISTORTOS_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLED)

#if defined(CONFIG_BOARD_DISPLAYOUTPUTS_ENABLE) && DISTORTOS_BOARD_DISPLAYOUTPUTS_COUNT != 0

namespace distortos
{

namespace chip
{

class ChipOutputPin;

}	// namespace chip

namespace board
{

/// count of displayOutputs on the board
constexpr size_t displayOutputsCount {DISTORTOS_BOARD_DISPLAYOUTPUTS_COUNT};

/*---------------------------------------------------------------------------------------------------------------------+
| indexes of displayOutputs
+---------------------------------------------------------------------------------------------------------------------*/

enum
{
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLE
		/// index of spiCsx from displayOutputs
		displayOutputsspiCsxIndex,
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLE
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_RDX_ENABLE
		/// index of rdx from displayOutputs
		displayOutputsrdxIndex,
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_RDX_ENABLE
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_TE_ENABLE
		/// index of te from displayOutputs
		displayOutputsteIndex,
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_TE_ENABLE
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLE
		/// index of wrxDcx from displayOutputs
		displayOutputswrxDcxIndex,
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLE
};

/*---------------------------------------------------------------------------------------------------------------------+
| indexed access to displayOutputs objects
+---------------------------------------------------------------------------------------------------------------------*/

/// array with all displayOutputs objects
extern chip::ChipOutputPin displayOutputs[displayOutputsCount];

}	// namespace board

}	// namespace distortos

#endif	// defined(CONFIG_BOARD_DISPLAYOUTPUTS_ENABLE) && DISTORTOS_BOARD_DISPLAYOUTPUTS_COUNT != 0

#endif	// SOURCE_BOARD_ST_32F429IDISCOVERY_INCLUDE_DISTORTOS_BOARD_DISPLAYOUTPUTS_HPP_
