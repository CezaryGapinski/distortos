/**
 * \file
 * \brief Implementation of RCC-related functions for STM32F4
 *
 * \author Copyright (C) 2015-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/chip/STM32F4-RCC.hpp"

#include "distortos/chip/CMSIS-proxy.h"
#include "distortos/chip/STM32-bit-banding.h"

#include <array>

#include <cerrno>

#if defined(CONFIG_CHIP_STM32F427) || defined(CONFIG_CHIP_STM32F429) || defined(CONFIG_CHIP_STM32F437) || \
		defined(CONFIG_CHIP_STM32F439) || defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || \
		defined(CONFIG_CHIP_STM32F479)
#define RCC_DCKCFGR_PLLSAIDIVR_DIV2					0x00000000U
#define RCC_DCKCFGR_PLLSAIDIVR_DIV4					0x00010000U
#define RCC_DCKCFGR_PLLSAIDIVR_DIV8					0x00020000U
#define RCC_DCKCFGR_PLLSAIDIVR_DIV16					0x00030000U
#endif	// defined(CONFIG_CHIP_STM32F427) || defined(CONFIG_CHIP_STM32F429) || defined(CONFIG_CHIP_STM32F437) ||
		// defined(CONFIG_CHIP_STM32F439) || defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) ||
		// defined(CONFIG_CHIP_STM32F479)

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

int configureAhbClockDivider(const uint16_t hpre)
{
	static const std::pair<decltype(hpre), decltype(RCC_CFGR_HPRE_DIV1)> associations[]
	{
			{hpreDiv1, RCC_CFGR_HPRE_DIV1},
			{hpreDiv2, RCC_CFGR_HPRE_DIV2},
			{hpreDiv4, RCC_CFGR_HPRE_DIV4},
			{hpreDiv8, RCC_CFGR_HPRE_DIV8},
			{hpreDiv16, RCC_CFGR_HPRE_DIV16},
			{hpreDiv64, RCC_CFGR_HPRE_DIV64},
			{hpreDiv128, RCC_CFGR_HPRE_DIV128},
			{hpreDiv256, RCC_CFGR_HPRE_DIV256},
			{hpreDiv512, RCC_CFGR_HPRE_DIV512},
	};

	for (auto& association : associations)
		if (association.first == hpre)
		{
			RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_HPRE) | association.second;
			return 0;
		}

	return EINVAL;
}

int configureApbClockDivider(const bool ppre2, const uint8_t ppre)
{
	static const std::pair<decltype(ppre), std::array<decltype(RCC_CFGR_PPRE1_DIV1), 2>> associations[]
	{
			{ppreDiv1, {RCC_CFGR_PPRE1_DIV1, RCC_CFGR_PPRE2_DIV1}},
			{ppreDiv2, {RCC_CFGR_PPRE1_DIV2, RCC_CFGR_PPRE2_DIV2}},
			{ppreDiv4, {RCC_CFGR_PPRE1_DIV4, RCC_CFGR_PPRE2_DIV4}},
			{ppreDiv8, {RCC_CFGR_PPRE1_DIV8, RCC_CFGR_PPRE2_DIV8}},
			{ppreDiv16, {RCC_CFGR_PPRE1_DIV16, RCC_CFGR_PPRE2_DIV16}},
	};

	for (auto& association : associations)
		if (association.first == ppre)
		{
			static const decltype(RCC_CFGR_PPRE1) masks[] {RCC_CFGR_PPRE1, RCC_CFGR_PPRE2};
			RCC->CFGR = (RCC->CFGR & ~masks[ppre2]) | association.second[ppre2];
			return 0;
		}

	return EINVAL;
}

#if defined(CONFIG_CHIP_STM32F427) || defined(CONFIG_CHIP_STM32F429) || defined(CONFIG_CHIP_STM32F437) || \
		defined(CONFIG_CHIP_STM32F439) || defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || \
		defined(CONFIG_CHIP_STM32F479)
int configureLcdClockDividers(uint8_t pllsair, uint8_t pllsaidivr)
{
	if (pllsair < minPllSair || pllsair > maxPllSair)
		return EINVAL;

	static const std::pair<decltype(pllsaidivr), decltype(RCC_DCKCFGR_PLLSAIDIVR_DIV2)> associations[]
	{
			{pllsaiDivr2, RCC_DCKCFGR_PLLSAIDIVR_DIV2},
			{pllsaiDivr4, RCC_DCKCFGR_PLLSAIDIVR_DIV4},
			{pllsaiDivr8, RCC_DCKCFGR_PLLSAIDIVR_DIV8},
			{pllsaiDivr16, RCC_DCKCFGR_PLLSAIDIVR_DIV16},
	};

	for (auto& association : associations)
		if (association.first == pllsaidivr)
		{
			RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR) | association.second;
			RCC->PLLSAICFGR = (RCC->PLLSAICFGR & ~RCC_PLLSAICFGR_PLLSAIR) | pllsair << RCC_PLLSAICFGR_PLLSAIR_Pos;
			return 0;
		}

	return EINVAL;
}

int enablePllSai(uint16_t pllsain)
{
	if (pllsain < minPllSain || pllsain > maxPllSain)
		return EINVAL;

	RCC->PLLSAICFGR = (RCC->PLLSAICFGR & ~RCC_PLLSAICFGR_PLLSAIN) | pllsain << RCC_PLLSAICFGR_PLLSAIN_Pos;
	STM32_BITBAND(RCC, CR, PLLSAION) = 1;
	while (STM32_BITBAND(RCC, CR, PLLSAIRDY) == 0);	// wait until PLLSAI is stable
	return 0;
}

void disablePllSai()
{
	STM32_BITBAND(RCC, CR, PLLSAION) = 0;
}
#endif	// defined(CONFIG_CHIP_STM32F427) || defined(CONFIG_CHIP_STM32F429) || defined(CONFIG_CHIP_STM32F437) ||
		// defined(CONFIG_CHIP_STM32F439) || defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) ||
		// defined(CONFIG_CHIP_STM32F479)

void configurePllClockSource(const bool hse)
{
	STM32_BITBAND(RCC, PLLCFGR, PLLSRC) = hse;
}

int configurePllInputClockDivider(const uint8_t pllm)
{
	if (pllm < minPllm || pllm > maxPllm)
		return EINVAL;

	RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLM) | pllm << RCC_PLLCFGR_PLLM_Pos;
	return 0;
}

void disableHse()
{
	STM32_BITBAND(RCC, CR, HSEON) = 0;
}

void disablePll()
{
	STM32_BITBAND(RCC, CR, PLLON) = 0;
}

void enableHse(const bool bypass)
{
	STM32_BITBAND(RCC, CR, HSEBYP) = bypass;
	STM32_BITBAND(RCC, CR, HSEON) = 1;
	while (STM32_BITBAND(RCC, CR, HSERDY) == 0);	// wait until HSE oscillator is stable
}

#if defined(CONFIG_CHIP_STM32F412) || defined(CONFIG_CHIP_STM32F413) || defined(CONFIG_CHIP_STM32F423) || \
		defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)
int enablePll(const uint16_t plln, const uint8_t pllp, const uint8_t pllq, const uint8_t pllr)
#else	// !defined(CONFIG_CHIP_STM32F412) && !defined(CONFIG_CHIP_STM32F413) && !defined(CONFIG_CHIP_STM32F423) &&
		// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)
int enablePll(const uint16_t plln, const uint8_t pllp, const uint8_t pllq)
#endif	// !defined(CONFIG_CHIP_STM32F412) && !defined(CONFIG_CHIP_STM32F413) && !defined(CONFIG_CHIP_STM32F423) &&
		// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)
{
	if (plln < minPlln || plln > maxPlln ||
			(pllp != pllpDiv2 && pllp != pllpDiv4 && pllp != pllpDiv6 && pllp != pllpDiv8) ||
			pllq < minPllq || pllq > maxPllq)
		return EINVAL;

#if defined(CONFIG_CHIP_STM32F412) || defined(CONFIG_CHIP_STM32F413) || defined(CONFIG_CHIP_STM32F423) || \
		defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)

	if (pllr < minPllr || pllr > maxPllr)
		return EINVAL;

	RCC->PLLCFGR = (RCC->PLLCFGR & ~(RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLR)) |
			plln << RCC_PLLCFGR_PLLN_Pos | (pllp / 2 - 1) << RCC_PLLCFGR_PLLP_Pos | pllq << RCC_PLLCFGR_PLLQ_Pos |
			pllr << RCC_PLLCFGR_PLLR_Pos;

#else	// !defined(CONFIG_CHIP_STM32F412) && !defined(CONFIG_CHIP_STM32F413) && !defined(CONFIG_CHIP_STM32F423) &&
		// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)

	RCC->PLLCFGR = (RCC->PLLCFGR & ~(RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ)) |
			plln << RCC_PLLCFGR_PLLN_Pos | (pllp / 2 - 1) << RCC_PLLCFGR_PLLP_Pos | pllq << RCC_PLLCFGR_PLLQ_Pos;

#endif	// !defined(CONFIG_CHIP_STM32F412) && !defined(CONFIG_CHIP_STM32F413) && !defined(CONFIG_CHIP_STM32F423) &&
		// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)

	STM32_BITBAND(RCC, CR, PLLON) = 1;
	while (STM32_BITBAND(RCC, CR, PLLRDY) == 0);	// wait until PLL is stable
	return 0;
}

void switchSystemClock(const SystemClockSource source)
{
	const auto sourceValue = static_cast<uint32_t>(source);
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | sourceValue << RCC_CFGR_SW_Pos;
	while ((RCC->CFGR & RCC_CFGR_SWS) != sourceValue << RCC_CFGR_SWS_Pos);
}

}	// namespace chip

}	// namespace distortos
