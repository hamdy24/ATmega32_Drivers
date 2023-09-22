/*
 * TIMER_Config.c
 *
 *  Created on:  Aug 27, 2023
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */

#include "TIMER2_config.h"

/*
 * For other option see TIMER_config.h file and place your required configuration here
 */

Timer2_Configs_t Timer2_Configs = {
		.ClockSourceSelect = Timer2_PRES_128,
		.WaveGenerationMode= Timer2_CTC_Mode,
		.OutputCompareMode = Timer2_OC2_Toggle
};
