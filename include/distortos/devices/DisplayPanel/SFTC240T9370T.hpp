/**
 * \file
 * \brief SFTC240T9370T class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAYPANEL_SFTC240T9370T_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAYPANEL_SFTC240T9370T_HPP_

#include <cstdint>

namespace distortos
{

namespace devices
{

class Ili9341;
class VideoMode;

/**
 * SFTC240T9370T class is a SFTC240T9370T LCD module with touch panel.
 *
 * \ingroup devices
 */

class SFTC240T9370T
{
public:

	/// active frame horizontal resolution
	constexpr static uint32_t hActive {240};

	/// number of pixel clock pulses between the last valid pixel data in the line and the next H Sync pulse
	constexpr static uint32_t hFrontPorch {10};

	/// number of pixel clock pulses between H Sync signal and the first valid pixel data
	constexpr static uint32_t hBackPorch {20};

	/// number of pixel clock pulses when a H Sync signal is active
	constexpr static uint32_t hSyncLength {10};

	/// active frame vertical resolution
	constexpr static uint32_t vActive {320};

	/// number of lines between the last valid line of the frame and the next V Sync pulse
	constexpr static uint32_t vFrontPorch {4};

	/// number of lines from V Sync signal to the first valid line
	constexpr static uint32_t vBackPorch {2};

	/// number of H Sync pulses when a V Sync signal is active
	constexpr static uint32_t vSyncLength {2};

	/// low horizontal sync signal polarity
	constexpr static bool hSyncPolarity {false};

	/// low vertical sync signal polarity
	constexpr static bool vSyncPolarity {false};

	/// low data enable signal polarity
	constexpr static bool dataEnablePolarity {false};

	/// negative pixel drive data edge
	constexpr static bool pixelDataEdge {false};

	/// negative synchronization edge
	constexpr static bool syncEde {false};

	/// video mode parameters for SFTC240T9370T LCD module
	static const VideoMode videoMode;

	/**
	 * \brief SFTC240T9370T's constructor
	 *
	 * \param [in] ili9341 is a reference to ILI9341 Display Driver to which this LCD module is connected
	 */

	constexpr SFTC240T9370T(Ili9341& ili9341) :
		ili9341_{ili9341}
	{

	}

	/**
	 * \brief SFTC240T9370T's destructor
	 */

	~SFTC240T9370T();

	/**
	 * \brief Initializing sequence for SFTC240T9370T LCD module.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - error codes returned by Ili9341::open();
	 * - error codes returned by Ili9341::writeCmd();
	 */

	int init();

private:

	/// reference to internal ILI9341 device
	Ili9341& ili9341_;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_DISPLAYPANEL_SFTC240T9370T_HPP_
