/*
 * EXTI_config.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of all needed parameters or configurations would be used to control the EXTI
 */

#ifndef MCAL_EXTI_EXTI_CONFIG_H_
#define MCAL_EXTI_EXTI_CONFIG_H_

#define INTERRUPT_NUM	3

typedef enum{
	LOW_LEVEL ,
	ANY_LOGICAL,
	FALLING ,
	RISING ,
}INT_SenseLevel_t;
typedef enum{
	ENABELED =0 ,
	DISABELED ,
}INT_State_t;
typedef enum{

	INT0 = 0,
	INT1 ,
	INT2
}INT_NumSelector_t;

typedef struct
{
	INT_State_t Interrupt_State : 1;
	INT_SenseLevel_t INT_Sense_Level : 2;
}EXTI_T;



#endif /* MCAL_EXTI_EXTI_CONFIG_H_ */
