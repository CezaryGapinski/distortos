/**
 * \file
 * \brief MipiDpiBase class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPIBASE_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPIBASE_HPP_

#include <bitset>

namespace distortos
{

namespace devices
{

/**
 * MipiDpiBase class is an interface with callbacks for low-level MipiDpi driver, which can serve as a base for high-level
 * MipiDpi drivers
 *
 * \ingroup devices
 */

class MipiDpiBase
{
public:

	/// indexes of error bits in ErrorSet
	enum ErrorBits
	{
		/// reads data from the empty FIFO
		fifoUnderrun,
		/// bus error
		busError,

		/// number of supported error bits - must be last!
		errorBitsMax
	};
	/// set of error bits
	using ErrorSet = std::bitset<errorBitsMax>;

	/**
	 * \brief MipiDpiBase's destructor
	 */

	virtual ~MipiDpiBase() = 0;

	/**
	 * \brief "V Sync complete" event
	 *
	 * Called by low-level MIPI DPI driver when a Vertical Sync is physically finished.
	 *
	 * Notifies any thread waiting for this event.
	 */

	virtual void VSyncEvent() = 0;

	/**
	 * \brief "error" event
	 *
	 * Called by low-level MIPI DPI driver when an error occurs.
	 *
	 * \param [in] errorSet is the set of error bits
	 */

	virtual void errorEvent(ErrorSet errorSet) = 0;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MIPIDPI_MIPIDPIBASE_HPP_
