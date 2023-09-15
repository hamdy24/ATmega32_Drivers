/*
 * GIE_prog.c
 *
 *  Created on: Oct 30, 2021
 *      Author: hamdy
 */

#include "GIE_priv.h"

ES_t GIE_enuInit(void)
{
	ES_t Local_ErorrState = ES_NOK ;

	SREG &= ~(MASK_BIT<<GIE_BIT_EN);		// GIE BIT FROM SREG REGEISTER

	Local_ErorrState = ES_OK;

	return Local_ErorrState;
}

ES_t GIE_enuEnable(void)
{
	ES_t Local_ErorrState = ES_NOK ;

	SREG |= (MASK_BIT<<GIE_BIT_EN);

	Local_ErorrState = ES_OK;
	return Local_ErorrState;
}

ES_t GIE_enuDisable(void)
{
	ES_t Local_ErorrState = ES_NOK ;

	SREG &= ~(MASK_BIT<<GIE_BIT_EN);

	Local_ErorrState = ES_OK;
	return Local_ErorrState;
}

