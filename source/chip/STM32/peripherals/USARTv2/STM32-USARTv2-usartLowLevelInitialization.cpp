/**
 * \file
 * \brief chip::usartLowLevelInitialization() definition for USARTv2 in STM32
 *
 * \author Copyright (C) 2016-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "STM32-USARTv2-usartLowLevelInitialization.hpp"

#include "distortos/chip/CMSIS-proxy.h"

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void usartLowLevelInitialization()
{
#ifdef CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE
	NVIC_SetPriority(USART1_IRQn, {});
	NVIC_EnableIRQ(USART1_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART1_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE
	NVIC_SetPriority(USART2_IRQn, {});
	NVIC_EnableIRQ(USART2_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART2_ENABLE

#if defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART8_COMBINED_INTERRUPT)

#if defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || \
		defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE) || \
		defined(CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE)
	NVIC_SetPriority(USART3_8_IRQn, {});
	NVIC_EnableIRQ(USART3_8_IRQn);
#endif	// defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE)

#elif defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART6_COMBINED_INTERRUPT)

#if defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || \
		defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE)
	NVIC_SetPriority(USART3_6_IRQn, {});
	NVIC_EnableIRQ(USART3_6_IRQn);
#endif	// defined(CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) ||
		// defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE)

#else	// !defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART8_COMBINED_INTERRUPT) &&
		// !defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART6_COMBINED_INTERRUPT)

#ifdef CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE
	NVIC_SetPriority(USART3_IRQn, {});
	NVIC_EnableIRQ(USART3_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART3_ENABLE

#if defined(CONFIG_CHIP_STM32_USARTV2_USART4_USART5_COMBINED_INTERRUPT)

#if defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE)
	NVIC_SetPriority(USART4_5_IRQn, {});
	NVIC_EnableIRQ(USART4_5_IRQn);
#endif	// defined(CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE) || defined(CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE)

#else	// !defined(CONFIG_CHIP_STM32_USARTV2_USART4_USART5_COMBINED_INTERRUPT)

#ifdef CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
	NVIC_SetPriority(USART4_IRQn, {});
	NVIC_EnableIRQ(USART4_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART4_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE
	NVIC_SetPriority(USART5_IRQn, {});
	NVIC_EnableIRQ(USART5_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART5_ENABLE

#endif	// !defined(CONFIG_CHIP_STM32_USARTV2_USART4_USART5_COMBINED_INTERRUPT)

#ifdef CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE
	NVIC_SetPriority(UART4_IRQn, {});
	NVIC_EnableIRQ(UART4_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART4_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE
	NVIC_SetPriority(UART5_IRQn, {});
	NVIC_EnableIRQ(UART5_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART5_ENABLE

#ifdef CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE
	NVIC_SetPriority(USART6_IRQn, {});
	NVIC_EnableIRQ(USART6_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART6_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE
	NVIC_SetPriority(UART7_IRQn, {});
	NVIC_EnableIRQ(UART7_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART7_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE
	NVIC_SetPriority(USART7_IRQn, {});
	NVIC_EnableIRQ(USART7_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART7_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE
	NVIC_SetPriority(UART8_IRQn, {});
	NVIC_EnableIRQ(UART8_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_UART8_ENABLE
#ifdef CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE
	NVIC_SetPriority(USART8_IRQn, {});
	NVIC_EnableIRQ(USART8_IRQn);
#endif	// def CONFIG_CHIP_STM32_USARTV2_USART8_ENABLE

#endif	// defined(CONFIG_CHIP_STM32_USARTV2_USART3_USART6_COMBINED_INTERRUPT)
}

}	// namespace chip

}	// namespace distortos
