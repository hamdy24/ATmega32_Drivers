/*
 * TIMER_Config.c
 *
 *  Created on:  Aug 27, 2023
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */

#include "TIMER0_config.h"

/*
 * For other option see TIMER_config.h file and place your required configuration here
 */
Timer0_Configs_t Timer0_Configs = {
		.ClockSourceSelect = Timer0_PRES_256,
		.WaveGenerationMode= Timer0_PWM_Fast,
		.OutputCompareMode = Timer0_OC0_Set
};
