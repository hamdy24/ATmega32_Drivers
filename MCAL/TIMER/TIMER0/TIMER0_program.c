/*
 * TIMER_program.c
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of TIMER0
 */

#include "TIMER0_private.h"

/*******************************************************************************************************
 ****************************************** Timer0 Implementations *************************************
 *******************************************************************************************************/

/***************** TCCR0 Watch window ************************
 * FOC0	WGM00 COM01	COM00 WGM01	CS02 CS01 CS00				 *
 *   0	  0	    0 	  0	   0	 1	  0	   0	TCCR0 = 0x13 *
 *************************************************************/

ES_t TIMER0_enuInit(Timer0_Configs_t * Copy_pstrTimer0Configs){
	u8 Local_enuErrorState = ES_NOK;

	TCNT0 = 0;	//Empty
	TCCR0 &= ~(MASK_BIT<<FOC0); //Force output compare match: 0

	/*******************************************/
	/*********** Wave Generation Mode **********/
	/*******************************************/
	switch(Copy_pstrTimer0Configs->WaveGenerationMode){
	case Timer0_OVF_Mode:
		TCCR0 &= ~(MASK_BIT<<WGM00);
		TCCR0 &= ~(MASK_BIT<<WGM01);
		 //Overflow INT Enabled
		TIMSK |=  (MASK_BIT<<TOIE0);
		TIMSK &= ~(MASK_BIT<<OCIE0);
		break;
	case Timer0_CTC_Mode:
		TCCR0 &= ~(MASK_BIT<<WGM00);
		TCCR0 |=  (MASK_BIT<<WGM01);
		//Output Compare Match INT Enabled
		TIMSK &= ~(MASK_BIT<<TOIE0);
		TIMSK |=  (MASK_BIT<<OCIE0);
		break;
	case Timer0_PWM_Fast:
		TCCR0 |=  (MASK_BIT<<WGM00);
		TCCR0 |=  (MASK_BIT<<WGM01);
		break;
	case Timer0_PWM_Phase:
		TCCR0 |=  (MASK_BIT<<WGM00);
		TCCR0 &= ~(MASK_BIT<<WGM01);
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	if(ES_OUT_OF_RANGE != Local_enuErrorState){

		/*******************************************/
		/*********** OUTPUT COMPARE MODE ***********/
		/*******************************************/
		if(Copy_pstrTimer0Configs->OutputCompareMode >= Timer0_OC0_Disabled
				&& Copy_pstrTimer0Configs->OutputCompareMode <= Timer0_OC0_Set){

			TCCR0 |= (Copy_pstrTimer0Configs->OutputCompareMode<<COM00);

			/*******************************************/
			/********** Clock Mode Selection ***********/
			/*******************************************/
			if(Copy_pstrTimer0Configs->ClockSourceSelect >= Timer0_PRES_Disabled
					&& Copy_pstrTimer0Configs->ClockSourceSelect <= Timer0_T0_Rising){

				TCCR0 |= (Copy_pstrTimer0Configs->ClockSourceSelect<<CS00);

				Local_enuErrorState = TIMER0_enuUpdatePrescaler(Copy_pstrTimer0Configs->ClockSourceSelect);
			}
			else{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		else{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}

	return Local_enuErrorState;
}
ES_t TIMER0_enuSetOutputCompareMode(Timer0_OCM_t Copy_enuTimer0_OCM){
	ES_t Local_enuErrorState = ES_NOK;
	/****** OUTPUT COMPARE MODE ******/
	if(Copy_enuTimer0_OCM >= Timer0_OC0_Disabled
			&& Copy_enuTimer0_OCM <= Timer0_OC0_Set){

		TCCR0 &= ~(MASK_FIRST_TWO_BITS<<COM00);
		TCCR0 |= (Copy_enuTimer0_OCM<<COM00);
	}
	if(ES_OUT_OF_RANGE != Local_enuErrorState){
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER0_enuSetWaveGenMode(Timer0_WGM_t Copy_enuTimer0_WGM){
	ES_t Local_enuErrorState = ES_NOK;
	/********* Wave Generation Mode*******/
	switch(Copy_enuTimer0_WGM){
	case Timer0_OVF_Mode:
		TCCR0 &= ~(MASK_BIT<<WGM00);
		TCCR0 &= ~(MASK_BIT<<WGM01);
		break;
	case Timer0_CTC_Mode:
		TCCR0 &= ~(MASK_BIT<<WGM00);
		TCCR0 |=  (MASK_BIT<<WGM01);
		break;
	case Timer0_PWM_Fast:
		TCCR0 |=  (MASK_BIT<<WGM00);
		TCCR0 |=  (MASK_BIT<<WGM01);
		break;
	case Timer0_PWM_Phase:
		TCCR0 |=  (MASK_BIT<<WGM00);
		TCCR0 &= ~(MASK_BIT<<WGM01);
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}
	if(ES_OUT_OF_RANGE != Local_enuErrorState){
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER0_enuUpdatePrescaler(Timer0_Pres_t Copy_enuTimer0_Pres){
	ES_t Local_enuErrorState = ES_NOK;
	switch(Copy_enuTimer0_Pres){
	case Timer0_PRES_Disabled:
		Timer0_u32PrescalerVal = 0;
		break;
	case Timer0_PRES_1:
		Timer0_u32PrescalerVal = 1;
		break;
	case Timer0_PRES_8:
		Timer0_u32PrescalerVal = 8;
		break;
	case Timer0_PRES_64:
		Timer0_u32PrescalerVal = 64;
		break;
	case Timer0_PRES_256:
		Timer0_u32PrescalerVal = 256;
		break;
	case Timer0_PRES_1024:
		Timer0_u32PrescalerVal = 1024;
		break;
	case Timer0_T0_Falling:
		Timer0_u32PrescalerVal = 0xff;
		break;
	case Timer0_T0_Rising:
		Timer0_u32PrescalerVal = 0xff;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}
	if(ES_OUT_OF_RANGE != Local_enuErrorState){
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER0_enuSelect_Clock(Timer0_Pres_t Copy_enuTimer0_Pres){
	ES_t Local_enuErrorState = ES_NOK;
	/****** Clock Mode Selection ********/
	if(Copy_enuTimer0_Pres >= Timer0_PRES_Disabled
			&& Copy_enuTimer0_Pres <= Timer0_T0_Rising){
		TCCR0 &= PRES_MSK;
		TCCR0 |= (Copy_enuTimer0_Pres<<CS00);

		Local_enuErrorState = TIMER0_enuUpdatePrescaler(Copy_enuTimer0_Pres);
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}
ES_t TIMER0_enuDelay_ms_OVF(u32 Copy_u32DesiredTime_ms){
	u8 Local_enuErrorState = ES_NOK;

	u32 Local_u32TotalCounts = (u32)(Copy_u32DesiredTime_ms * (F_CPU /(Timer0_u32PrescalerVal * CALC_LIMIT_TO_MS)) );

	Timer0_u32OVFs_Number = (u32)(Local_u32TotalCounts / FULL_OVF_COUNTS);
	u8 Local_u8FractionCounts = Local_u32TotalCounts % FULL_OVF_COUNTS;

	// this is a polling on the counter that is decremented each time ISR is executed means every ovf occurs
	while (Timer0_u32OVFs_Number > 0);
	while (TCNT0 < Local_u8FractionCounts);

	return Local_enuErrorState;
}
ES_t TIMER0_enuDelay_ms_CTC(u32 Copy_u32DesiredTime_ms){
	u8 Local_enuErrorState = ES_NOK;

/********************************************  OCR0 = desired * freq/pres **************************************************************/
/*
 * We calculate the required OCR value for delay of 1msec each time OCR reached then the input will be the number of counts required directly
 * for prescalers 64..256..1024 the value is divided by 1000 to convert to msec
 * But in prescaler of 1 or 8 the max OCR0 value will generate delay less than 1msec
 * so we divide by 10000 or 100000 to convert calculations from msec to the suitable scale
 */

	if(Timer0_u32PrescalerVal == 8){
		OCR0 = (u8)( (F_CPU /(Timer0_u32PrescalerVal * 1000ul * 10)));
		Timer0_u32OCFs_Number = Copy_u32DesiredTime_ms * 10;
	}
	else if(Timer0_u32PrescalerVal == 1){
		OCR0 = (u8)( (F_CPU /(Timer0_u32PrescalerVal * 1000ul * 100)) );
		Timer0_u32OCFs_Number = Copy_u32DesiredTime_ms * 100;
	}
	else{
		OCR0 = (u8)(F_CPU /(Timer0_u32PrescalerVal * 1000ul));
		Timer0_u32OCFs_Number = Copy_u32DesiredTime_ms;
	}


	 while ( Timer0_u32OCFs_Number > 0);


	return Local_enuErrorState;
}
ES_t TIMER0_enuSetTCNT0_Value(u8 Copy_u8PreloadValue) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_u8PreloadValue >= 0 || Copy_u8PreloadValue <= 255) {
		TCNT0 = Copy_u8PreloadValue;
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}
ES_t TIMER0_enuGetTCNT0_Value(u8* Copy_pu8PreloadValue) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_pu8PreloadValue != NULL) {
		*Copy_pu8PreloadValue = TCNT0;
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_POINTER_TO_VOID;
	return Local_enuErrorState;
}
ES_t TIMER0_enuSetOCR0_Value(u8 Copy_u8CompareValue) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_u8CompareValue >= 0 || Copy_u8CompareValue <= 255) {
		OCR0 = Copy_u8CompareValue;
		Local_enuErrorState = ES_OK;
	}else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}
ES_t TIMER0_enuGetOCR0_Value(u8* Copy_pu8CompareValue) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_pu8CompareValue != NULL) {
		*Copy_pu8CompareValue = OCR0;
		Local_enuErrorState = ES_OK;
	}
	else{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}
	return Local_enuErrorState;
}
ES_t TIMER0_enuOVF_Interrupt(bool Copy_enuInterruptEnable) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_enuInterruptEnable == false) {
		TIMSK &= ~(MASK_BIT<<TOIE0);
		Local_enuErrorState = ES_OK;
	} else if (Copy_enuInterruptEnable == true) {
		TIMSK |=  (MASK_BIT<<TOIE0);
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}
ES_t TIMER0_enuCompareMatch_Interrupt(bool Copy_enuInterruptEnable){
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_enuInterruptEnable == false) {
		TIMSK &= ~(MASK_BIT<<OCIE0);
		Local_enuErrorState = ES_OK;
	} else if (Copy_enuInterruptEnable == true) {
		TIMSK |=  (MASK_BIT<<OCIE0);
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}
ES_t TIMER0_enuSetCallBack(Timer0_ISRs_t Copy_enuSelectedISR, volatile void (*Copy_pfunAppFunction)(void)){
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_pfunAppFunction != NULL) {
		if (Copy_enuSelectedISR == Timer0_OVF_ISR)
			TIMER0_pfunOVF_ISR_fun = Copy_pfunAppFunction;
		else if (Copy_enuSelectedISR == Timer0_COM_ISR)
			TIMER0_pfunCOM_ISR_fun = Copy_pfunAppFunction;
		Local_enuErrorState = ES_OK;
	} else {
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}
	return Local_enuErrorState;
}

 /******************************************************************************************************
 ****************************************** ISR Implementations ****************************************
 *******************************************************************************************************/

/**** Timer0 ISRs ****/
ISR(VECT_TIMER0_OVF) {

	if (Timer0_u32OVFs_Number > 0) {
		Timer0_u32OVFs_Number--;
	}
	if (TIMER0_pfunOVF_ISR_fun != NULL) {
		TIMER0_pfunOVF_ISR_fun();
	}
}
ISR(VECT_TIMER0_COM) {
	if (Timer0_u32OCFs_Number > 0) {
		Timer0_u32OCFs_Number--;
	}
	if (TIMER0_pfunCOM_ISR_fun != NULL) {
		TIMER0_pfunCOM_ISR_fun();
	}
}

