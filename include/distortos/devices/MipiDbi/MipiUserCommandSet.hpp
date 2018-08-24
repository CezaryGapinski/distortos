/**
 * \file
 * \brief MipiUserCommandSet enum class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIUSERCOMMANDSET_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIUSERCOMMANDSET_HPP_

#include <cstdint>

namespace distortos
{

namespace devices
{

/**
 * MIPI User Command Set
 *
 * \ingroup devices
 */

enum class MipiUserCommandSet : uint8_t
{
	/// nop command
	nop = 0x0,
	/// Software Reset
	softReset = 0x1,
	/// Get Display Identification Information
	getDisplayId = 0x4,
	/// Get Red Channel
	getRedChannel = 0x6,
	/// Get Green Channel
	getGreenChannel = 0x7,
	/// Get Blue Channel
	getBlueChannel = 0x8,
	/// Get Display Status
	getDisplayStatus = 0x9,
	/// Get Power Mode
	getPowerMode = 0xa,
	/// Get Address Mode
	getAddressMode = 0xb,
	/// Get Pixel Format
	getPixelFormat = 0xc,
	/// Get Display Mode
	getDisplayMode = 0xd,
	/// Get Signal Mode
	getSignalMode = 0xe,
	/// Get Self-Diagnostic Result
	getDiagnosticResult = 0xf,
	/// Enter Sleep Mode
	enterSleepMode = 0x10,
	/// Exit Sleep Mode
	exitSleepMode = 0x11,
	/// Enter Partial Mode
	enterPartialMode = 0x12,
	/// Enter Normal Mode = 0x13,
	enterNormalMode = 0x13,
	/// Exit Invert Mode
	exitInvertMode = 0x20,
	/// Enter Invert Mode
	enterInvertMode = 0x21,
	/// Set Gamma Curve
	setGammaCurve = 0x26,
	/// Set Display Off
	setDisplayOff = 0x28,
	/// Set Display On
	setDisplayOn = 0x29,
	/// Set Column Address
	setColumnAddress = 0x2a,
	/// Set Page Address
	setPageAddress = 0x2b,
	/// Write Memory Start
	writeMemoryStart = 0x2c,
	/// Write Color Set - LUT
	writeLut = 0x2d,
	/// Read Memory Start
	readMemoryStart = 0x2e,
	/// Set Partial Area
	setPartialArea = 0x30,
	/// Set Scroll Area
	setScrollArea = 0x33,
	/// Set Tearing Effect Off
	setTearOff = 0x34,
	/// Set Tearing Effect On
	setTearOn = 0x35,
	/// Set Address Mode
	setAddressMode = 0x36,
	// Scrolling Start Address
	setScrollStart = 0x37,
	/// Exit Idle Mode
	exitIdleMode = 0x38,
	/// Enter Idle Mode
	enterIdleMode = 0x39,
	/// Set Pixel Format
	setPixelFormat = 0x3a,
	/// Write Memory Continue
	writeMemoryContinue = 0x3c,
	/// Read Memory Continue
	readMemoryContinue = 0x3e,
	/// Set Tear Scanline
	setTearScanline = 0x44,
	/// Get Scanline
	getScanline = 0x45,
	/// Set Display Brightness
	setDisplayBrightness = 0x51,
	/// Get Display Brightness
	getDisplayBrightness = 0x51,
	/// Write Control Display
	writeControlDisplay = 0x53,
	/// Get Control Display
	getControlDisplay = 0x54,
	/// Write Power Save
	writePowerSave = 0x55,
	/// Get Power Save
	getPowerSave = 0x56,
	/// Set Content Adaptive Brightness Control Minimum Brightness
	setCabcMinBrightness = 0x5e,
	/// Get Content Adaptive Brightness Control Minimum Brightness
	getCabcMinBrightness = 0x5f,
	/// Read Device Descriptor Block from the provided location
	readDdbStart = 0xa1,
	/// Continue reading the Device Descriptor Block from the last read location
	readDdbContinue = 0xa8,
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDBI_MIPIUSERCOMMANDSET_HPP_
