/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @file   : app.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Tasks includes. */
#include "board.h"

/********************** macros and definitions *******************************/
#define G_APP_CNT_INI	0u

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_sys	= " Bare Metal - Event-Triggered Systems (ETS)\r\n";
const char *p_app	= " App - Timer HW\r\n";

/********************** external data declaration *****************************/
uint32_t g_app_cnt;
volatile uint32_t g_tick_cnt;

/********************** external functions definition ************************/
void app_init(void)
{
	/* Print out: Application Initialized */
	LOGGER_LOG("\r\n");
	LOGGER_LOG("%s is running - Tick [mS] = %d\r\n", GET_NAME(app_init), (int)HAL_GetTick());

	LOGGER_LOG(p_sys);
	LOGGER_LOG(p_app);

	g_app_cnt = G_APP_CNT_INI;

	/* Print out: Application execution counter */
	LOGGER_LOG(" %s = %d\r\n", GET_NAME(g_app_cnt), (int)g_app_cnt);

	/* Start timer */
	HAL_TIM_Base_Start_IT(&htim2);
}

/* STM32 Timer Frequency
 *
 *   Ftimer = Fclk / ((ARR + 1) * (PSC + 1))
 *
 *   Ftimer = 1Hz, Fclk = 64MHz, ARR = 64000-1, PSC = 1000-1
 *
 */
void app_update(void)
{
	/* Update App Counter */
	g_app_cnt++;

	/* Print out: Application Update */
	LOGGER_LOG("\r\n");
	LOGGER_LOG("%s is running - Tick [mS] = %d\r\n", GET_NAME(app_update), (int)HAL_GetTick());

	/* Print out: Application execution counter */
	LOGGER_LOG(" %s = %d\r\n", GET_NAME(g_app_cnt), (int)g_app_cnt);

	for (;;);
}

void HAL_SYSTICK_Callback(void)
{
	g_tick_cnt++;
}

/* Callback in non blocking modes (Interrupt and DMA) */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Check which version of the timer triggered this callback
	if (htim == &htim2 )
	{
		HAL_GPIO_TogglePin(LED_A_PORT, LED_A_PIN);
	}
}

/********************** end of file ******************************************/
