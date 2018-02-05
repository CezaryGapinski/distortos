/**
 * \file
 * \brief ChipUartDmaV1Transfer class header for USARTv2 in STM32
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTDMAV1TRANSFER_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTDMAV1TRANSFER_HPP_

#include "distortos/distortosConfiguration.h"

#ifdef CONFIG_CHIP_STM32_DMAV1

#include "distortos/chip/ChipDmaLowLevel.hpp"
#include "distortos/chip/ChipUartDmaV1LowLevel.hpp"

namespace distortos
{

namespace chip
{

class ChipUartDmaLowLevel;

/**
 * \brief ChipUartDmaTransfer is a class used to transfer data via UART with usage of DMA low-Level driver
 *
 * \ingroup devices
 */

class ChipUartDmaTransfer : private ChipDmaBase
{
public:

	/**
	 * \brief ChipUartDmaTransfer's constructor
	 *
	 * \param [in] chipDmaLowLevel is a reference to object with DMA low-level driver
	 */

	constexpr explicit ChipUartDmaTransfer(ChipDmaLowLevel& chipDmaLowLevel) :
		chipUartDmaLowLevel_{},
		chipDmaLowLevel_{chipDmaLowLevel},
		receivingEn_{}
	{

	}

	/**
	 * \brief ChipUartDmaTransfer destructor
	 *
	 * Does nothing if driver is already stopped. If it's not, performs forced stop of operation.
	 */

	~ChipUartDmaTransfer() override;

	/**
	 * \brief Configure UART DMA transfer low-level driver.
	 *
	 * \param [in] chipUartDmaLowLevel is reference to ChipUartDmaLowLevel object
	 * \param [in] busWidth is bus width used to data transfer
	 * \param [in] receivingEn selects whether receiving (true) or transmitting (false) direction is used
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - selected options are invalid;
	 */

	int start(ChipUartDmaLowLevel& chipUartDmaLowLevel, ChipDmaLowLevel::DataSize dataSize, bool receivingEn);

	/**
	 * \brief Starts transfer operation.
	 *
	 * This function returns immediately. When the operation is finished (expected number of data were written),
	 * ChipDmaBase::transferCompleteEvent() will be executed. If error occurs transferErrorEvent() will be executed.
	 *
	 * \param [in] srcAddress is a source memory buffer address
	 * \param [in] dstAddress is a destination memory buffer address
	 * \param [in] length is a length of data to transfer
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - write is in progress;
	 * - EINVAL - \a buffer and/or \a size are invalid;
	 */

	int startTransfer(uintptr_t srcAddress, uintptr_t dstAddress, size_t length);

	/**
	 * \brief Stops transfer operation.
	 *
	 * This function waits for finishing last data after stops transfer.
	 * After this call ChipDmaBase::transferCompleteEvent() will not be executed.
	 *
	 * \return number of data transfered by low-level DMA driver
	 *
	 */

	size_t stopTransfer();

private:

	/**
	 * \brief "Half transfer complete" event
	 *
	 * Called by low-level DMA driver when the half of transfer is physically finished.
	 *
	 * Does nothing.
	 *
	 */

	void halfTransferCompleteEvent() override;

	/**
	 * \brief "Transfer complete" event
	 *
	 * Called by low-level DMA driver when the transfer is physically finished.
	 *
	 */

	void transferCompleteEvent() override;

	/**
	 * \brief "Transfer error" event
	 *
	 * Called by low-level DMA driver when transfer error occurs.
	 */

	void transferErrorEvent() override;

	/// pointer to ChipUartDmaLowLevel object associated with this one
	ChipUartDmaLowLevel* chipUartDmaLowLevel_;

	/// reference to ChipDmaLowLevel object associated with this one
	ChipDmaLowLevel& chipDmaLowLevel_;

	/// "receiving direction" flag
	bool receivingEn_;
};

}	// namespace chip

}	// namespace distortos

#endif	// CONFIG_CHIP_STM32_DMAV1

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTDMAV1TRANSFER_HPP_
