/**
 * \file
 * \brief ChipDmaBase class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_CHIPDMABASE_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_CHIPDMABASE_HPP_

#include <bitset>

namespace distortos
{

namespace chip
{

/**
 * ChipDmaBase class is an interface with callbacks for low-level DMA driver, which can serve as a base for high-level
 * DMA drivers
 *
 * \ingroup devices
 */

class ChipDmaBase
{
public:

	/// bitset with DMA errors
	class ErrorSet : public std::bitset<3>
	{
	public:

		/// indexes of error bits in DmaErrorSet
		enum errorBits
		{
			/// FIFO error
			fifo,
			/// direct mode error
			directMode,
			/// stream transfer error
			streamTransfer,

			/// number of errors bits - must be last!
			dmaErrorBitsMax
		};
	};

	static_assert(ErrorSet{}.size() == ErrorSet::dmaErrorBitsMax,
			"Invalid size of DmaErrorSet's underlying bitset!");

	/**
	 * \brief ChipDmaBase's destructor
	 */

	virtual ~ChipDmaBase() = 0;

	/**
	 * \brief "Transfer complete" event
	 *
	 * Called by low-level DMA driver when the transfer is physically finished.
	 */

	virtual void transferCompleteEvent() = 0;

	/**
	 * \brief "Half transfer complete" event
	 *
	 * Called by low-level DMA driver when the half of transfer is physically finished.
	 */

	virtual void halfTransferCompleteEvent() = 0;

	/**
	 * \brief "Transfer error" event
	 *
	 * Called by low-level DMA driver when the transfer error occurs.
	 *
	 * \param [in] errorSet is the set of error bits
	 */

	virtual void transferErrorEvent(ErrorSet errorSet) = 0;
};

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_CHIPDMABASE_HPP_
