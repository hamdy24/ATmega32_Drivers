/*
 * ICU_Interface.h
 *
 *  Created on:  Sep 19, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Interfaces to be used to run the Input Capture Unit
 */

#ifndef MCAL_ICU_HW_ICU_INTERFACE_H_
#define MCAL_ICU_HW_ICU_INTERFACE_H_

#include "ICU_Config.h"
/* Use This in APP Initialization for ICU*/
extern ICU_Cfg_t ICU_Configs;

ES_t ICU_enuInit(ICU_Cfg_t * Copy_pstrConfigs);
ES_t ICU_enuGetDutyCycle(f32 * Copy_pf32DutyCycle);
ES_t ICU_enuGetFrequency(u16 * Copy_pu16Frequency);
ES_t ICU_enuGetPulseWidth(u16 * Copy_pu16PulseWidth);
ES_t ICU_enuGetPeriod(u16 * Copy_pu16Period);
ES_t ICU_enuSetEventEdge(ICU_Edge_t Copy_enuEdgeSelected);
ES_t ICU_enuSetPrescaler(ICU_Pres_t Copy_enuPrescaler);
ES_t ICU_enuSetNoiseCancler_EN(bool Copy_enuIsEnabled);
ES_t ICU_enuSetICU_EN(bool Copy_enuIsEnabled);
ES_t ICU_enuSetCallBack(volatile void (*Copy_pfunAppFunc)(void));


#endif /* MCAL_ICU_HW_ICU_INTERFACE_H_ */
