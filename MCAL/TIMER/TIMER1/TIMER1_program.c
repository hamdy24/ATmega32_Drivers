/*
 * TIMER_program.c
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the TIMER1
 */

#include "TIMER1_private.h"


/*******************************************************************************************************
 ****************************************** Timer1 Implementations *************************************
 *******************************************************************************************************/

/********************** TCCR1A Watch window ************************
 * COM1A1 	COM1A0 	COM1B1 	COM1B0 	FOC1A 	FOC1B 	WGM11 	WGM10  *
 *	 0		  0		  0	  	  0		 0		  0		  0		  0	   *
 ********************** TCCR1B Watch window ************************
 * ICNC1 	ICES1 	  – 	WGM13 	WGM12 	CS12 	CS11 	CS10   *
 *   0		  0		  d		  0		  0		  0		  0		  0	   *
 *******************************************************************/

ES_t TIMER1_enuInit(Timer1_Configs_t * Copy_pstrTimer1Configs) {
	ES_t Local_enuErrorState = ES_NOK;

	/*** Interrupts Initialization ***/
	TIMSK &= ~(MASK_BIT<<TICIE1); /** Input Capture Interrupt Disabled **/
	TIMSK &= ~(MASK_BIT<<OCIE1A); /** Output Compare A Match Interrupt Disabled **/
	TIMSK &= ~(MASK_BIT<<OCIE1B); /** Output Compare B Match Interrupt Disabled **/
	TIMSK &= ~(MASK_BIT<<TOIE1);  /** Overflow Interrupt Disabled **/

	/*** Input Capture Initialization ***/
	TCCR1B &= ~(MASK_BIT <<ICNC1); /** Input Capture Noise Canceler Disabled **/
	TCCR1B &= ~(MASK_BIT <<ICES1); /** Input Capture Edge Select Falling **/

	/*** Force Output Compare Disabled ***/
	TCCR1A &= ~(MASK_BIT<<FOC1A);
	TCCR1A &= ~(MASK_BIT<<FOC1B);

	/*******************************************/
	/*** Wave Generation Mode Initialization ***/
	/*******************************************/
	if(Copy_pstrTimer1Configs->WaveGenerationMode >= Timer1_OVF_Mode
			&& Copy_pstrTimer1Configs->WaveGenerationMode<= Timer1_PWM_Fast_OCR1A){

		// AND with 3  (binary 00 11) to get the first two bits only from the value
		TCCR1A |= ( (Copy_pstrTimer1Configs->WaveGenerationMode & MASK_FIRST_TWO_BITS)<<WGM10); // 14=> 11 10 & 00 11 = 10
		// AND with 12 (binary 11 00) to get the second two bits only from the value
		TCCR1B |= ( (Copy_pstrTimer1Configs->WaveGenerationMode & MASK_SECOND_TWO_BITS)<<WGM12); // 14=> 11 10 & 11 00 = 11

		/*******************************************/
		/*********** OUTPUT COMPARE MODE ***********/
		/*******************************************/
		if(Copy_pstrTimer1Configs->OutputCompareMode >= Timer1_OC1A_B_Disabled
			&& Copy_pstrTimer1Configs->OutputCompareMode <= Timer1_OC1A_B_Set){

			TCCR1A |= (Copy_pstrTimer1Configs->OutputCompareMode<<COM1B0);
			TCCR1A |= (Copy_pstrTimer1Configs->OutputCompareMode<<COM1A0);

			/*******************************************/
			/******* Clock Source Initialization *******/
			/*******************************************/
			if(Copy_pstrTimer1Configs->ClockSourceSelect >= Timer1_PRES_Disabled
				&& Copy_pstrTimer1Configs->ClockSourceSelect <= Timer1_T1_Rising){

				TCCR1B |= (Copy_pstrTimer1Configs->ClockSourceSelect<<CS10);
			}
			else{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		else{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	if(ES_OUT_OF_RANGE != Local_enuErrorState ){
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER1_enuSelectWaveGenMode(Timer1_WGM_t Copy_enuTimer1_WGM) {
	ES_t Local_enuErrorState = ES_NOK;


	/*** Wave Generation Mode Initialization ***/
	if(Copy_enuTimer1_WGM >= Timer1_OVF_Mode
			&& Copy_enuTimer1_WGM<= Timer1_PWM_Fast_OCR1A){
		TCCR1A &= ~(MASK_FIRST_TWO_BITS<<WGM10);
		TCCR1B &= ~(MASK_FIRST_TWO_BITS<<WGM12);

		// AND with 3  (binary 00 11) to get the first two bits only from the value
		TCCR1A |= ( (Copy_enuTimer1_WGM & MASK_FIRST_TWO_BITS)<<WGM10); // 14=> 11 10 & 00 11 = 10
		// AND with 12 (binary 11 00) to get the second two bits only from the value
		TCCR1B |= ( (Copy_enuTimer1_WGM & MASK_SECOND_TWO_BITS)<<WGM12); // 14=> 11 10 & 11 00 = 11

		Local_enuErrorState = ES_OK;
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}
ES_t TIMER1_enuSelectOutputCompareMode(Timer1_OCM_t Copy_enuTimer1_OCM) {
	ES_t Local_enuErrorState = ES_NOK;

	/******** OUTPUT COMPARE MODE ********/
	if(Copy_enuTimer1_OCM >= Timer1_OC1A_B_Disabled
		&& Copy_enuTimer1_OCM <= Timer1_OC1A_B_Set){

		TCCR1A &= ~(MASK_FIRST_TWO_BITS<<COM1A0);
		TCCR1A &= ~(MASK_FIRST_TWO_BITS<<COM1B0);

		TCCR1A |= (Copy_enuTimer1_OCM<<COM1A0);
		TCCR1A |= (Copy_enuTimer1_OCM<<COM1B0);

		Local_enuErrorState = ES_OK;
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}
ES_t TIMER1_enuSelectClockSource(Timer1_Pres_t Copy_enuTimer1_Pres) {
	ES_t Local_enuErrorState = ES_NOK;

	/*** Clock Source Initialization ***/
	if(Copy_enuTimer1_Pres >= Timer1_PRES_Disabled
		&& Copy_enuTimer1_Pres <= Timer1_T1_Rising){
		TCCR1B &= PRES_MSK;
		TCCR1B |= (Copy_enuTimer1_Pres<<CS10);

		Local_enuErrorState = ES_OK;
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}
ES_t TIMER1_enuSetTCNT1(u16 Copy_u16TCNT1_Value) {
	ES_t Local_enuErrorState = ES_NOK;
	if(TIMER1_MAX_COUNTS >= Copy_u16TCNT1_Value){
		TCNT1 = Copy_u16TCNT1_Value;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}
ES_t TIMER1_enuSet_OCR1A(u16 Copy_u16OCR1A_Value) {
	ES_t Local_enuErrorState = ES_NOK;
	if(TIMER1_MAX_COUNTS >= Copy_u16OCR1A_Value){
		OCR1A = Copy_u16OCR1A_Value;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}
ES_t TIMER1_enuSet_OCR1B(u16 Copy_u16OCR1B_Value) {
	ES_t Local_enuErrorState = ES_NOK;
	if(TIMER1_MAX_COUNTS >= Copy_u16OCR1B_Value){
		OCR1B = Copy_u16OCR1B_Value;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}
ES_t TIMER1_enuSet_ICR1(u16 Copy_u16ICR1B_Value) {
	ES_t Local_enuErrorState = ES_NOK;
	if(TIMER1_MAX_COUNTS >= Copy_u16ICR1B_Value){
		ICR1 = Copy_u16ICR1B_Value;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t TIMER1_enuGetTCNT1(u16* Copy_pu16TCNT1_Value) {
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_pu16TCNT1_Value){
		*Copy_pu16TCNT1_Value = TCNT1;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}

	return Local_enuErrorState;
}

ES_t TIMER1_enuGet_OCR1A(u16* Copy_pu16OCR1A_Value){
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_pu16OCR1A_Value){
		*Copy_pu16OCR1A_Value = OCR1A;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}

	return Local_enuErrorState;
}

ES_t TIMER1_enuGet_OCR1B(u16* Copy_pu16OCR1B_Value){
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_pu16OCR1B_Value){
		*Copy_pu16OCR1B_Value = OCR1B;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}

	return Local_enuErrorState;
}

ES_t TIMER1_enuGet_ICR1(u16* Copy_pu16ICR1_Value){
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_pu16ICR1_Value){
		*Copy_pu16ICR1_Value = ICR1;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}

	return Local_enuErrorState;
}

ES_t TIMER1_enuEnable_InputCapture_INT(bool Copy_enuInterruptEnable) {
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_enuInterruptEnable == true){
		TIMSK |= (MASK_BIT<<TICIE1); /** Input Capture Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}
	else if(Copy_enuInterruptEnable == false)
	{
		TIMSK &= ~(MASK_BIT<<TICIE1); /** Input Capture Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}


	return Local_enuErrorState;
}
ES_t TIMER1_enuEnable_OVF_INT(bool Copy_enuInterruptEnable) {
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuInterruptEnable == true){
		TIMSK |=  (MASK_BIT<<TOIE1);  /** Overflow Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}
	else if(Copy_enuInterruptEnable == false)
	{
		TIMSK &= ~(MASK_BIT<<TOIE1);  /** Overflow Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}


	return Local_enuErrorState;
}
ES_t TIMER1_enuEnable_OCRA_INT(bool Copy_enuInterruptEnable) {
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuInterruptEnable == true){
		TIMSK |=  (MASK_BIT<<OCIE1A); /** Output Compare A Match Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}
	else if(Copy_enuInterruptEnable == false)
	{
		TIMSK &= ~(MASK_BIT<<OCIE1A); /** Output Compare A Match Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER1_enuEnable_OCRB_INT(bool Copy_enuInterruptEnable) {
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuInterruptEnable == true){
		TIMSK |=  (MASK_BIT<<OCIE1B); /** Output Compare B Match Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}
	else if(Copy_enuInterruptEnable == false)
	{
		TIMSK &= ~(MASK_BIT<<OCIE1B); /** Output Compare B Match Interrupt Disabled **/
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER1_enuSetCallBack(Timer1_ISRs_t Copy_enuTimer1_SelectedISR,volatile void (*Copy_pfunAppCallBack)(void)) {
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_pfunAppCallBack){
		switch(Copy_enuTimer1_SelectedISR){
		case Timer1_OCR1A_ISR:
				TIMER1_pfunComA_ISR_fun = Copy_pfunAppCallBack;
			break;
		case Timer1_OCR1B_ISR:
				TIMER1_pfunComB_ISR_fun = Copy_pfunAppCallBack;
			break;
		case Timer1_OVF_ISR:
				TIMER1_pfunOVF_ISR_fun = Copy_pfunAppCallBack;
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANGE;
			break;

			if (ES_OUT_OF_RANGE != Local_enuErrorState) {
				Local_enuErrorState = ES_OK;
			}
		}

	}
	else{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}



	return Local_enuErrorState;
}

 /******************************************************************************************************
 ****************************************** ISR Implementations ****************************************
 *******************************************************************************************************/

/**** Timer1 ISRs ****/
ISR(VECT_TIMER1_COMA){

	if (TIMER1_pfunComA_ISR_fun != NULL) {
		TIMER1_pfunComA_ISR_fun();
	}
}
ISR(VECT_TIMER1_COMB){

	if (TIMER1_pfunComB_ISR_fun != NULL) {
		TIMER1_pfunComB_ISR_fun();
	}
}
ISR(VECT_TIMER1_OVF){

	if (TIMER1_pfunOVF_ISR_fun != NULL) {
		TIMER1_pfunOVF_ISR_fun();
	}
}

