/**
 * \file
 * \brief ChipUartDmaV1Transfer class implementation for USARTv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/ChipUartDmaV1Transfer.hpp"

#ifdef CONFIG_CHIP_STM32_DMAV1

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

int ChipUartDmaTransfer::start(ChipUartDmaLowLevel& chipUartDmaLowLevel, const ChipDmaLowLevel::DataSize dataSize,
		const bool transmitDir)
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

	return chipDmaLowLevel_.start(*this, mode, dataSize, dataSize, optionBits);
}

int ChipUartDmaTransfer::startTransfer(const uintptr_t srcAddress, const uintptr_t dstAddress, const size_t length)
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

void ChipUartDmaTransfer::transferErrorEvent()
{
	return receivingEn_ ? chipUartDmaLowLevel_->rxDmaTransferError() : chipUartDmaLowLevel_->txDmaTransferError();
}

}	// namespace chip

}	// namespace distortos

#endif	// CONFIG_CHIP_STM32_DMAV1
