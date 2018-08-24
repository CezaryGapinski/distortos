/**
 * \file
 * \brief Ili9341 class implementation
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/devices/DisplayDriver/Ili9341.hpp"

namespace distortos
{

namespace devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

Ili9341::~Ili9341()
{

}

int Ili9341::writeCmd(const MipiUserCommandSet command, const void* buffer, const size_t size)
{
	return writeDcsCmd(command, buffer, size);
}

int Ili9341::readCmd(const MipiUserCommandSet command, void* const buffer, const size_t size)
{
	return readDcsCmd(command, buffer, size);
}

int Ili9341::writeCmd(const Ili9341ManufacturerCommandSet command, const void* buffer, const size_t size)
{
	return writeMcsCmd(static_cast<uint8_t>(command), buffer, size);
}

int Ili9341::readCmd(const Ili9341ManufacturerCommandSet command, void* const buffer, const size_t size)
{
	return readMcsCmd(static_cast<uint8_t>(command), buffer, size);
}

}	// namespace devices

}	// namespace distortos
