/*
 * ADC_Config.c
 *
 *  Created on: Nov 15, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */


#include "ADC_config.h"



ADC_Cfg_t ADC_Configs = {
	.INT_Src = ADC_FREE_RUNNIG,
	.ChannelNum = ADC_CHANNEL_NUM_1,
	.PRES = ADC_PRES_128,
	.VREF = AREF_REF,
	.ADJ_Direction = ADC_LEFT_ADJ,
};
