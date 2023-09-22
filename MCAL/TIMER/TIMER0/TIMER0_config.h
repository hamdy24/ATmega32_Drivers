/*
 * TIMER_config.h
 *
 *  Created on: Nov 19, 2021
 *	Description: File of all needed parameters or configurations would be used to control the TIMER0
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_


#include "../../../LIBRARIES/errorstate.h"
#include "../../../LIBRARIES/common.h"
#include "../../../LIBRARIES/stdTypes.h"

/******************************************************************************
 ************************* Timer0 Configuration Types *************************
 ******************************************************************************/

typedef enum{
	//Clock Source Configurations
	Timer0_PRES_Disabled = 0,
	Timer0_PRES_1,
	Timer0_PRES_8,
	Timer0_PRES_64,
	Timer0_PRES_256,
	Timer0_PRES_1024,
	Timer0_T0_Falling,
	Timer0_T0_Rising,
}Timer0_Pres_t;

typedef enum{
	//Wave Generator Configurations
	Timer0_OVF_Mode = 0,
	Timer0_PWM_Phase,
	Timer0_CTC_Mode,
	Timer0_PWM_Fast,
}Timer0_WGM_t;

typedef enum{
	//Compare Match Output Configurations
	Timer0_OC0_Disabled = 0,
	Timer0_OC0_Toggle,
	Timer0_OC0_Clear,
	Timer0_OC0_Set,

}Timer0_OCM_t;

typedef enum{
	Timer0_OVF_ISR,
	Timer0_COM_ISR,
}Timer0_ISRs_t;
/******************************************************************************
 ************************* Configuration DataTypes ****************************
 ******************************************************************************/

typedef struct{
	Timer0_Pres_t 	ClockSourceSelect  :3;
	Timer0_WGM_t	WaveGenerationMode :2;
	Timer0_OCM_t	OutputCompareMode  :2;
}Timer0_Configs_t;



#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
