


/**
 * \file
 * \brief Definition of displayPinmux for ST,32F429IDISCOVERY
 *
 * \author Copyright (C) 2014-2018 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \warning
 * Automatically generated file - do not edit!
 */

#include "distortos/distortosConfiguration.h"

#include "distortos/BIND_LOW_LEVEL_INITIALIZER.h"

#include "distortos/chip/STM32-GPIOv2.hpp"

#ifdef CONFIG_BOARD_DISPLAYPINMUX_ENABLE

namespace distortos
{

namespace board
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief displayPinmux initializer for alternate pins in STM32
 *
 * This function is called before constructors for global and static objects via BIND_LOW_LEVEL_INITIALIZER().
 */

void displayPinmuxInitializer()
{
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTVSYNC_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pa4, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTVSYNC_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTHSYNC_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pc6, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTHSYNC_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTDE_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pf10, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTDE_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTCLK_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pg7, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTCLK_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTR2_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pc10, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTR2_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTR3_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pb0, chip::PinAlternateFunction::af9, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTR3_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTR4_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pa11, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTR4_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTR5_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pa12, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTR5_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTR6_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pb1, chip::PinAlternateFunction::af9, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTR6_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTR7_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pg6, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTR7_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTG2_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pa6, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTG2_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTG3_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pg10, chip::PinAlternateFunction::af9, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTG3_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTG4_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pb10, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTG4_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTG5_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pb11, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTG5_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTG6_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pc7, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTG6_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTG7_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pd3, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTG7_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTB2_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pd6, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTB2_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTB3_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pg11, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTB3_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTB4_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pg12, chip::PinAlternateFunction::af9, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTB4_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTB5_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pa3, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTB5_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTB6_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pb8, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTB6_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_TFTB7_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pb9, chip::PinAlternateFunction::af14, false,
		chip::PinOutputSpeed::veryHigh, chip::PinPull::none);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_TFTB7_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_SPISCK_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pf7, chip::PinAlternateFunction::af5, false,
		chip::PinOutputSpeed::medium, chip::PinPull::down);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_SPISCK_ENABLE
#ifdef CONFIG_BOARD_DISPLAYPINMUX_SPIMOSI_ENABLE
	chip::configureAlternateFunctionPin(chip::Pin::pf9, chip::PinAlternateFunction::af5, false,
		chip::PinOutputSpeed::medium, chip::PinPull::down);
#endif	// def CONFIG_BOARD_DISPLAYPINMUX_SPIMOSI_ENABLE
};

BIND_LOW_LEVEL_INITIALIZER(50, displayPinmuxInitializer);

}	// namespace board

}	// namespace distortos

#endif	// def CONFIG_BOARD_DISPLAYPINMUX_ENABLE
