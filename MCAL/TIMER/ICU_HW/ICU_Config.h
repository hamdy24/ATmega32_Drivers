/*
 * ICU_Config.h
 *
 *  Created on:  Sep 19, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Helpers to be used to run the Input Capture Unit
 */

#ifndef MCAL_ICU_HW_ICU_CONFIG_H_
#define MCAL_ICU_HW_ICU_CONFIG_H_

#include "../../../LIBRARIES/stdTypes.h"

typedef enum{
	ICU_FallingEdge,
	ICU_RisingEdge
}ICU_Edge_t;

typedef enum{
	//Clock Source Configurations
	ICU_PRES_Disabled = 0,
	ICU_PRES_1,
	ICU_PRES_8,
	ICU_PRES_64,
	ICU_PRES_256,
	ICU_PRES_1024,
	ICU_T1_Falling,
	ICU_T1_Rising,
}ICU_Pres_t;


typedef struct {
	bool NoiseCanceler_EN:1;
	ICU_Edge_t EdgeSelect:1;
	ICU_Pres_t ICU_Prescaler:3;
}ICU_Cfg_t;

#endif /* MCAL_ICU_HW_ICU_CONFIG_H_ */
