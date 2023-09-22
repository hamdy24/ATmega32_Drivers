/*
 * EXTI_int.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the EXTI of the ATmega32
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

#include "EXTI_config.h"
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorstate.h"

/**** Use This in EXTI Initialization in main APP ****/
extern EXTI_T EXTI_enuAstrEXTI_CONFIG[INTERRUPT_NUM];


ES_t EXTI_enuInit(EXTI_T * Copy_AstrEXTI_CONFIG);

ES_t EXTI_enuSetSenseLevel(INT_NumSelector_t Copy_u8InterruptNum , INT_SenseLevel_t Copy_u8SenseLevel);

ES_t EXTI_enuSetInterruptEnable(INT_NumSelector_t Copy_u8InterruptNum,bool Copy_enuIsEnabled);

ES_t EXTI_enuCallBack(CallBackFunc_t Copy_pfun_AppFun , INT_NumSelector_t Copy_u8InterruptNum);


#endif /* MCAL_EXTI_EXTI_INT_H_ */
