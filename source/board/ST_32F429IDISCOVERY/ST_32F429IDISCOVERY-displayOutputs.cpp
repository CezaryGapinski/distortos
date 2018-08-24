/**
 * \file
 * \brief Definition of displayOutputs for ST,32F429IDISCOVERY
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

#include "distortos/board/displayOutputs.hpp"

#if defined(CONFIG_BOARD_DISPLAYOUTPUTS_ENABLE) && DISTORTOS_BOARD_DISPLAYOUTPUTS_COUNT != 0

#include "distortos/chip/ChipOutputPin.hpp"

namespace distortos
{

namespace board
{

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

chip::ChipOutputPin displayOutputs[displayOutputsCount]
{
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLE
		chip::ChipOutputPin{chip::Pin::pc2, false, chip::PinOutputSpeed::low, chip::PinPull::none, false, false},
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_SPICSX_ENABLE
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_RDX_ENABLE
		chip::ChipOutputPin{chip::Pin::pd12, false, chip::PinOutputSpeed::low, chip::PinPull::none, false, false},
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_RDX_ENABLE
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_TE_ENABLE
		chip::ChipOutputPin{chip::Pin::pd11, false, chip::PinOutputSpeed::low, chip::PinPull::none, false, false},
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_TE_ENABLE
#ifdef CONFIG_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLE
		chip::ChipOutputPin{chip::Pin::pd13, false, chip::PinOutputSpeed::low, chip::PinPull::none, false, false},
#endif	// def CONFIG_BOARD_DISPLAYOUTPUTS_WRXDCX_ENABLE
};

}	// namespace board

}	// namespace distortos

#endif	// defined(CONFIG_BOARD_DISPLAYOUTPUTS_ENABLE) && DISTORTOS_BOARD_DISPLAYOUTPUTS_COUNT != 0
