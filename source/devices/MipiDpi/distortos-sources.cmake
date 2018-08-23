#
# file: distortos-sources.cmake
#
# author: Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

target_sources(distortos PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/MipiDpiBase.cpp
		${CMAKE_CURRENT_LIST_DIR}/MipiDpiDevice.cpp
		${CMAKE_CURRENT_LIST_DIR}/MipiDpiLowLevel.cpp)
