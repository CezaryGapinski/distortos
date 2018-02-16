/**
 * \file
 * \brief ChipDmaLowLevel class header for DMAv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_CHIPDMALOWLEVEL_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_CHIPDMALOWLEVEL_HPP_

#include "distortos/chip/ChipDmaBase.hpp"
#include "distortos/Semaphore.hpp"

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
	enum class DmaMode : uint8_t
	{
		/// memory to memory
		memoryToMemory,
		/// peripheral to memory
		peripheralToMemory,
		/// memory to peripheral
		memoryToPeripheral
	};

	/// FIFO threshold level
	enum class DmaFifoLevel : uint8_t
	{
		/// 1/4 full FIFO
		oneQuarter,
		/// 1/2 full FIFO
		oneHalf,
		/// 3/4 full FIFO
		threeQuarters,
		/// full FIFO
		full,
		/// disable FIFO
		disable
	};

	/// all possible burst transfer configurations
	enum class BurstBeats : uint8_t
	{
		/// single transfer
		single,
		/// incremental burst of 4 beats
		incr4,
		/// incremental burst of 8 beats
		incr8,
		/// incremental burst of 16 beats
		incr16
	};

	/// all possible data size configurations
	enum class DataSize : uint8_t
	{
		/// byte (8-bit)
		byte,
		/// half-word (16-bit)
		halfWord,
		/// word (32-bit)
		word
	};

	/// bitset with DMA options
	class DmaOptionSet : public std::bitset<6>
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
			/// selects whether peripheral indicates by hardware to the DMA controller when the last data are being
			/// transfered
			peripheralFlowController,
			/// selects whether double buffer mode will be enabled
			doubleBufferMode,
			/// fix the increment offset size for the peripheral address
			fixPeripheralIncrementOffset,

			/// number of supported options bits - must be last!
			dmaOptionBitsMax
		};
	};

	static_assert(DmaOptionSet{}.size() == DmaOptionSet::dmaOptionBitsMax,
			"Invalid size of DmaOptionSet's underlying bitset!");

	/// maximum value for channel mapping
	constexpr static uint8_t channelMax {15};

	/// maximum value for allowed priority
	constexpr static uint8_t maxPriority {3};

	/// minimum allowed transfer length
	constexpr static size_t minTransferLength {1};

	/// maximum allowed transfer length
	constexpr static size_t maxTransferLength {65535};

	class Parameters;

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
	 * \param [in] srcDataSize is source data size (one of DataSize values)
	 * \param [in] dstDataSize is destination data size (one of DataSize values)
	 * \param [in] srcBurstSize is number of beats in the burst transfer from source (one of BurstBeats values)
	 * \param [in] dstBurstSize is number of beats in the burst transfer to destination (one of BurstBeats values)
	 * \param [in] fifoThreshold is used to temporarily store data coming from the source before transmitting
	 * them to the destination (one of DmaFifoLevel values)
	 * \param [in] optionBits is the set of DMA option bits, supported by this driver are:
	 * - srcIncr selects whether source memory pointer will be automatically post-incremented
	 * after each transaction
	 * - dstIncr selects whether destination memory pointer will be automatically post-incremented
	 * after each transaction
	 * - circularMode selects whether data will be transfered again after last data transfer
	 * - peripheralFlowController selects whether peripheral indicates by hardware to the DMA controller when the last
	 * data are being transfered
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - selected options are invalid;
	 */

	int start(ChipDmaBase& chipDmaBase, DmaMode mode, DataSize srcDataSize, DataSize dstDataSize,
			BurstBeats srcBurstBeats, BurstBeats dstBurstBeats, DmaFifoLevel fifoThreshold, DmaOptionSet optionBits);

	/**
	 * \brief Starts transfer operation.
	 *
	 * This function returns immediately. When the operation is finished (expected number of data were written),
	 * ChipDmaBase::transferCompleteEvent() will be executed. When half of transfer is finished
	 * halfTransferCompleteEvent() will be executed. If error occurs transferErrorEvent() will be executed.
	 *
	 * \param [in] srcAddress is a source memory buffer address
	 * \param [in] dstAddress is a destination memory buffer address
	 * \param [in] length is a length of data to transfer, [minTransferLength; maxTransferLength]
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - write is in progress;
	 * - EINVAL - \a srcAddress, \a dstAddress and/or \a length are invalid;
	 */

	int startTransfer(uintptr_t srcAddress, uintptr_t dstAddress, size_t length);

	/**
	 * \brief Updates not already used buffer in double buffer mode.
	 *
	 * \param [in] address is a source memory buffer address
	 * \param [in] length is a length of data to transfer, [minTransferLength; maxTransferLength]
	 *
	 * \return 0 on success, error code otherwise:
	 * - EINVAL - \a address or \a length are invalid;
	 * - EBADF - the driver is not enabled or configured to double buffer mode;
	 */

	int updateNextBuffer(uintptr_t address, size_t length);

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

	/**
	 * \brief Mapping the DMA stream to selected peripheral channel.
	 *
	 * \param [in] channel is a value written to channel selection field [0; 7] or [0; maxChannel]
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - selection is invalid;
	 */

	int streamMapping(uint8_t channel);

	/**
	 * \brief Configure stream priority level
	 *
	 * \param [in] priority is a stream priority [0; 3] or [0; maxPriority] (0 - Low, 1 - Medium, 2 - High,
	 * 3 - Very high)
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - priority is invalid;
	 */

	int streamPriority(uint8_t priority);

private:

	/**
	 * \brief Checks transfer length correctness and restriction for memory and peripheral bus size.
	 *
	 * \param [in] length is a length of data to transfer
	 *
	 * \return 0 on success, error code otherwise:
	 * - EINVAL - selected options are invalid;
	 */

	int checkLengthResctriction(size_t length);

	/**
	 * \brief Checks burst configuration correctness.
	 *
	 * \param [in] address is a begin memory address
	 * \param [in] length is a length of data to transfer
	 *
	 * \return 0 on success, error code otherwise:
	 * - EINVAL - configuration cause crossing 1 KiB address boundary;
	 */

	int checkMemoryBurst(uintptr_t address, size_t length);

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

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_DMAV2_INCLUDE_DISTORTOS_CHIP_CHIPDMALOWLEVEL_HPP_
