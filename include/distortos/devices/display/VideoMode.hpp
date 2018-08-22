/**
 * \file
 * \brief VideoMode struct header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAY_VIDEOMODE_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAY_VIDEOMODE_HPP_

#include <bitset>

namespace distortos
{

namespace devices
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// bits number for SignalBitsSet enum class
constexpr size_t signalBitsNumber = 5;

}	// namespace

/**
 * VideoMode struct is a struct with video mode parameters
 *
 * \ingroup devices
 */

struct VideoMode
{

	/**
	 * SignalBitsSet class is a bitset with polarity and edge bits related to Display signal configuration.
	 *
	 * \ingroup devices
	 */

	class SignalBitsSet : public std::bitset<signalBitsNumber>
	{
	public:

		/// indexes of error bits in SignalBitsSet
		enum SignalBits
		{
			/// horizontal sync signal polarity - 0 - low, 1 - high
			hSyncPolarity,
			/// vertical sync signal polarity - 0 - low, 1 - high
			vSyncPolarity,
			/// data enable signal polarity - 0 - low, 1 - high
			dataEnablePolarity,
			/// pixel drive data edge - 0 - negative, 1 - positive
			pixelDataEdge,
			/// synchronization edge - 0 - negative, 1 - positive
			syncEde,

			/// number of supported signal bits - must be last!
			signalBitsMax
		};

		/**
		 * \brief SignalBitsSet's constructor
		 *
		 * \param [in] bits is a value to initialize SignalBitsSet from SignalBits indexes
		 */

		constexpr SignalBitsSet(const uint8_t bits) :
				std::bitset<signalBitsNumber>{bits}
		{

		}
	};

	static_assert(std::bitset<signalBitsNumber>{}.size() == SignalBitsSet::signalBitsMax,
			"Invalid size of SignalBitsSet's underlying bitset!");

	/// active frame horizontal resolution
	uint32_t hActive;

	/// number of pixel clock pulses between the last valid pixel data in the line and the next H Sync pulse
	uint32_t hFrontPorch_;

	/// number of pixel clock pulses between H Sync signal and the first valid pixel data
	uint32_t hBackPorch;

	/// number of pixel clock pulses when a H Sync signal is active
	uint32_t hSyncLength;

	/// active frame vertical resolution
	uint32_t vActive;

	/// number of lines between the last valid line of the frame and the next V Sync pulse
	uint32_t vFrontPorch;

	/// number of lines from V Sync signal to the first valid line
	uint32_t vBackPorch;

	/// number of H Sync pulses when a V Sync signal is active
	uint32_t vSyncLength;

	/// polarity and edge bits
	SignalBitsSet signalBits;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_DISPLAY_VIDEOMODE_HPP_
