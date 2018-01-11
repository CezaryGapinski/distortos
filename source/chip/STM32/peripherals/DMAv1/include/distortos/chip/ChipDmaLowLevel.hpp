/**
 * \file
 * \brief ChipDmaLowLevel class header for DMAv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_DMAV1_INCLUDE_DISTORTOS_CHIP_CHIPDMALOWLEVEL_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_DMAV1_INCLUDE_DISTORTOS_CHIP_CHIPDMALOWLEVEL_HPP_

#include "distortos/chip/ChipDmaBase.hpp"

#include "distortos/distortosConfiguration.h"

#include <bitset>

namespace distortos
{

namespace chip
{

/**
 * ChipDmaLowLevel class is a low-level DMA driver for DMAv1 in STM32
 *
 * \ingroup devices
 */

class ChipDmaLowLevel
{
public:

	/// types of DMA transfer
	enum DmaMode
	{
		/// memory to memory
		memoryToMemory,
		/// peripheral to memory
		peripheralToMemory,
		/// memory to peripheral
		memoryToPeripheral
	};

	/// all possible data size configurations
	enum DataSize : uint8_t
	{
		/// byte (8-bit)
		byte,
		/// half-word (16-bit)
		halfWord,
		/// word (32-bit)
		word
	};

	/// bitset with DMA options
	class DmaOptionSet : public std::bitset<3>
	{
	public:

		/// indexes of option bits in DmaOptionSet
		enum optionBits
		{
			/// selects whether source memory pointer will be automatically post-incremented after each transaction
			srcIncr,
			/// selects whether destination memory pointer will be automatically post-incremented after each transaction
			dstIncr,
			/// circularMode selects whether data will be transfered again after last data transfer
			circularMode,

			/// number of supported options bits - must be last!
			dmaOptionBitsMax
		};
	};

	static_assert(DmaOptionSet{}.size() == DmaOptionSet::dmaOptionBitsMax,
			"Invalid size of DmaOptionSet's underlying bitset!");

	/// maximum allowed channel selection
	constexpr static uint8_t maxSelection {7};

	/// maximum allowed priority
	constexpr static uint8_t maxPriority {3};

	/// minimum allowed transfer length
	constexpr static size_t minTransferLength {1};

	/// maximum allowed transfer length
	constexpr static size_t maxTransferLength {65535};

	class Parameters;

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

	/// parameters for construction of DMA low-level driver for DMA1 Channel1
	static const Parameters dma1Channel1Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

	/// parameters for construction of DMA low-level driver for DMA1 Channel2
	static const Parameters dma1Channel2Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

	/// parameters for construction of DMA low-level driver for DMA1 Channel3
	static const Parameters dma1Channel3Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

	/// parameters for construction of DMA low-level driver for DMA1 Channel4
	static const Parameters dma1Channel4Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

	/// parameters for construction of DMA low-level driver for DMA1 Channel5
	static const Parameters dma1Channel5Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

	/// parameters for construction of DMA low-level driver for DMA1 Channel6
	static const Parameters dma1Channel6Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

	/// parameters for construction of DMA low-level driver for DMA1 Channel7
	static const Parameters dma1Channel7Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA1_CHANNEL7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

	/// parameters for construction of DMA low-level driver for DMA2 Channel1
	static const Parameters dma2Channel1Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

	/// parameters for construction of DMA low-level driver for DMA2 Channel2
	static const Parameters dma2Channel2Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

	/// parameters for construction of DMA low-level driver for DMA2 Channel3
	static const Parameters dma2Channel3Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

	/// parameters for construction of DMA low-level driver for DMA2 Channel4
	static const Parameters dma2Channel4Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

	/// parameters for construction of DMA low-level driver for DMA2 Channel5
	static const Parameters dma2Channel5Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

	/// parameters for construction of DMA low-level driver for DMA2 Channel6
	static const Parameters dma2Channel6Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

	/// parameters for construction of DMA low-level driver for DMA2 Channel7
	static const Parameters dma2Channel7Parameters;

#endif	// def CONFIG_CHIP_STM32_DMAV1_DMA2_CHANNEL7_ENABLE

	/**
	 * \brief ChipDmaLowLevel's constructor
	 *
	 * \param [in] parameters is a reference to object with peripheral parameters
	 */

	constexpr explicit ChipDmaLowLevel(const Parameters& parameters) :
			parameters_{parameters},
			chipDmaBase_{},
			transferLength_{}
	{

	}

	/**
	 * \brief ChiDmaLowLevel's destructor
	 *
	 * Does nothing if driver is already stopped. If it's not, performs forced stop of operation.
	 */

	~ChipDmaLowLevel();

	/**
	 * \brief Interrupt handler
	 *
	 * \note this must not be called by user code
	 */

	void interruptHandler();

	/**
	 * \brief Starts low-level DMA driver.
	 *
	 * \param [in] chipDmaBase is a reference to ChipDmaBase object that will be associated with this one
	 * \param [in] mode is the desired DMA mode
	 * \param [in] srcDataSize is source bus width used to data transfer (one of DataSize values)
	 * \param [in] dstDataSize is destination bus width used to data transfer (one of DataSize values)
	 * \param [in] optionBits is the set of DMA option bits, supported by this driver are:
	 *  - srcIncr selects whether source memory pointer will be automatically post-incremented
	 *  after each transaction
	 *  - dstIncr selects whether destination memory pointer will be automatically post-incremented
	 *  after each transaction
	 * - circularMode selects whether data will be transfered again after last data transfer
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - selected options are invalid;
	 */

	int start(ChipDmaBase& chipDmaBase, DmaMode mode, DataSize srcDataSize, DataSize dstDataSize,
			DmaOptionSet optionBits);

	/**
	 * \brief Starts transfer operation.
	 *
	 * This function returns immediately. When the operation is finished (expected number of data were written),
	 * ChipDmaBase::transferCompleteEvent() will be executed. When half of transfer is finished
	 * halfTransferCompleteEvent() will be executed. If error occurs transferErrorEvent() will be executed.
	 *
	 * \param [in] srcAddress is a source memory buffer address
	 * \param [in] dstAddress is a destination memory buffer address
	 * \param [in] length is a length of data to transfer [1; 65535] or [minTransferLength; maxTransferLength]
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - write is in progress;
	 * - EINVAL - \a srcAddress, \a dstAddress and/or \a length are invalid;
	 */

	int startTransfer(uintptr_t srcAddress, uintptr_t dstAddress, size_t length);

	/**
	 * \brief Stops transfer operation.
	 *
	 * This function stops transfer and returns number of transfered data.
	 *
	 * \return number of data transfered by low-level DMA driver
	 */

	size_t stopTransfer();

	/**
	 * \brief Stops low-level DMA driver.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - read and/or write are in progress;
	 */

	int stop();

	#ifdef CONFIG_CHIP_STM32_DMAV1_HAS_CSELR

	/**
	 * \brief Mapping the DMA channel to selected peripheral.
	 *
	 * \param [in] selection is a value written to channel selection register [0; 7] or [0; maxSelection]
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - selection is invalid;
	 */

	int channelMapping(uint8_t selection);

	#endif	// CONFIG_CHIP_STM32_DMAV1_HAS_CSELR

	/**
	 * \brief Configure channel priority level
	 *
	 * \param [in] priority is a channel priority [0; 3] or [0; maxPriority]
	 * (0 - Low, 1 - Medium, 2 - High, 3 - Very high)
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - priority is invalid;
	 */

	int channelPriority(uint8_t priority);

private:

	/**
	 * \brief Check transfer size.
	 *
	 * Verify that the source and destination address are aligned to their size.
	 *
	 * \param [in] srcAddress is a source address
	 * \param [in] dstAddress is a destination address
	 *
	 * \return 0 on success, error code otherwise:
	 * - EINVAL - \a srcAddress and/or \a dstAddress are invalid;
	 */

	int checkTransferSize(uintptr_t srcAddress, uintptr_t dstAddress);

	/**
	 * \return true if driver is started, false otherwise
	 */

	bool isStarted() const
	{
		return chipDmaBase_ != nullptr;
	}

	/**
	 * \return true if transfer operation is in progress, false otherwise
	 */

	bool isTransferInProgress() const
	{
		return transferLength_ != 0;
	}

	/// reference to configuration parameters
	const Parameters& parameters_;

	/// pointer to ChipDmaBase object associated with this one
	ChipDmaBase* chipDmaBase_;

	/// contains data length requested to transfer
	volatile size_t transferLength_;
};

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_DMAV1_INCLUDE_DISTORTOS_CHIP_CHIPDMALOWLEVEL_HPP_
