/**
 * \file
 * \brief ChipUartDmaV2Transfer class implementation for USARTv1 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipUartDmaV2Transfer.hpp"

#ifdef CONFIG_CHIP_STM32_DMAV2

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

ChipUartDmaTransfer::~ChipUartDmaTransfer()
{
	chipDmaLowLevel_.stopTransfer();
	chipDmaLowLevel_.stop();
}

int ChipUartDmaTransfer::start(ChipUartDmaLowLevel& chipUartDmaLowLevel, const uint8_t busWidth, const bool transmitDir)
{
	ChipDmaLowLevel::DmaOptionSet optionBits {};
	ChipDmaLowLevel::DmaMode mode {};

	receivingEn_ = transmitDir;

	if (receivingEn_)
	{
		optionBits[ChipDmaLowLevel::DmaOptionSet::dstIncr] = true;
		mode = ChipDmaLowLevel::DmaMode::peripheralToMemory;
	}
	else
	{
		optionBits[ChipDmaLowLevel::DmaOptionSet::srcIncr] = true;
		mode = ChipDmaLowLevel::DmaMode::memoryToPeripheral;
	}

	chipUartDmaLowLevel_ = &chipUartDmaLowLevel;

	const auto dmaDataSize = busWidth == 8 ? ChipDmaLowLevel::DataSize::byte : ChipDmaLowLevel::DataSize::halfWord;
	return chipDmaLowLevel_.start(*this, mode, dmaDataSize, dmaDataSize, ChipDmaLowLevel::BurstBeats::single,
			ChipDmaLowLevel::BurstBeats::single, ChipDmaLowLevel::DmaFifoLevel::disable, optionBits);
}

int ChipUartDmaTransfer::startTransfer(uintptr_t srcAddress, uintptr_t dstAddress, size_t length)
{
	return chipDmaLowLevel_.startTransfer(srcAddress, dstAddress, length);
}

size_t ChipUartDmaTransfer::stopTransfer()
{
	return chipDmaLowLevel_.stopTransfer();
}

/*---------------------------------------------------------------------------------------------------------------------+
| private functions
+---------------------------------------------------------------------------------------------------------------------*/

void ChipUartDmaTransfer::transferCompleteEvent()
{
	return receivingEn_ ? chipUartDmaLowLevel_->rxDmaTransferComplete() : chipUartDmaLowLevel_->txDmaTransferComplete();
}

void ChipUartDmaTransfer::halfTransferCompleteEvent()
{

}

void ChipUartDmaTransfer::transferErrorEvent(ErrorSet)
{
	return receivingEn_ ? chipUartDmaLowLevel_->rxDmaTransferError() : chipUartDmaLowLevel_->txDmaTransferError();
}

}	// namespace chip

}	// namespace distortos

#endif	// CONFIG_CHIP_STM32_DMAV2
