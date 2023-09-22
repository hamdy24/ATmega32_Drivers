/*
 * EXTI_prog.c
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of EXTI
 */

#include "EXTI_priv.h"

ES_t EXTI_enuInit(EXTI_T * Copy_AstrEXTI_CONFIG)
{
ES_t Local_enuErrorState = ES_NOK ;

	if(Copy_AstrEXTI_CONFIG[INT0].Interrupt_State == ENABELED) //make sure the interrupt state is enabled
	{
		MCUCR &= TWO_BIT_MSK(INT0_SENSE_BIT0); // mask the two level control bits
		MCUCR |=  (Copy_AstrEXTI_CONFIG[INT0].INT_Sense_Level<<INT0_SENSE_BIT0);

		GICR |= (MASK_BIT<<INT0_EN); // for interrupt 0

	}
	else if(Copy_AstrEXTI_CONFIG[INT0].Interrupt_State == DISABELED)
	{
		GICR &= ~(MASK_BIT<<INT0_EN);
	}

/////////////////////////////////////////////////////////////////////////////////////////
	if(Copy_AstrEXTI_CONFIG[INT1].Interrupt_State == ENABELED)
	{
		MCUCR &= TWO_BIT_MSK(INT1_SENSE_BIT2);
		MCUCR |=  (Copy_AstrEXTI_CONFIG[INT1].INT_Sense_Level<<INT1_SENSE_BIT2);

		GICR |= (MASK_BIT<<INT1_EN); // for interrupt 1
	}
////////////////////////////////////////////////////////////////////////////////////////////////
		else if(Copy_AstrEXTI_CONFIG[INT0].Interrupt_State == DISABELED)
		{
			GICR &= ~(MASK_BIT<<INT1_EN);
		}
///////////////////////////////////////////////////////////////////////////////////////////////
if(Copy_AstrEXTI_CONFIG[INT2].Interrupt_State == ENABELED)
{
			switch(Copy_AstrEXTI_CONFIG[INT2].INT_Sense_Level)
				{
					case FALLING:

						MCUCSR &= ~(MASK_BIT<<INT2_SENSE_BIT6);
						break;
					case RISING:

						MCUCSR |= (MASK_BIT<<INT2_SENSE_BIT6);
						break;
					default :
						Local_enuErrorState =ES_OUT_OF_RANGE;

				}
			GICR |= (MASK_BIT<<INT2_EN); // for interrupt 0
}
/////////////////////////////////////////////////////////////////////////////////////
		else if(Copy_AstrEXTI_CONFIG[INT2].Interrupt_State == DISABELED)
		{
			GICR &= ~(MASK_BIT<<INT2_EN);
		}

return Local_enuErrorState;
}

ES_t EXTI_enuSetSenseLevel(INT_NumSelector_t Copy_u8InterruptNum , INT_SenseLevel_t Copy_u8SenseLevel)
{
ES_t Local_enuErrorState = ES_NOK ;

if(Copy_u8InterruptNum == INT0)
{

	MCUCR &= TWO_BIT_MSK(INT0_SENSE_BIT0); // mask the two level control bits
	MCUCR |=  (Copy_u8SenseLevel<<INT0_SENSE_BIT0);

	GICR |= (MASK_BIT<<INT0_EN); // for interrupt 0

}

if(Copy_u8InterruptNum == INT1)
{

		MCUCR &= TWO_BIT_MSK(INT1_SENSE_BIT2);
		MCUCR |=  (Copy_u8SenseLevel<<INT1_SENSE_BIT2);

		GICR |= (MASK_BIT<<INT1_EN); // for interrupt 1
}


if(Copy_u8InterruptNum == INT2)
{

		switch(Copy_u8SenseLevel)
		{
		case FALLING:
		{
			MCUCSR &= ~(MASK_BIT<<INT2_SENSE_BIT6);	//mask bit 6
			Local_enuErrorState = ES_OK;
		}
			break;
		case RISING:
		{
			MCUCSR |= (MASK_BIT<<INT2_SENSE_BIT6);	//set bit 6
			Local_enuErrorState = ES_OK;
		}
			break;

		default :
			Local_enuErrorState =ES_OUT_OF_RANGE;

		}
}

return Local_enuErrorState;
}

ES_t EXTI_enuSetInterruptEnable(INT_NumSelector_t Copy_u8InterruptNum,bool Copy_enuIsEnabled)
{
ES_t Local_enuErrorState = ES_NOK ;

if(true == Copy_enuIsEnabled){
	switch(Copy_u8InterruptNum)
		{
		case INT0:

			GICR |= (MASK_BIT<<INT0_EN);
			Local_enuErrorState = ES_OK;
			break;
		case INT1:

			GICR |= (MASK_BIT<<INT1_EN);
			Local_enuErrorState = ES_OK;
			break;
		case INT2:

			GICR |= (MASK_BIT<<INT2_EN);
			Local_enuErrorState = ES_OK;
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
}
else if(false == Copy_enuIsEnabled){
	switch(Copy_u8InterruptNum)
	{
	case INT0:

		GICR &= ~(MASK_BIT<<INT0_EN);
		Local_enuErrorState = ES_OK;
		break;
	case INT1:

		GICR &= ~(MASK_BIT<<INT1_EN);
		Local_enuErrorState = ES_OK;
		break;
	case INT2:

		GICR &= ~(MASK_BIT<<INT2_EN);
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
}
else{
	Local_enuErrorState = ES_OUT_OF_RANGE;
}

return Local_enuErrorState;
}

ES_t EXTI_enuCallBack(CallBackFunc_t Copy_pfun_AppFun,INT_NumSelector_t Copy_u8InterruptNum)
{
ES_t Local_enuErrorState = ES_NOK ;

	if(Copy_pfun_AppFun != NULL)
	{
		if(Copy_u8InterruptNum <= (INTERRUPT_NUM-1)) //if valid interrupt number
		{
			EXTI_pfunISR_fun[Copy_u8InterruptNum] = Copy_pfun_AppFun;

			Local_enuErrorState = ES_OK;
		}
	}
	else
	{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}

	return Local_enuErrorState;
}

ISR(VECT_INT0)
{
	if(EXTI_pfunISR_fun[INT0] != NULL)
	{
		EXTI_pfunISR_fun[INT0] ();
	}
}
ISR(VECT_INT1)
{
	if(EXTI_pfunISR_fun[INT1] != NULL)
	{
		EXTI_pfunISR_fun[INT1] ();
	}
}
ISR(VECT_INT2)
{
	if(EXTI_pfunISR_fun[INT2] != NULL)
	{
		EXTI_pfunISR_fun[INT2] ();
	}
}
