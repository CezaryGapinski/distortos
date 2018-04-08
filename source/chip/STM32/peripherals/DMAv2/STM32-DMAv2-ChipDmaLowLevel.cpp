/**
 * \file
 * \brief ChipDmaLowLevel class implementation for DMAv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipDmaLowLevel.hpp"

#include "distortos/chip/CMSIS-proxy.h"
#include "distortos/chip/STM32-bit-banding.h"

#include "distortos/InterruptMaskingLock.hpp"

#include <tuple>

#define DMA_INT_REG_SHIFT_STREAM0		(0U)
#define DMA_INT_REG_SHIFT_STREAM1		(6U)
#define DMA_INT_REG_SHIFT_STREAM2		(16U)
#define DMA_INT_REG_SHIFT_STREAM3		(22U)
#define DMA_INT_REG_SHIFT_STREAM4		(0U)
#define DMA_INT_REG_SHIFT_STREAM5		(6U)
#define DMA_INT_REG_SHIFT_STREAM6		(16U)
#define DMA_INT_REG_SHIFT_STREAM7		(22U)

#define DMA_INT_REG_STREAM_MASK		(0x3DU)

#define DMA_IFCR_CFEIF		(DMA_LIFCR_CFEIF0)
#define DMA_IFCR_CDMEIF		(DMA_LIFCR_CDMEIF0)
#define DMA_IFCR_CTEIF		(DMA_LIFCR_CTEIF0)
#define DMA_IFCR_CHTIF		(DMA_LIFCR_CHTIF0)
#define DMA_IFCR_CTCIF		(DMA_LIFCR_CTCIF0)
#define DMA_ISR_FEIF		(DMA_LISR_FEIF0)
#define DMA_ISR_DMEIF		(DMA_LISR_DMEIF0)
#define DMA_ISR_TEIF		(DMA_LISR_TEIF0)
#define DMA_ISR_HTIF		(DMA_LISR_HTIF0)
#define DMA_ISR_TCIF		(DMA_LISR_TCIF0)

namespace distortos
{

namespace chip
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Decode value of DMA_ISR flags to ChipDmaBase::DmaErrorSet
 *
 * \param [in] isr is the value of DMA_ISR flags that will be decoded
 *
 * \return ChipDmaBase::ErrorSet with errors decoded from \a isr
 */

ChipDmaBase::ErrorSet decodeErrors(const uint32_t isr)
{
	ChipDmaBase::ErrorSet errorSet {};
	errorSet[ChipDmaBase::ErrorSet::fifo] = (isr & DMA_ISR_FEIF) != 0;
	errorSet[ChipDmaBase::ErrorSet::directMode] = (isr & DMA_ISR_DMEIF) != 0;
	errorSet[ChipDmaBase::ErrorSet::streamTransfer] = (isr & DMA_ISR_TEIF) != 0;
	return errorSet;
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| public types
+---------------------------------------------------------------------------------------------------------------------*/

/// parameters for construction of DMA low-level drivers
class ChipDmaLowLevel::Parameters
{
public:
#ifdef DISTORTOS_BITBANDING_SUPPORTED

	/**
	 * \brief Parameters's constructor
	 *
	 * \param [in] dmaBase is a base address of DMA peripheral
	 * \param [in] dmaStreamBase is a base address of DMA stream peripheral
	 * \param [in] intStatusOffset is a offset of DMA register with interrupt status
	 * \param [in] intClearOffset is a offset of DMA register with interrupt clear
	 * \param [in] shift is a stream shift in registers
	 */

	constexpr Parameters(const uintptr_t dmaBase, const uintptr_t dmaStreamBase, const size_t intStatusOffset,
			const size_t intClearOffset, const uint8_t shift) :
			dmaBase_{dmaBase},
			dmaStreamBase_{dmaStreamBase},
			tcieBbAddress_{STM32_BITBAND_IMPLEMENTATION(dmaStreamBase_, DMA_Stream_TypeDef, CR, DMA_SxCR_TCIE)},
			htieBbAddress_{STM32_BITBAND_IMPLEMENTATION(dmaStreamBase_, DMA_Stream_TypeDef, CR, DMA_SxCR_HTIE)},
			teieBbAddress_{STM32_BITBAND_IMPLEMENTATION(dmaStreamBase_, DMA_Stream_TypeDef, CR, DMA_SxCR_TEIE)},
			dmeieBbAddress_{STM32_BITBAND_IMPLEMENTATION(dmaStreamBase_, DMA_Stream_TypeDef, CR, DMA_SxCR_DMEIE)},
			feieBbAddress_{STM32_BITBAND_IMPLEMENTATION(dmaStreamBase_, DMA_Stream_TypeDef, FCR, DMA_SxFCR_FEIE)},
			enBbAddress_{STM32_BITBAND_IMPLEMENTATION(dmaStreamBase_, DMA_Stream_TypeDef, CR, DMA_SxCR_EN)},
			intStatusOffset_{intStatusOffset},
			intClearOffset_{intClearOffset},
			shift_{shift}
	{

	}

#else	// !def DISTORTOS_BITBANDING_SUPPORTED

	/**
	 * \brief Parameters's constructor
	 *
	 * \param [in] dmaBase is a base address of DMA peripheral
	 * \param [in] dmaStreamBase is a base address of DMA stream peripheral
	 * \param [in] intStatusOffset is a offset of DMA register with interrupt status
	 * \param [in] intClearOffset is a offset of DMA register with interrupt clear
	 * \param [in] shift is a stream shift in registers
	 */

	constexpr Parameters(const uintptr_t dmaBase, const uintptr_t dmaStreamBase, const size_t intStatusOffset,
			const size_t intClearOffset, const uint8_t shift) :
			dmaBase_{dmaBase},
			dmaStreamBase_{dmaStreamBase},
			intStatusOffset_{intStatusOffset},
			intClearOffset_{intClearOffset},
			shift_{shift}
	{

	}

#endif	// !def DISTORTOS_BITBANDING_SUPPORTED

	/**
	 * \brief Enables or disables TC interrupt of DMA stream.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableTcInterrupt(const bool enable) const
	{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
		*reinterpret_cast<volatile unsigned long*>(tcieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
		auto& dmaStream = getDmaStream();
		const InterruptMaskingLock interruptMaskingLock;
		dmaStream.CR = (dmaStream.CR & ~DMA_SxCR_TCIE) | (enable == true ? DMA_SxCR_TCIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
	}

	/**
	 * \brief Enables or disables HT interrupt of DMA stream.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableHtInterrupt(const bool enable) const
	{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
		*reinterpret_cast<volatile unsigned long*>(htieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
		auto& dmaStream = getDmaStream();
		const InterruptMaskingLock interruptMaskingLock;
		dmaStream.CR = (dmaStream.CR & ~DMA_SxCR_HTIE) | (enable == true ? DMA_SxCR_HTIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
	}

	/**
	 * \brief Enables or disables TE interrupt of DMA stream.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableTeInterrupt(const bool enable) const
	{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
		*reinterpret_cast<volatile unsigned long*>(teieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
		auto& dmaStream = getDmaStream();
		const InterruptMaskingLock interruptMaskingLock;
		dmaStream.CR = (dmaStream.CR & ~DMA_SxCR_TEIE) | (enable == true ? DMA_SxCR_TEIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
	}

	/**
	 * \brief Enables or disables DME interrupt of DMA stream.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableDmeInterrupt(const bool enable) const
	{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
		*reinterpret_cast<volatile unsigned long*>(dmeieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
		auto& dmaStream = getDmaStream();
		const InterruptMaskingLock interruptMaskingLock;
		dmaStream.CR = (dmaStream.CR & ~DMA_SxCR_DMEIE) | (enable == true ? DMA_SxCR_DMEIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
	}

	/**
	 * \brief Enables or disables FE interrupt of DMA stream.
	 *
	 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
	 */

	void enableFeInterrupt(const bool enable) const
	{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
		*reinterpret_cast<volatile unsigned long*>(feieBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
		auto& dmaStream = getDmaStream();
		const InterruptMaskingLock interruptMaskingLock;
		dmaStream.FCR = (dmaStream.FCR & ~DMA_SxFCR_FEIE) | (enable == true ? DMA_SxFCR_FEIE : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
	}

	/**
	 * \brief Enables or disables DMA stream.
	 *
	 * \param [in] enable selects whether the stream will be enabled (true) or disabled (false)
	 */

	void enableStream(const bool enable) const
	{
#ifdef DISTORTOS_BITBANDING_SUPPORTED
		*reinterpret_cast<volatile unsigned long*>(enBbAddress_) = enable;
#else	// !def DISTORTOS_BITBANDING_SUPPORTED
		auto& dmaStream = getDmaStream();
		const InterruptMaskingLock interruptMaskingLock;
		dmaStream.CR = (dmaStream.CR & ~DMA_SxCR_EN) | (enable == true ? DMA_SxCR_EN : 0);
#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
	}

	/**
	 * \return true if stream is enabled, false otherwise
	 */

	bool getEnableStream() const
	{
		return getDmaStream().CR & DMA_SxCR_EN;
	}

	/**
	 * \return true if circular mode is enabled, false otherwise
	 */

	bool getCircularMode() const
	{
		return getDmaStream().CR & DMA_SxCR_CIRC;
	}

	/**
	 * \return DmaMode
	 */

	ChipDmaLowLevel::DmaMode getTransferDirection() const
	{
		const auto cr = getDmaStream().CR;

		if ((cr & DMA_SxCR_DIR) == DMA_SxCR_DIR_0)
			return ChipDmaLowLevel::DmaMode::memoryToPeripheral;
		if ((cr & DMA_SxCR_DIR) == DMA_SxCR_DIR_1)
			return ChipDmaLowLevel::DmaMode::peripheralToMemory;

		return ChipDmaLowLevel::DmaMode::memoryToMemory;
	}

	/**
	 * return status flags from corresponding xISR register and shift it to use as for stream 0
	 */

	uint32_t getStatusFlags() const
	{
		const auto isr = *reinterpret_cast<volatile uint32_t*>(dmaBase_ + intStatusOffset_);
		return (isr >> shift_) & DMA_INT_REG_STREAM_MASK;
	}

	/**
	 * \brief Clear flags as for stream 0 to corresponding xIFCR register.
	 *
	 * \param [in] flags to clear (DMA_IFCR_CFEIF, DMA_IFCR_CDMEIF, DMA_IFCR_CTEIF, DMA_IFCR_CHTIF, DMA_IFCR_CTCIF)
	 */

	void clearStatusFlags(uint32_t flags) const
	{
		auto& ifcr = *reinterpret_cast<volatile uint32_t*>(dmaBase_ + intClearOffset_);
		const InterruptMaskingLock interruptMaskingLock;
		ifcr = (flags & DMA_INT_REG_STREAM_MASK) << shift_;
	}

	/**
	 * \return reference to DMA_TypeDef object
	 */

	DMA_TypeDef& getDma() const
	{
		return *reinterpret_cast<DMA_TypeDef*>(dmaBase_);
	}

	/**
	 * \return reference to DMA_Stream_TypeDef object
	 */

	DMA_Stream_TypeDef& getDmaStream() const
	{
		return *reinterpret_cast<DMA_Stream_TypeDef*>(dmaStreamBase_);
	}

private:

	/// base address of DMA peripheral
	uintptr_t dmaBase_;

	/// base address of DMA stream peripheral
	uintptr_t dmaStreamBase_;

#ifdef DISTORTOS_BITBANDING_SUPPORTED

	/// address of bitband alias of TCIE bit in DMA_SxCR register
	uintptr_t tcieBbAddress_;

	/// address of bitband alias of HTIE bit in DMA_SxCR register
	uintptr_t htieBbAddress_;

	/// address of bitband alias of TEIE bit in DMA_SxCR register
	uintptr_t teieBbAddress_;

	/// address of bitband alias of DMEIE bit in DMA_SxCR register
	uintptr_t dmeieBbAddress_;

	/// address of bitband alias of FEIE bit in DMA_SxFCR register
	uintptr_t feieBbAddress_;

	/// address of bitband alias of EN bit in DMA_SxCR register
	uintptr_t enBbAddress_;

#endif	// def DISTORTOS_BITBANDING_SUPPORTED

	/// offset of DMA register with interrupt status
	size_t intStatusOffset_;

	/// offset of DMA register with interrupt clear
	size_t intClearOffset_;

	/// stream shift in interrupt status and clear registers
	uint8_t shift_;
};

/*---------------------------------------------------------------------------------------------------------------------+
| public static objects
+---------------------------------------------------------------------------------------------------------------------*/

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream0Parameters {DMA1_BASE, DMA1_Stream0_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM0};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream1Parameters {DMA1_BASE, DMA1_Stream1_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM1};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream2Parameters {DMA1_BASE, DMA1_Stream2_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM2};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream3Parameters {DMA1_BASE, DMA1_Stream3_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM3};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream4Parameters {DMA1_BASE, DMA1_Stream4_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM4};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream5Parameters {DMA1_BASE, DMA1_Stream5_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM5};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream6Parameters {DMA1_BASE, DMA1_Stream6_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM6};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma1Stream7Parameters {DMA1_BASE, DMA1_Stream7_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM7};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA1_STREAM7_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream0Parameters {DMA2_BASE, DMA2_Stream0_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM0};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM0_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream1Parameters {DMA2_BASE, DMA2_Stream1_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM1};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM1_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream2Parameters {DMA2_BASE, DMA2_Stream2_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM2};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM2_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream3Parameters {DMA2_BASE, DMA2_Stream3_BASE,
		offsetof(DMA_TypeDef, LISR), offsetof(DMA_TypeDef, LIFCR), DMA_INT_REG_SHIFT_STREAM3};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM3_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream4Parameters {DMA2_BASE, DMA2_Stream4_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM4};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM4_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream5Parameters {DMA2_BASE, DMA2_Stream5_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM5};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM5_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream6Parameters {DMA2_BASE, DMA2_Stream6_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM6};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM6_ENABLE

#ifdef CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

const ChipDmaLowLevel::Parameters ChipDmaLowLevel::dma2Stream7Parameters {DMA2_BASE, DMA2_Stream7_BASE,
		offsetof(DMA_TypeDef, HISR), offsetof(DMA_TypeDef, HIFCR), DMA_INT_REG_SHIFT_STREAM7};

#endif	// def CONFIG_CHIP_STM32_DMAV2_DMA2_STREAM7_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

ChipDmaLowLevel::~ChipDmaLowLevel()
{
	if (isStarted() == false)
		return;

	parameters_.enableStream(false);
}

void ChipDmaLowLevel::interruptHandler()
{
	auto& stream = parameters_.getDmaStream();
	const uint32_t isr = parameters_.getStatusFlags();
	const uint32_t isrErrorMask = (stream.FCR & DMA_SxFCR_FEIE ? DMA_ISR_FEIF : 0) |
			(stream.FCR & DMA_SxFCR_DMDIS ? 0 : DMA_ISR_DMEIF) | DMA_ISR_TEIF;

	if ((isr & isrErrorMask) != 0)
	{
		parameters_.clearStatusFlags(isr & isrErrorMask);
		parameters_.enableStream(false);
		chipDmaBase_->transferErrorEvent(decodeErrors(isr & isrErrorMask));
	}
	if ((isr & DMA_ISR_HTIF) != 0 && (stream.CR & DMA_SxCR_HTIE) != 0)
	{
		parameters_.clearStatusFlags(DMA_IFCR_CHTIF);
		chipDmaBase_->halfTransferCompleteEvent();
	}
	if ((isr & DMA_ISR_TCIF) != 0 && (stream.CR & DMA_SxCR_TCIE) != 0)
	{
		parameters_.clearStatusFlags(DMA_IFCR_CTCIF);
		if (!parameters_.getCircularMode())
		{
			parameters_.enableStream(false);
			transferLength_ = {};
		}
		chipDmaBase_->transferCompleteEvent();
	}
}

int ChipDmaLowLevel::start(ChipDmaBase& chipDmaBase, const DmaMode mode, const DataSize srcDataSize,
		const DataSize dstDataSize, const BurstBeats srcBurstBeats, const BurstBeats dstBurstBeats,
		const DmaFifoLevel fifoThreshold, const DmaOptionSet optionBits)
{
	if (isStarted() == true)
		return EBADF;

	if (&parameters_.getDma() != reinterpret_cast<DMA_TypeDef*>(DMA2_BASE) && mode == DmaMode::memoryToMemory)
		return EINVAL;

	if (mode == DmaMode::memoryToMemory && optionBits[DmaOptionSet::circularMode])
		return EINVAL;

	chipDmaBase_ = &chipDmaBase;
	auto& stream = parameters_.getDmaStream();

	if (fifoThreshold != DmaFifoLevel::disable)
		stream.FCR = DMA_SxFCR_FEIE | DMA_SxFCR_DMDIS | static_cast<uint32_t>(fifoThreshold) << DMA_SxFCR_FTH_Pos;

	// mask already configured priority and clear other settings
	stream.CR = (stream.CR & DMA_SxCR_CHSEL_Msk);

	stream.CR |= optionBits[DmaOptionSet::circularMode] << DMA_SxCR_CIRC_Pos |
			optionBits[DmaOptionSet::peripheralFlowController] << DMA_SxCR_PFCTRL_Pos |
			optionBits[DmaOptionSet::doubleBufferMode] << DMA_SxCR_DBM_Pos |
			optionBits[DmaOptionSet::fixPeripheralIncrementOffset] << DMA_SxCR_PINCOS_Pos;

	const auto srcDataSizeReg = static_cast<uint32_t>(srcDataSize);
	const auto dstDataSizeReg = static_cast<uint32_t>(dstDataSize);
	const auto srcBurstBeatsReg = static_cast<uint32_t>(srcBurstBeats);
	const auto dstBurstBeatsReg = static_cast<uint32_t>(dstBurstBeats);

	if (mode == DmaMode::memoryToPeripheral)
	{
		stream.CR |= optionBits[DmaOptionSet::srcIncr] << DMA_SxCR_MINC_Pos |
				optionBits[DmaOptionSet::dstIncr] << DMA_SxCR_PINC_Pos |
				srcDataSizeReg << DMA_SxCR_MSIZE_Pos | dstDataSizeReg << DMA_SxCR_PSIZE_Pos |
				srcBurstBeatsReg << DMA_SxCR_MBURST_Pos | dstBurstBeatsReg << DMA_SxCR_PBURST_Pos | DMA_SxCR_DIR_0;
	}
	else
	{
		stream.CR |= optionBits[DmaOptionSet::srcIncr] << DMA_SxCR_PINC_Pos |
				optionBits[DmaOptionSet::dstIncr] << DMA_SxCR_MINC_Pos |
				srcDataSizeReg << DMA_SxCR_PSIZE_Pos | dstBurstBeatsReg << DMA_SxCR_MSIZE_Pos |
				srcBurstBeatsReg << DMA_SxCR_PBURST_Pos | dstBurstBeatsReg << DMA_SxCR_MBURST_Pos;
		if (mode == DmaMode::memoryToMemory)
			stream.CR |= DMA_SxCR_DIR_1;
	}

	parameters_.enableDmeInterrupt(fifoThreshold == DmaFifoLevel::disable);
	parameters_.enableTeInterrupt(true);
	parameters_.enableHtInterrupt(true);
	parameters_.enableTcInterrupt(true);

	return 0;
}

int ChipDmaLowLevel::startTransfer(const uintptr_t srcAddress, const uintptr_t dstAddress, const size_t length)
{
	if (srcAddress == 0 || dstAddress == 0)
		return EINVAL;

	if (isStarted() == false)
		return EBADF;

	if (isTransferInProgress() == true)
		return EBUSY;

	if (checkLengthResctriction(length))
		return EINVAL;

	if (checkMemoryBurst(parameters_.getTransferDirection() == DmaMode::memoryToPeripheral ? srcAddress : dstAddress,
			length))
		return EINVAL;

	auto& stream = parameters_.getDmaStream();
	stream.NDTR = length;
	if (parameters_.getTransferDirection() == DmaMode::memoryToPeripheral)
	{
		stream.M0AR = srcAddress;
		stream.PAR = dstAddress;
	}
	else
	{
		stream.PAR = srcAddress;
		stream.M0AR = dstAddress;
	}

	transferLength_ = length;
	// clears TC, HT, TE, DM, CF flags
	parameters_.clearStatusFlags(DMA_IFCR_CFEIF | DMA_IFCR_CDMEIF | DMA_IFCR_CTEIF | DMA_IFCR_CHTIF | DMA_IFCR_CTCIF);
	parameters_.enableStream(true);

	return 0;
}

int ChipDmaLowLevel::updateNextBuffer(const uintptr_t address, const size_t length)
{
	if (address == 0)
		return EINVAL;

	if (length != transferLength_)
		return EINVAL;

	if (parameters_.getEnableStream() == false)
		return EBADF;

	auto& stream = parameters_.getDmaStream();

	if ((stream.CR & DMA_SxCR_DBM) == 0)
		return EBADF;

	if (checkMemoryBurst(address, transferLength_))
		return EINVAL;

	if (stream.CR & DMA_SxCR_CT)
		stream.M0AR = address;
	else
		stream.M1AR = address;

	return 0;
}

size_t ChipDmaLowLevel::stopTransfer()
{
	parameters_.enableStream(false);

	while (parameters_.getEnableStream() == true);

	const auto transferLength = transferLength_ - parameters_.getDmaStream().NDTR;
	transferLength_ = {};

	return transferLength;
}

int ChipDmaLowLevel::stop()
{
	if (isStarted() == false)
		return EBADF;

	if (isTransferInProgress() == true)
		return EBUSY;

	parameters_.enableStream(false);
	chipDmaBase_ = nullptr;

	return 0;
}

int ChipDmaLowLevel::streamMapping(const uint8_t channel)
{
	if (isStarted() == true)
		return EBADF;

	if (channel > channelMax)
		return EINVAL;

	auto& stream = parameters_.getDmaStream();
	stream.CR = (stream.CR & ~DMA_SxCR_CHSEL_Msk) | channel << DMA_SxCR_CHSEL_Pos;

	return 0;
}

int ChipDmaLowLevel::streamPriority(const uint8_t priority)
{
	if (isStarted() == true)
		return EBADF;

	if (priority > maxPriority)
		return EINVAL;

	auto& stream = parameters_.getDmaStream();
	stream.CR = (stream.CR & ~DMA_SxCR_PL_Msk) | priority << DMA_SxCR_PL_Pos;

	return 0;
}

/*---------------------------------------------------------------------------------------------------------------------+
| private functions
+---------------------------------------------------------------------------------------------------------------------*/

int ChipDmaLowLevel::checkLengthResctriction(const size_t length)
{
	static const std::tuple<DataSize, DataSize, size_t> associations[]
	{
			{DataSize::byte, DataSize::halfWord, 2},
			{DataSize::byte, DataSize::word, 4},
			{DataSize::halfWord, DataSize::word, 2},
	};

	if (length < minTransferLength || length > maxTransferLength)
		return EINVAL;

	const auto cr = parameters_.getDmaStream().CR;
	const auto psize = static_cast<DataSize>((cr & DMA_SxCR_PSIZE_Msk) >> DMA_SxCR_PSIZE_Pos);
	const auto msize = static_cast<DataSize>((cr & DMA_SxCR_MSIZE_Msk) >> DMA_SxCR_MSIZE_Pos);

	if (psize >= msize)
		return 0;

	for (auto& association : associations)
		if ((std::get<0>(association) == psize) && (std::get<1>(association) == msize) &&
			(length % std::get<2>(association)) == 0)
			return 0;

	return EINVAL;
}

int ChipDmaLowLevel::checkMemoryBurst(const uintptr_t begin, const size_t length)
{
	const auto cr = parameters_.getDmaStream().CR;
	const auto size = (cr & DMA_SxCR_MSIZE_Msk) >> DMA_SxCR_MSIZE_Pos;
	const auto transferSize = size == 0 ? 1 : size == 1 ? 2 : 4;
	const auto burst = static_cast<BurstBeats>((cr & DMA_SxCR_MBURST_Msk) >> DMA_SxCR_MBURST_Pos);
	const auto burstExp = burst == BurstBeats::incr4 ? 2 : burst == BurstBeats::incr8 ? 3 :
			burst == BurstBeats:: incr16 ? 4 : 0;

	const auto end = begin + (length << size) - 1;

	// check if cross 1 KiB boundary
	if ((begin / 1024) != (end / 1024))
	{
		const auto burstLength = transferSize << burstExp;

		if ((begin & (burstLength - 1)) != 0)
			return EINVAL;
	}

	return 0;
}

}	// namespace chip

}	// namespace distortos
