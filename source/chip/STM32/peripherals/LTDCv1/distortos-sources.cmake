#
# file: distortos-sources.cmake
#
# author: Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

if(CONFIG_CHIP_STM32_LTDCV1)

	target_sources(distortos PRIVATE
			${CMAKE_CURRENT_LIST_DIR}/STM32-LTDCv1-ChipMipiDpiLowLevel.cpp
			${CMAKE_CURRENT_LIST_DIR}/STM32-LTDCv1-ltdcs.cpp
			${CMAKE_CURRENT_LIST_DIR}/STM32-LTDCv1-ltdcLowLevelInitializer.cpp)

	doxygen(INPUT ${CMAKE_CURRENT_LIST_DIR} INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/include)

endif()
