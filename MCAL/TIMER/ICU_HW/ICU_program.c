/*
 * ICU_program.c
 *
 *  Created on:  Sep 19, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the Definitions of all interfaces
 */

#include "ICU_Private.h"


ES_t ICU_enuInit(ICU_Cfg_t * Copy_pstrConfigs){
	ES_t Local_enuErorrState = ES_NOK;

	    // Set Timer1 to Normal mode
	    TCCR1A = 0;
	    TCCR1B = 0;
	    if(Copy_pstrConfigs->NoiseCanceler_EN == true){
		    TCCR1B |=  (MASK_BIT << ICNC1);
	    }
	    else if(Copy_pstrConfigs->NoiseCanceler_EN == false){
		    TCCR1B &= ~(MASK_BIT << ICNC1);
	    }
	    else
	    	Local_enuErorrState = ES_OUT_OF_RANGE;

	    if(Copy_pstrConfigs->EdgeSelect == ICU_RisingEdge){
		    TCCR1B |=  (MASK_BIT << ICES1);
	    }
	    else if(Copy_pstrConfigs->EdgeSelect == ICU_FallingEdge){
		    TCCR1B &= ~(MASK_BIT << ICES1);
	    }
	    else
	    	Local_enuErorrState = ES_OUT_OF_RANGE;


	    if(Copy_pstrConfigs->ICU_Prescaler <= ICU_T1_Rising
	    		&& Copy_pstrConfigs->ICU_Prescaler >= ICU_PRES_Disabled){
		    TCCR1B |=  (Copy_pstrConfigs->ICU_Prescaler << CS10);
		    ICU_Pres = ICU_Prescalers[Copy_pstrConfigs->ICU_Prescaler];
	    }
	    else
	    	Local_enuErorrState = ES_OUT_OF_RANGE;


	    if(ES_OUT_OF_RANGE != Local_enuErorrState){
		    // Enable input capture interrupt for Timer1
		    TIMSK |= (MASK_BIT << TICIE1);
		    Local_enuErorrState = ES_OK;
	    }

	return Local_enuErorrState;
}

ES_t ICU_enuGetDutyCycle(f32 * Copy_pf32DutyCycle){
	ES_t Local_enuErorrState = ES_NOK;
	if(NULL != Copy_pf32DutyCycle){
//		f32 Local_u16DutyTicks = ((f32)(ICU_u16Time3 - ICU_u16Time2)/(ICU_u16Time2 - ICU_u16Time1));
		ICU_HighTime = ((f32)(ICU_u16Time3 - ICU_u16Time2)*ICU_Pres*1000)/F_CPU;
		ICU_Period   = ((f32)(ICU_u16Time2 - ICU_u16Time1)*ICU_Pres*1000)/F_CPU;
		ICU_DutyCycle = ((f32)(ICU_HighTime*100) /(ICU_Period));
		*Copy_pf32DutyCycle = ICU_DutyCycle;
		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_POINTER_TO_VOID;
	}
	return Local_enuErorrState;
}

ES_t ICU_enuGetFrequency(u16 * Copy_pu16Frequency){
	ES_t Local_enuErorrState = ES_NOK;
	if(NULL != Copy_pu16Frequency){
		while(ICU_State<2); // poll till the two required values are ready
		u16 Local_u16PeriodTicks = (u16)(ICU_u16Time2 - ICU_u16Time1);
		ICU_Frequency = (u16)(F_CPU/((f32)Local_u16PeriodTicks * ICU_Pres));
		*Copy_pu16Frequency =ICU_Frequency;
		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_POINTER_TO_VOID;
	}
	return Local_enuErorrState;
}

ES_t ICU_enuGetPulseWidth(u16 * Copy_pu16PulseWidth){
	ES_t Local_enuErorrState = ES_NOK;
	if(NULL != Copy_pu16PulseWidth){
		ICU_HighTime = ((f32)(ICU_u16Time3 - ICU_u16Time2)*ICU_Pres*1000)/F_CPU;
		*Copy_pu16PulseWidth = ICU_HighTime;
		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_POINTER_TO_VOID;
	}
	return Local_enuErorrState;
}

ES_t ICU_enuGetPeriod(u16 * Copy_pu16Period){
	ES_t Local_enuErorrState = ES_NOK;
	if(NULL != Copy_pu16Period){
		ICU_Period   = ((f32)(ICU_u16Time2 - ICU_u16Time1)*ICU_Pres*1000)/F_CPU;
		*Copy_pu16Period = ICU_Period;
		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_POINTER_TO_VOID;
	}
	return Local_enuErorrState;
}

ES_t ICU_enuSetEventEdge(ICU_Edge_t Copy_enuEdgeSelected){
	ES_t Local_enuErorrState = ES_NOK;

    if(Copy_enuEdgeSelected == ICU_RisingEdge){
	    TCCR1B |=  (MASK_BIT << ICES1);
	    Local_enuErorrState = ES_OK;
    }
    else if(Copy_enuEdgeSelected == ICU_FallingEdge){
	    TCCR1B &= ~(MASK_BIT << ICES1);
	    Local_enuErorrState = ES_OK;
    }
    else
    	Local_enuErorrState = ES_OUT_OF_RANGE;

	return Local_enuErorrState;
}

ES_t ICU_enuSetPrescaler(ICU_Pres_t Copy_enuPrescaler){
	ES_t Local_enuErorrState = ES_NOK;

    if(Copy_enuPrescaler >= ICU_T1_Rising
    		&& Copy_enuPrescaler <= ICU_PRES_Disabled){

    	TCCR1B &= ICU_PRES_MASKING;
	    TCCR1B |=  (Copy_enuPrescaler << CS10);
	    ICU_Pres = ICU_Prescalers[Copy_enuPrescaler];


    }
    else
    	Local_enuErorrState = ES_OUT_OF_RANGE;

	return Local_enuErorrState;
}

ES_t ICU_enuSetNoiseCancler_EN(bool Copy_enuIsEnabled){
	ES_t Local_enuErorrState = ES_NOK;

	if(Copy_enuIsEnabled == true){
	    TCCR1B |=  (MASK_BIT << ICNC1);
    }
    else if(Copy_enuIsEnabled == false){
	    TCCR1B &= ~(MASK_BIT << ICNC1);
    }
    else
    	Local_enuErorrState = ES_OUT_OF_RANGE;

	return Local_enuErorrState;
}

ES_t ICU_enuSetICU_EN(bool Copy_enuIsEnabled){
	ES_t Local_enuErorrState = ES_NOK;
	if(Copy_enuIsEnabled == true){
	    TIMSK |= (MASK_BIT << TICIE1);
	    Local_enuErorrState = ES_OK;
	}
	else if(Copy_enuIsEnabled == false){
	    TIMSK &= ~(MASK_BIT << TICIE1);
	    Local_enuErorrState = ES_OK;
	}else
		Local_enuErorrState = ES_OUT_OF_RANGE;
	return Local_enuErorrState;
}

ES_t ICU_enuSetCallBack(volatile void (*Copy_pfunAppFunc)(void)){
	ES_t Local_enuErorrState = ES_NOK;
	if(NULL != Copy_pfunAppFunc  ){
		ICU_pfunAppCallBack = Copy_pfunAppFunc;
	    Local_enuErorrState = ES_OK;
	}
	else
		Local_enuErorrState = ES_POINTER_TO_VOID;
	return Local_enuErorrState;
}

ISR(VECT_ICU1_CAPT){

	ICU_CapturedValue = ICR1;
	if(NULL != ICU_pfunAppCallBack){
		ICU_pfunAppCallBack();
	}
	else if(ICU_CapturedValue > 0){
		switch(ICU_State){
		case 0:
			ICU_u16Time1 = ICU_CapturedValue;
			ICU_State = 1;
			break;
		case 1:
			ICU_u16Time2 = ICU_CapturedValue;
		    TCCR1B &= ~(MASK_BIT << ICES1);
			ICU_State = 2;
			break;
		case 2:
			ICU_u16Time3 = ICU_CapturedValue;
			ICU_State = 3;
			break;
		}

	}
}
