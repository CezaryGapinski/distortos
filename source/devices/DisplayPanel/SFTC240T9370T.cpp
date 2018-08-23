/**
 * \file
 * \brief SFTC240T9370T class implementation
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/devices/DisplayPanel/SFTC240T9370T.hpp"

#include "distortos/devices/MipiDbi/MipiDbiLowLevel.hpp"
#include "distortos/devices/MipiDbi/MipiUserCommandSet.hpp"
#include "distortos/devices/display/VideoMode.hpp"
#include "distortos/internal/CHECK_FUNCTION_CONTEXT.hpp"

#include "distortos/ThisThread.hpp"

#include "distortos/devices/DisplayDriver/Ili9341ManufacturerCommandSet.hpp"
#include "distortos/devices/DisplayDriver/Ili9341.hpp"


namespace distortos
{

namespace devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public static objects
+---------------------------------------------------------------------------------------------------------------------*/

const VideoMode SFTC240T9370T::videoMode {hActive, hFrontPorch, hBackPorch, hSyncLength, vActive, vFrontPorch,
	vBackPorch, vSyncLength,
	{
			hSyncPolarity << VideoMode::SignalBitsSet::hSyncPolarity |
			vSyncPolarity << VideoMode::SignalBitsSet::vSyncPolarity |
			dataEnablePolarity << VideoMode::SignalBitsSet::dataEnablePolarity |
			pixelDataEdge << VideoMode::SignalBitsSet::pixelDataEdge |
			syncEde << VideoMode::SignalBitsSet::syncEde
	}
};

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

SFTC240T9370T::~SFTC240T9370T()
{

}

int SFTC240T9370T::init()
{
	int ret;

	ret = ili9341_.open();
	if (ret != 0)
		return ret;

	{
		const uint8_t parameters[] = {0xc3, 0x08, 0x50};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::undocumentedCommandCAh, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x00, 0xc1, 0x30};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setPowerB, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x64, 0x03, 0x12, 0x81};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setPowerOnSequence, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x85, 0x00, 0x78};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setDriverTimingA, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x39, 0x2c, 0x00, 0x34, 0x02};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setPowerA, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameter = 0x20;
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setPumpRatio, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x00, 0x00};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setDriverTimingB, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x00, 0x1b};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setNormalFrameRate, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x0a, 0xa2};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setDisplayFunction, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameter = 0x10;
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setPower1, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setPower2, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x45, 0x15};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setVcom1, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameter = 0x90;
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setVcom2, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameter = 0xc8;
		ret = ili9341_.writeCmd(MipiUserCommandSet::setAddressMode, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameter = 0x00;
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setEnable3Gamma, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameter = 0xc2;
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setRgbInterface, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x0a, 0xa7, 0x27, 0x04};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setDisplayFunction, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x00, 0x00, 0x00, 0xef};
		ret = ili9341_.writeCmd(MipiUserCommandSet::setColumnAddress, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x00, 0x00, 0x01, 0x3f};
		ret = ili9341_.writeCmd(MipiUserCommandSet::setPageAddress, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x01, 0x00, 0x06};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setInterface, parameters, sizeof(parameters));
		if (ret != 0)
			return ret;
	}

	ret = ili9341_.writeCmd(MipiUserCommandSet::writeMemoryStart, nullptr, 0);
	if (ret != 0)
		return ret;

	{
		const auto sleepForRet = ThisThread::sleepFor(std::chrono::milliseconds{200});
		if (sleepForRet != 0)
			return sleepForRet;
	}

	{
		const uint8_t parameter = 0x01;
		ret = ili9341_.writeCmd(MipiUserCommandSet::setGammaCurve, &parameter, sizeof(parameter));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x0f, 0x29, 0x24, 0x0c, 0x0e, 0x09, 0x4e, 0x78, 0x3c, 0x09, 0x13, 0x05, 0x17,
				0x11, 0x00};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setPositiveGammaCorrection, parameters,
				sizeof(parameters));
		if (ret != 0)
			return ret;
	}
	{
		const uint8_t parameters[] = {0x00, 0x16, 0x1b, 0x04, 0x11, 0x07, 0x31, 0x33, 0x42, 0x05, 0x0c, 0x0a, 0x28,
				0x2f, 0x0f};
		ret = ili9341_.writeCmd(Ili9341ManufacturerCommandSet::setNegativeGammaCorrection, parameters,
				sizeof(parameters));
		if (ret != 0)
			return ret;
	}

	ret = ili9341_.writeCmd(MipiUserCommandSet::exitSleepMode, nullptr, 0);
	if (ret != 0)
		return ret;

	{
		const auto sleepForRet = ThisThread::sleepFor(std::chrono::milliseconds{200});
		if (sleepForRet != 0)
			return sleepForRet;
	}

	ret = ili9341_.writeCmd(MipiUserCommandSet::setDisplayOn, nullptr, 0);
	if (ret != 0)
		return ret;
	ret = ili9341_.writeCmd(MipiUserCommandSet::writeMemoryStart, nullptr, 0);
	if (ret != 0)
		return ret;

	return 0;
}

}	// namespace devices

}	// namespace distortos
