--
-- file: Tupfile.lua
--
-- author: Copyright (C) Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
--
-- This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
-- distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
--

if CONFIG_CHIP_STM32_DMAV1 == "y" then

	CXXFLAGS += STANDARD_INCLUDES
	CXXFLAGS += ARCHITECTURE_INCLUDES
	CXXFLAGS += CHIP_INCLUDES

	tup.include(DISTORTOS_TOP .. "compile.lua")

end	-- if CONFIG_CHIP_STM32_DMAV1 == "y" then
