/**
 * \file
 * \brief ChipDmaLowLevel class implementation for DMAv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipDmaLowLevel.hpp"

#include "distortos/chip/CMSIS-proxy.h"

#include "distortos/InterruptMaskingLock.hpp"

#include <tuple>

#define CSELR_REG_OFFSET		(0x000000A8U)

#define DMA_REG_SHIFT_CHANNEL1		(0U)
#define DMA_REG_SHIFT_CHANNEL2		(4U)
#define DMA_REG_SHIFT_CHANNEL3		(8U)
#define DMA_REG_SHIFT_CHANNEL4		(12U)
#define DMA_REG_SHIFT_CHANNEL5		(16U)
#define DMA_REG_SHIFT_CHANNEL6		(20U)
#define DMA_REG_SHIFT_CHANNEL7		(24U)

#define DMA_REG_CHANNEL_MASK		(0x0FU)

#define DMA_IFCR_CGIF		(DMA_IFCR_CGIF1)
#define DMA_IFCR_CTCIF		(DMA_IFCR_CTCIF1)
#define DMA_IFCR_CHTIF		(DMA_IFCR_CHTIF1)
#define DMA_IFCR_CTEIF		(DMA_IFCR_CTEIF1)
#define DMA_ISR_GIF		(DMA_ISR_GIF1)
#define DMA_ISR_TCIF		(DMA_ISR_TCIF1)
#define DMA_ISR_HTIF		(DMA_ISR_HTIF1)
#define DMA_ISR_TEIF		(DMA_ISR_TEIF1)

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| public types
+---------------------------------------------------------------------------------------------------------------------*/

/// parameters for construction of DMA low-level drivers
class ChipDmaLowLevel::Parameters
{
public:

	/**
	 * \brief Parameters's constructor
	 *
	 * \param [in] dmaBase is a base address of DMA peripheral
	 * \param [in] dmaChannelBase is a base address of DMA channel peripheral
	 * \param [in] shift is a channel shift in registers
	 */

	constexpr Parameters(const uintptr_t dmaBase, const uintptr_t dmaChannelBase, const uint8_t shift) :
			dmaBase_{dmaBase},
			dmaChannelBase_{dmaChannelBase},
			shift_{shift}
	{

	}

	/**
	 * \brief Enables or disables TC interrupt of DMA channel.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableTcInterrupt(const bool enable) const
	{
		auto& dmaChannel = getDmaChannel();
		const InterruptMaskingLock interruptMaskingLock;
		dmaChannel.CCR = (dmaChannel.CCR & ~DMA_CCR_TCIE) | (enable == true ? DMA_CCR_TCIE : 0);
	}

	/**
	 * \brief Enables or disables HT interrupt of DMA channel.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableHtInterrupt(const bool enable) const
	{
		auto& dmaChannel = getDmaChannel();
		const InterruptMaskingLock interruptMaskingLock;
		dmaChannel.CCR = (dmaChannel.CCR & ~DMA_CCR_HTIE) | (enable == true ? DMA_CCR_HTIE : 0);
	}

	/**
	 * \brief Enables or disables TE interrupt of DMA channel.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableTeInterrupt(const bool enable) const
	{
		auto& dmaChannel = getDmaChannel();
		const InterruptMaskingLock interruptMaskingLock;
		dmaChannel.CCR = (dmaChannel.CCR & ~DMA_CCR_TEIE) | (enable == true ? DMA_CCR_TEIE : 0);
	}

	/**
	 * \brief Enables or disables DMA channel.
	 *
	 * \param [in] enable selects whether the channel will be enabled (true) or disabled (false)
	 */

	void enableChannel(const bool enable) const
	{
		auto& dmaChannel = getDmaChannel();
		const InterruptMaskingLock interruptMaskingLock;
		dmaChannel.CCR = (dmaChannel.CCR & ~DMA_CCR_EN) | (enable == true ? DMA_CCR_EN : 0);
	}

	/**
	 * \return true if circular mode is enabled, false otherwise
	 */

	bool isCircularMode() const
	{
		return getDmaChannel().CCR & DMA_CCR_CIRC;
	}

	/**
	 * \return true if read from memory, false if from peripheral
	 */

	bool getTransferDirection() const
	{
		return getDmaChannel().CCR & DMA_CCR_DIR;
	}

	/**
	 * return status flags from corresponding ISR register and shift it to use as for channel 1
	 */

	uint32_t getStatusFlags() const
	{
		return (getDma().ISR >> shift_) & DMA_REG_CHANNEL_MASK;
	}

	/**
	 * \brief Clear status flags for channel.
	 *
	 * \param [in] flags to clear (DMA_IFCR_CGIF , DMA_IFCR_CTCIF, DMA_IFCR_CHTIF, DMA_IFCR_CTEIF
	 */

	void clearStatusFlags(const uint32_t flags) const
	{
		auto& dma = getDma();
		const InterruptMaskingLock interruptMaskingLock;
		dma.IFCR = (flags & DMA_REG_CHANNEL_MASK) << shift_;
	}

#ifdef CONFIG_CHIP_STM32_DMAV1_HAS_CSELR
	/**
	 * \brief Mapping the DMA channel.
	 *
	 * \param [in] selection is a value written to channel selection register
	 *
	 * This function configure DMA channel to be mapped to selected peripheral.
	 */

	void channelMapping(const uint8_t selection) const
	{
		auto& mode = *reinterpret_cast<volatile uint32_t*>(dmaBase_ + CSELR_REG_OFFSET);
		const InterruptMaskingLock interruptMaskingLock;
		mode &= ~(DMA_CSELR_C1S_Msk << shift_);
		mode |= selection << shift_;
	}
#endif	// CONFIG_CHIP_STM32_DMAV1_HAS_CSELR

	/**
	 * \return reference to DMA_TypeDef object
	 */

	DMA_TypeDef& getDma() const
	{
		return *reinterpret_cast<DMA_TypeDef*>(dmaBase_);
	}

	/**
	 * \return reference to DMA_Channel_TypeDef object
	 */

	DMA_Channel_TypeDef& getDmaChannel() const
	{
		return *reinterpret_cast<DMA_Channel_TypeDef*>(dmaChannelBase_);
	}

private:

	/// base address of DMA peripheral
	uintptr_t dmaBase_;

	/// base address of DMA channel peripheral
	uintptr_t dmaChannelBase_;

	/// channel shift in register
	uint8_t shift_;
};

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

ChipDmaLowLevel::~ChipDmaLowLevel()
{
	if (isStarted() == false)
		return;

	parameters_.enableChannel(false);
}

void ChipDmaLowLevel::interruptHandler()
{
	const auto ccr = parameters_.getDmaChannel().CCR;
	const auto isr = parameters_.getStatusFlags();

	if ((isr & DMA_ISR_TEIF) != 0 && (ccr & DMA_CCR_TEIE) != 0)
	{
		// clears TC, HT, EI flags, channel automatically disabled
		parameters_.clearStatusFlags(DMA_IFCR_CGIF);
		chipDmaBase_->transferErrorEvent();
	}
	else if ((isr & DMA_ISR_HTIF) != 0 && (ccr & DMA_CCR_HTIE) != 0)
	{
		parameters_.clearStatusFlags(DMA_IFCR_CHTIF);
		chipDmaBase_->halfTransferCompleteEvent();
	}
	else if ((isr & DMA_ISR_TCIF) != 0 && (ccr & DMA_CCR_TCIE) != 0)
	{
		parameters_.clearStatusFlags(DMA_IFCR_CTCIF);

		if (parameters_.isCircularMode() == false)
		{
			parameters_.enableChannel(false);
			transferLength_ = {};
		}
		chipDmaBase_->transferCompleteEvent();
	}
}

int ChipDmaLowLevel::start(ChipDmaBase& chipDmaBase, const DmaMode mode, const DataSize srcDataSize,
		const DataSize dstDataSize, const DmaOptionSet optionBits)
{
	if (isStarted() == true)
		return EBADF;

	if (mode == DmaMode::memoryToMemory && optionBits[DmaOptionSet::circularMode])
		return EINVAL;

	chipDmaBase_ = &chipDmaBase;
	auto& channel = parameters_.getDmaChannel();

	// mask already configured priority and clear other settings
	channel.CCR = (channel.CCR & DMA_CCR_PL_Msk);

	channel.CCR |= optionBits[DmaOptionSet::circularMode] << DMA_CCR_CIRC_Pos;
	if (mode == DmaMode::peripheralToMemory || mode == DmaMode::memoryToMemory)
	{
		channel.CCR |= optionBits[DmaOptionSet::srcIncr] << DMA_CCR_PINC_Pos |
				optionBits[DmaOptionSet::dstIncr] << DMA_CCR_MINC_Pos;
		channel.CCR |= srcDataSize << DMA_CCR_PSIZE_Pos | dstDataSize << DMA_CCR_MSIZE_Pos;
		if (mode == DmaMode::memoryToMemory)
			channel.CCR |= true << DMA_CCR_MEM2MEM_Pos;
	}
	else if (mode == DmaMode::memoryToPeripheral)
	{
		channel.CCR |= true << DMA_CCR_DIR_Pos;
		channel.CCR |= optionBits[DmaOptionSet::srcIncr] << DMA_CCR_MINC_Pos |
				optionBits[DmaOptionSet::dstIncr] << DMA_CCR_PINC_Pos;
		channel.CCR |= srcDataSize << DMA_CCR_MSIZE_Pos | dstDataSize << DMA_CCR_PSIZE_Pos;
	}

	parameters_.enableTeInterrupt(true);
	parameters_.enableHtInterrupt(true);
	parameters_.enableTcInterrupt(true);

	return 0;
}

int ChipDmaLowLevel::startTransfer(const uintptr_t srcAddress, const uintptr_t dstAddress, const size_t length)
{
	if (srcAddress == 0 || dstAddress == 0 || length < minTransferLength || length > maxTransferLength)
		return EINVAL;

	if (checkTransferSize(srcAddress, dstAddress))
		return EINVAL;

	if (isStarted() == false)
		return EBADF;

	if (isTransferInProgress() == true)
		return EBUSY;

	auto& channel = parameters_.getDmaChannel();
	channel.CNDTR = length;
	if (parameters_.getTransferDirection())
	{
		channel.CMAR = srcAddress;
		channel.CPAR = dstAddress;
	}
	else
	{
		channel.CPAR = srcAddress;
		channel.CMAR = dstAddress;
	}

	transferLength_ = length;
	// clears TC, HT, EI flags
	parameters_.clearStatusFlags(DMA_IFCR_CGIF);
	parameters_.enableChannel(true);

	return 0;
}

size_t ChipDmaLowLevel::stopTransfer()
{
	parameters_.enableChannel(false);

	const auto transferLength = transferLength_ - parameters_.getDmaChannel().CNDTR;
	transferLength_ = {};

	return transferLength;
}

int ChipDmaLowLevel::stop()
{
	if (isStarted() == false)
		return EBADF;

	if (isTransferInProgress() == true)
		return EBUSY;

	parameters_.enableChannel(false);
	chipDmaBase_ = nullptr;

	return 0;
}

#ifdef CONFIG_CHIP_STM32_DMAV1_HAS_CSELR

int ChipDmaLowLevel::channelMapping(const uint8_t selection)
{
	if (isStarted() == true)
		return EBADF;

	if (selection > maxSelection)
		return EINVAL;

	parameters_.channelMapping(selection);

	return 0;
}

#endif	// CONFIG_CHIP_STM32_DMAV1_HAS_CSELR

int ChipDmaLowLevel::channelPriority(const uint8_t priority)
{
	if (isStarted() == true)
		return EBADF;

	if (priority > maxPriority)
		return EINVAL;

	auto& channel = parameters_.getDmaChannel();
	channel.CCR = (channel.CCR & ~DMA_CCR_PL_Msk) | priority << DMA_CCR_PL_Pos;

	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------+
| private functions
+---------------------------------------------------------------------------------------------------------------------*/

int ChipDmaLowLevel::checkTransferSize(const uintptr_t srcAddress, const uintptr_t dstAddress)
{
	const auto ccr = parameters_.getDmaChannel().CCR;
	const auto srcSize = parameters_.getTransferDirection() == true ? (ccr & DMA_CCR_MSIZE_Msk) >> DMA_CCR_MSIZE_Pos :
			(ccr & DMA_CCR_PSIZE_Msk) >> DMA_CCR_PSIZE_Pos;
	const auto dstSize = parameters_.getTransferDirection() == true ? (ccr & DMA_CCR_PSIZE_Msk) >> DMA_CCR_PSIZE_Pos :
			(ccr & DMA_CCR_MSIZE_Msk) >> DMA_CCR_MSIZE_Pos;
	const auto srcTransferWidth = srcSize == 0 ? 1 : srcSize == 1 ? 2 : 4;
	const auto dstTransferWidth = dstSize == 0 ? 1 : dstSize == 1 ? 2 : 4;

	if ((srcAddress & (srcTransferWidth - 1)) != 0)
		return EINVAL;

	if ((dstAddress & (dstTransferWidth - 1)) != 0)
		return EINVAL;

	return 0;
}

}	// namespace chip

}	// namespace distortos
