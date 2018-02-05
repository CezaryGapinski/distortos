/**
 * \file
 * \brief ChipUartLowLevel class header for USARTv2 in STM32
 *
 * \author Copyright (C) 2016-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTLOWLEVEL_HPP_
#define SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTLOWLEVEL_HPP_

#include "distortos/devices/communication/UartLowLevel.hpp"

#include "distortos/devices/communication/UartBase.hpp"

#include "distortos/chip/getBusFrequency.hpp"
#include "distortos/chip/STM32-bit-banding.h"

#include "distortos/distortosConfiguration.h"

namespace distortos
{

namespace chip
{

/**
 * ChipUartLowLevel class is a low-level UART driver for USARTv2 in STM32
 *
 * \ingroup devices
 */

class ChipUartLowLevel : public devices::UartLowLevel
{
public:

	/// minimum allowed value for UART character length
#ifdef CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT
	constexpr static uint8_t minCharacterLength {6};
#else	// !def CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT
	constexpr static uint8_t minCharacterLength {7};
#endif	// !def CONFIG_CHIP_STM32_USARTV2_HAS_CR1_M1_BIT

	/// maximum allowed value for UART character length
	constexpr static uint8_t maxCharacterLength {9};

/*---------------------------------------------------------------------------------------------------------------------+
| public types
+---------------------------------------------------------------------------------------------------------------------*/

	/// parameters for construction of UART low-level drivers
	class Parameters
	{
	public:

	#ifdef DISTORTOS_BITBANDING_SUPPORTED

		/**
		 * \brief Parameters's constructor
		 *
		 * \param [in] uartBase is a base address of UART peripheral
		 * \param [in] rccEnBb is an address of bitband alias of appropriate U[S]ARTxEN bit in RCC register
		 * \param [in] rccRstBb is an address of bitband alias of appropriate U[S]ARTxRST bit in RCC register
		 */

		constexpr Parameters(const uintptr_t uartBase, const uintptr_t rccEnBbAddress, const uintptr_t rccRstBbAddress) :
				uartBase_{uartBase},
				peripheralFrequency_{getBusFrequency(uartBase)},
				rxneieBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR1, USART_CR1_RXNEIE)},
				tcieBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR1, USART_CR1_TCIE)},
				txeieBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR1, USART_CR1_TXEIE)},
				peieBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR1, USART_CR1_PEIE)},
				eieBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR3, USART_CR3_EIE)},
				ddreBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR3, USART_CR3_DDRE)},
				dmatBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR3, USART_CR3_DMAT)},
				dmarBbAddress_{STM32_BITBAND_IMPLEMENTATION(uartBase, USART_TypeDef, CR3, USART_CR3_DMAR)},
				rccEnBbAddress_{rccEnBbAddress},
				rccRstBbAddress_{rccRstBbAddress}
		{

		}

	#else	// !def DISTORTOS_BITBANDING_SUPPORTED

		/**
		 * \brief Parameters's constructor
		 *
		 * \param [in] uartBase is a base address of UART peripheral
		 * \param [in] rccEnOffset is the offset of RCC register with appropriate U[S]ARTxEN bit, bytes
		 * \param [in] rccEnBitmask is the bitmask of appropriate U[S]ARTxEN bit in RCC register at \a rccEnOffset offset
		 * \param [in] rccRstOffset is the offset of RCC register with appropriate U[S]ARTxRST bit, bytes
		 * \param [in] rccRstBitmask is the bitmask of appropriate U[S]ARTxRST bit in RCC register at \a rccRstOffset offset
		 */

		constexpr Parameters(const uintptr_t uartBase, const size_t rccEnOffset, const uint32_t rccEnBitmask,
				const size_t rccRstOffset, const uint32_t rccRstBitmask) :
						uartBase_{uartBase},
						peripheralFrequency_{getBusFrequency(uartBase)},
						rccEnBitmask_{rccEnBitmask},
						rccEnOffset_{rccEnOffset},
						rccRstBitmask_{rccRstBitmask},
						rccRstOffset_{rccRstOffset}
		{

		}

	#endif	// !def DISTORTOS_BITBANDING_SUPPORTED

		/**
		 * \brief Enables or disables peripheral clock in RCC.
		 *
		 * \param [in] enable selects whether the clock will be enabled (true) or disabled (false)
		 */

		void enablePeripheralClock(const bool enable) const;

		/**
		 * \brief Enables or disables RXNE interrupt of UART.
		 *
		 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
		 */

		void enableRxneInterrupt(const bool enable) const;

		/**
		 * \brief Enables or disables TC interrupt of UART.
		 *
		 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
		 */

		void enableTcInterrupt(const bool enable) const;

		/**
		 * \brief Enables or disables TXE interrupt of UART.
		 *
		 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
		 */

		void enableTxeInterrupt(const bool enable) const;

		/**
		 * \brief Enables or disables PE interrupt of UART.
		 *
		 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
		 */

		void enablePeInterrupt(const bool enable) const;

		/**
		 * \brief Enables or disables EI of UART.
		 *
		 * \param [in] enable selects whether the interrupt will be enabled (true) or disabled (false)
		 */

		void enableEInterrupt(const bool enable) const;

		/**
		 * \brief Enables or disables DMA on reception error of UART.
		 *
		 * \param [in] enable selects whether the DMA will be disabled (true) or not disabled (false)
		 */

		void disableDmaOnReceptionError(const bool enable) const;

		/**
		 * \brief Enables or disables DMA transmitter of UART.
		 *
		 * \param [in] enable selects whether the DMA transmitter will be enabled (true) or not disabled (false)
		 */

		void enableDmaTransmiter(const bool enable) const;

		/**
		 * \brief Enables or disables DMA receiver of UART.
		 *
		 * \param [in] enable selects whether the DMA receiver will be enabled (true) or not disabled (false)
		 */

		void enableDmaReceiver(const bool enable) const;

		/**
		 * \return character length, bits
		 */

		uint8_t getCharacterLength() const;

		/**
		 * \return peripheral clock frequency, Hz
		 */

		uint32_t getPeripheralFrequency() const
		{
			return peripheralFrequency_;
		}

		/**
		 * \return reference to USART_TypeDef object
		 */

		USART_TypeDef& getUart() const
		{
			return *reinterpret_cast<USART_TypeDef*>(uartBase_);
		}

		/**
		 * \return DMA transmitter enable status
		 */

		bool isDmaTrasmitterEnabled() const;

		/**
		 * \return DMA transmitter enable status
		 */

		bool isDmaReceiverEnabled() const;

		/**
		 * \brief Resets all peripheral's registers via RCC
		 *
		 * \note Peripheral clock must be enabled in RCC for this operation to work.
		 */

		void resetPeripheral() const;

	private:

		/// base address of UART peripheral
		uintptr_t uartBase_;

		/// peripheral clock frequency, Hz
		uint32_t peripheralFrequency_;

	#ifdef DISTORTOS_BITBANDING_SUPPORTED

		/// address of bitband alias of RXNEIE bit in USART_CR1 register
		uintptr_t rxneieBbAddress_;

		/// address of bitband alias of TCIE bit in USART_CR1 register
		uintptr_t tcieBbAddress_;

		/// address of bitband alias of TXEIE bit in USART_CR1 register
		uintptr_t txeieBbAddress_;

		/// address of bitband alias of PEIE bit in USART_CR1 register
		uintptr_t peieBbAddress_;

		/// address of bitband alias of EIE bit in USART_CR3 register
		uintptr_t eieBbAddress_;

		/// address of bitband alias of DDRE bit in USART_CR3 register
		uintptr_t ddreBbAddress_;

		/// address of bitband alias of DMAT bit in USART_CR3 register
		uintptr_t dmatBbAddress_;

		/// address of bitband alias of DMAR bit in USART_CR3 register
		uintptr_t dmarBbAddress_;

		/// address of bitband alias of appropriate U[S]ARTxEN bit in RCC register
		uintptr_t rccEnBbAddress_;

		/// address of bitband alias of appropriate U[S]ARTxRST bit in RCC register
		uintptr_t rccRstBbAddress_;

	#else	// !def DISTORTOS_BITBANDING_SUPPORTED

		/// bitmask of appropriate U[S]ARTxEN bit in RCC register at \a rccEnOffset_ offset
		uint32_t rccEnBitmask_;

		/// offset of RCC register with appropriate U[S]ARTxEN bit, bytes
		size_t rccEnOffset_;

		/// bitmask of appropriate U[S]ARTxRST bit in RCC register at \a rccRstOffset_ offset
		uint32_t rccRstBitmask_;

		/// offset of RCC register with appropriate U[S]ARTxRST bit, bytes
		size_t rccRstOffset_;

	#endif	// !def DISTORTOS_BITBANDING_SUPPORTED
	};

#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

	/// parameters for construction of UART low-level driver for USART1
	static const Parameters usart1Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

	/// parameters for construction of UART low-level driver for USART2
	static const Parameters usart2Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

	/// parameters for construction of UART low-level driver for USART3
	static const Parameters usart3Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

	/// parameters for construction of UART low-level driver for UART4
	static const Parameters uart4Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

	/// parameters for construction of UART low-level driver for USART4
	static const Parameters usart4Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

	/// parameters for construction of UART low-level driver for UART5
	static const Parameters uart5Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

	/// parameters for construction of UART low-level driver for USART5
	static const Parameters usart5Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

	/// parameters for construction of UART low-level driver for USART6
	static const Parameters usart6Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

	/// parameters for construction of UART low-level driver for UART7
	static const Parameters uart7Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

	/// parameters for construction of UART low-level driver for USART7
	static const Parameters usart7Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

	/// parameters for construction of UART low-level driver for UART8
	static const Parameters uart8Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

	/// parameters for construction of UART low-level driver for USART8
	static const Parameters usart8Parameters;

#endif	// def CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

	/**
	 * \brief ChipUartLowLevel's constructor
	 *
	 * \param [in] parameters is a reference to object with peripheral parameters
	 */

	constexpr explicit ChipUartLowLevel(const Parameters& parameters) :
			parameters_{parameters},
			uartBase_{}
	{

	}

	/**
	 * \brief ChipUartLowLevel's destructor
	 *
	 * Does nothing if driver is already stopped. If it's not, performs forced stop of operation.
	 */

	~ChipUartLowLevel() override;

	/**
	 * \brief Starts low-level UART driver.
	 *
	 * Not all combinations of data format are supported. The general rules are:
	 * - if parity control is disabled, character length must not be \a minCharacterLength,
	 * - if parity control is enabled, character length must not be 9.
	 *
	 * \param [in] uartBase is a reference to UartBase object that will be associated with this one
	 * \param [in] baudRate is the desired baud rate, bps
	 * \param [in] characterLength selects character length, bits, [minCharacterLength; maxCharacterLength]
	 * \param [in] parity selects parity
	 * \param [in] _2StopBits selects whether 1 (false) or 2 (true) stop bits are used
	 *
	 * \return pair with return code (0 on success, error code otherwise) and real baud rate; error codes:
	 * - EBADF - the driver is not stopped;
	 * - EINVAL - selected baud rate and/or format are invalid;
	 */

	std::pair<int, uint32_t> start(devices::UartBase& uartBase, uint32_t baudRate, uint8_t characterLength,
			devices::UartParity parity, bool _2StopBits) override;

protected:

	/**
	 * \return true if driver is started, false otherwise
	 */

	bool isStarted() const
	{
		return uartBase_ != nullptr;
	}

	/// reference to configuration parameters
	const Parameters& parameters_;

	/// pointer to UartBase object associated with this one
	devices::UartBase* uartBase_;
};

/**
 * \brief Decode value of USART_ISR register to devices::UartBase::ErrorSet
 *
 * \param [in] isr is the value of USART_ISR register that will be decoded
 *
 * \return devices::UartBase::ErrorSet with errors decoded from \a isr
 */

devices::UartBase::ErrorSet decodeErrors(const uint32_t isr);

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_PERIPHERALS_USARTV2_INCLUDE_DISTORTOS_CHIP_CHIPUARTLOWLEVEL_HPP_
