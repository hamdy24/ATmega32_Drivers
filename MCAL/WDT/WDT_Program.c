/*
 * WDT_Program.c
 *
 *  Created on:  Sep 12, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions
 */


#include "WDT_Private.h"

ES_t WDT_enuStartWatching(WDT_Prescaler Copy_enuPrescaler){
	ES_t Local_enuErorrState = ES_NOK;

	if(Copy_enuPrescaler <= WDT_Pres_2048K && Copy_enuPrescaler>=WDT_Pres_16K){
		WDTCR |=  (MASK_BIT<<WDE);
		WDTCR &= WDT_PRES_MASK;
		WDTCR |=  (Copy_enuPrescaler<<WDP0);
		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_OUT_OF_RANGE;
	}


	return Local_enuErorrState;
}

//only error condition to occur is if global interrupt is enabled as an interrupt may occur
ES_t WDT_enuStopWatching(void){
	ES_t Local_enuErorrState = ES_NOK;

	/* Write logical one to WDTOE and WDE */
	WDTCR = (MASK_BIT<<WDTOE) | (MASK_BIT<<WDE);
	/* Turn off WDT */
	WDTCR = WDT_OFF;

	Local_enuErorrState = ES_OK;

	return Local_enuErorrState;
}

