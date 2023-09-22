/*
 * TIMER_Config.c
 *
 *  Created on:  Aug 27, 2023
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */

#include "TIMER1_config.h"

/*
 * For other option see TIMER_config.h file and place your required configuration here
 */

Timer1_Configs_t Timer1_Configs = {
		.ClockSourceSelect = Timer1_PRES_1024,
		.WaveGenerationMode= Timer1_CTC_ICR1_TopMode,
		.OutputCompareMode = Timer1_OC1A_B_Toggle
};
