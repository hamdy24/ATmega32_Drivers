/*
 * PWM_config.c
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */

#include "../../../LIBRARIES/errorstate.h"
#include "../../../LIBRARIES/stdTypes.h"

#include "PWM_config.h"

/*
 * Configurations for PWM of Timer1
 */
PWM1_t PWM_strPWM1_Config = {
		.PWM_EnableState = true,
		.PWM_Type = PWM1_Fast_ICR1,
		.PWM_Mode = OC_InvertingMode,
		.PWM_Channel = PWM1_OC_ChannelA,
};

/*
 * Configurations for PWM of Timer0,2
 */
PWM_Weak_t PWM_strWeakPWM_Config = {
	/** Timer0 PWM Configuration **/
		.PWM_EnableState = true,
		.PWM_WaveType = PWM_Fast,
		.PWM_Mode = OC_Non_InvertingModeWeak,

};




