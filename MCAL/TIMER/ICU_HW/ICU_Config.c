/*
 * ICU_Config.c
 *
 *  Created on:  Sep 19, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Configuration Object to use in Initialization Function
 */

#include "ICU_Config.h"

ICU_Cfg_t ICU_Configs={
		.NoiseCanceler_EN = false,
		.EdgeSelect = ICU_RisingEdge,
		.ICU_Prescaler = ICU_PRES_256
};
