/*
 * EXTI_prog.c
 *
 *  Created on: Oct 30, 2021
 *      Author: hamdy
 */

#include "EXTI_priv.h"

ES_t EXTI_enuInit(EXTI_T * Copy_AstrEXTI_CONFIG)
{
ES_t Local_enuErrorState = ES_NOK ;

if(Copy_AstrEXTI_CONFIG[INT0].Interrupt_State == ENABELED) //make sure the interrupt state is enabled
{
			GICR |= (MASK_BIT<<INT0_EN); // for interrupt 0

		switch(Copy_AstrEXTI_CONFIG[INT0].INT_Sense_Level)
		{
		case LOW_LEVEL:

			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT0);	//mask bit 0,1
			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT1);	//mask bit 0,1
			break;
		case ANY_LOGICAL:

			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT0);	//set bit 0

			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT1);	//mask bit 1

			break;
		case FALLING:

			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT0);	//mask bit 0

			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT1);	//set bit 1

			break;
		case RISING:

			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT0);	//set bit 0,1
			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT1);	//set bit 0,1

			break;
		default :
			Local_enuErrorState =ES_OUT_OF_RANGE;

		}
}

	else if(Copy_AstrEXTI_CONFIG[INT0].Interrupt_State == DISABELED)
		{
			GICR &= ~(MASK_BIT<<INT0_EN);
		}

/////////////////////////////////////////////////////////////////////////////////////////
if(Copy_AstrEXTI_CONFIG[INT1].Interrupt_State == ENABELED)
{
			GICR |= (MASK_BIT<<INT1_EN); // for interrupt 1

			switch(Copy_AstrEXTI_CONFIG[INT1].INT_Sense_Level)
					{
					case LOW_LEVEL:

						MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT2);
						MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT3);

						break;
					case ANY_LOGICAL:

						MCUCR |= (MASK_BIT<<INT1_SENSE_BIT2);

						MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT3);
						break;
					case FALLING:

						MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT2);

						MCUCR |= (MASK_BIT<<INT1_SENSE_BIT3);
						break;
					case RISING:

						MCUCR |= (MASK_BIT<<INT1_SENSE_BIT2);
						MCUCR |= (MASK_BIT<<INT1_SENSE_BIT3);

						break;
					default :
						Local_enuErrorState =ES_OUT_OF_RANGE;

					}
}
////////////////////////////////////////////////////////////////////////////////////////////////
		else if(Copy_AstrEXTI_CONFIG[INT0].Interrupt_State == DISABELED)
		{
			GICR &= ~(MASK_BIT<<INT1_EN);
		}
///////////////////////////////////////////////////////////////////////////////////////////////
if(Copy_AstrEXTI_CONFIG[INT2].Interrupt_State == ENABELED)
{
			GICR |= (MASK_BIT<<INT2_EN); // for interrupt 0
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

		switch(Copy_u8SenseLevel)
		{
		case LOW_LEVEL:

			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT0);	//mask bit 0,1
			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT1);	//mask bit 0,1
			Local_enuErrorState = ES_OK;
			break;
		case ANY_LOGICAL:

			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT0);	//set bit 0

			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT1);	//mask bit 1
			Local_enuErrorState = ES_OK;

			break;
		case FALLING:

			MCUCR &= ~(MASK_BIT<<INT0_SENSE_BIT0);	//mask bit 0

			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT1);	//set bit 1
			Local_enuErrorState = ES_OK;

			break;
		case RISING:

			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT0);	//set bit 0,1
			MCUCR |= (MASK_BIT<<INT0_SENSE_BIT1);	//set bit 0,1
			Local_enuErrorState = ES_OK;

			break;

		default :
			Local_enuErrorState =ES_OUT_OF_RANGE;

		}
}

if(Copy_u8InterruptNum == INT1)
{

		switch(Copy_u8SenseLevel)
		{
		case LOW_LEVEL:
		{
			MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT2);	//mask bit 2,3
			MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT3);	//mask bit 2,3
			Local_enuErrorState = ES_OK;
		}
		break;
		case ANY_LOGICAL:
		{
			MCUCR |= (MASK_BIT<<INT1_SENSE_BIT2);	//set bit 2

			MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT3);	//mask bit 3
			Local_enuErrorState = ES_OK;
		}
			break;
		case FALLING:
		{
			MCUCR &= ~(MASK_BIT<<INT1_SENSE_BIT2);	//mask bit 2

			MCUCR |= (MASK_BIT<<INT1_SENSE_BIT3);	//set bit 3
			Local_enuErrorState = ES_OK;
		}
			break;
		case RISING:
		{
			MCUCR |= (MASK_BIT<<INT1_SENSE_BIT2);	//set bit 2,3
			MCUCR |= (MASK_BIT<<INT1_SENSE_BIT3);	//set bit 2,3
			Local_enuErrorState = ES_OK;
		}
			break;

		default :
			Local_enuErrorState =ES_OUT_OF_RANGE;

		}
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

ES_t EXTI_enuSetInterruptEnable(INT_NumSelector_t Copy_u8InterruptNum,bool Copy_enuBoolean)
{
ES_t Local_enuErrorState = ES_NOK ;

if(Copy_enuBoolean == true){
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
else if(Copy_enuBoolean == false){
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

ES_t EXTI_enuCallBack(volatile void  (* pfunAppFunction)(void),INT_NumSelector_t Copy_u8InterruptNum)
{
ES_t Local_enuErrorState = ES_NOK ;

	if(pfunAppFunction != NULL)
	{
		if(Copy_u8InterruptNum <= (INTERRUPT_NUM-1)) //if valid interrupt number
		{
			EXTI_pfunISR_fun[Copy_u8InterruptNum] = pfunAppFunction;

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
