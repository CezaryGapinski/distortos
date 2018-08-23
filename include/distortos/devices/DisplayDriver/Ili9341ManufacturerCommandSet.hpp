/**
 * \file
 * \brief Ili9341ManufacturerCommandSet enum class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIINTERFACE_ILI9341MANUFACTURERCOMMANDSET_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIINTERFACE_ILI9341MANUFACTURERCOMMANDSET_HPP_

#include <cstdint>

namespace distortos
{

namespace devices
{

/**
 * MIPI ILI9341 Manufacturer Command Set for version v1.11, document No.:ILI9341_DS_V1.11.pdf
 *
 * \ingroup devices
 */

enum class Ili9341ManufacturerCommandSet : uint8_t
{
	/// Set RGB Interface Signals
	setRgbInterface = 0xb0,
	/// Set Frame Rate in Normal Mode
	setNormalFrameRate = 0xb1,
	/// Set Frame Rate in Idle Mode
	setIdleFrameRate = 0xb2,
	/// Set Frame Rate in Partial Mode
	setPartialFrameRate = 0xb3,
	/// Set Display Inversion
	setDisplayInversion = 0xb4,
	/// Set Blanking Porch
	setBlankingPorch = 0xb5,
	/// Set Display Function
	setDisplayFunction = 0xb6,
	/// Set Entry Mode
	setEntryMode = 0xb7,
	/// Set Backlight 1
	setBacklight1 = 0xb8,
	/// Set Backlight 2
	setBacklight2 = 0xb9,
	/// Set Backlight 3
	setBacklight3 = 0xba,
	/// Set Backlight 4
	setBacklight4 = 0xbb,
	/// Set Backlight 5
	setBacklight5 = 0xbc,
	/// Set Backlight 6
	setBacklight6 = 0xbd,
	/// Set Backlight 7
	setBacklight7 = 0xbe,
	/// Set Backlight 8
	setBacklight8 = 0xbf,
	/// Set Power 1
	setPower1 = 0xc0,
	/// Set Power 2
	setPower2 = 0xc1,
	/// Set Vcom Voltages 1
	setVcom1 = 0xc5,
	/// Set Vcom Voltages 2
	setVcom2 = 0xc7,
	/// Undocumented Command 0xca
	undocumentedCommandCAh = 0xca,
	/// Set Power A
	setPowerA = 0xcb,
	/// Set Power B
	setPowerB = 0xcf,
	/// Set Non Volatile Memory
	setNvMemory = 0xd0,
	/// Set Non Volatile Memory Protection Key
	setNvMemoryProtectionKey = 0xd1,
	/// Get Non Volatile Memory Status
	getNvMemoryStatus = 0xd2,
	/// Get ID4
	getId4 = 0xd3,
	/// Get ID1
	getId1 = 0xda,
	/// Get ID2
	getId2 = 0xdb,
	/// Get ID3
	getId3 = 0xdc,
	/// Set Positive Gamma Correction
	setPositiveGammaCorrection = 0xe0,
	/// Set Negative Gamma Correction
	setNegativeGammaCorrection = 0xe1,
	/// Set Digital Gamma 1
	setDigitalGamma1 = 0xe2,
	/// Set Digital Gamma 2
	setDigitalGamma2 = 0xe3,
	/// Set Driver Timing A
	setDriverTimingA = 0xe8,
	/// Set Power On Sequence
	setPowerOnSequence = 0xed,
	/// Set Driver Timing B
	setDriverTimingB = 0xea,
	/// Set Interface
	setInterface = 0xf6,
	/// Set Enable 3 Gamma
	setEnable3Gamma = 0xf2,
	/// Set Pump Ratio
	setPumpRatio = 0xf7,
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIINTERFACE_ILI9341MANUFACTURERCOMMANDSET_HPP_
