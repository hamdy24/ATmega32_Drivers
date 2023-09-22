/*
 * KEYPAD_prog.c
 *
 *  Created on: Nov 12, 2021
 *      Author: hamdy
 */

#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/common.h"

#include "KEYPAD_config.h"
#include "KEYPAD_private.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/AVR_REG.H"

#include <util/delay.h>

ES_t KEYPAD_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK ;

	DIO_enuSetPinDirection(COL1_PORT , COL1_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(COL2_PORT , COL2_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(COL3_PORT , COL3_PIN , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(COL4_PORT , COL4_PIN , DIO_u8OUTPUT);

	DIO_enuSetPinValue(COL1_PORT , COL1_PIN ,DIO_u8HIGH);
	DIO_enuSetPinValue(COL2_PORT , COL2_PIN ,DIO_u8HIGH);
	DIO_enuSetPinValue(COL3_PORT , COL3_PIN ,DIO_u8HIGH);
	DIO_enuSetPinValue(COL4_PORT , COL4_PIN ,DIO_u8HIGH);

	DIO_enuSetPinDirection(ROW1_PORT , ROW1_PIN , DIO_u8INPUT);
	DIO_enuSetPinDirection(ROW2_PORT , ROW2_PIN , DIO_u8INPUT);
	DIO_enuSetPinDirection(ROW3_PORT , ROW3_PIN , DIO_u8INPUT);
	DIO_enuSetPinDirection(ROW4_PORT , ROW4_PIN , DIO_u8INPUT);


	DIO_enuSetPinValue(ROW1_PORT , ROW1_PIN ,DIO_u8PULL_UP);
	DIO_enuSetPinValue(ROW2_PORT , ROW2_PIN ,DIO_u8PULL_UP);
	DIO_enuSetPinValue(ROW3_PORT , ROW3_PIN ,DIO_u8PULL_UP);
	DIO_enuSetPinValue(ROW4_PORT , ROW4_PIN ,DIO_u8PULL_UP);


	return Local_enuErrorState;
};

ES_t KEYPAD_enuGetCalledKey(u8 * Copy_pu8KeyPressed)
{
	u8 Local_u8ErorrState = ES_NOK;

	u8 Local_Au8ColPorts[COL_NUM] = { COL1_PORT ,COL2_PORT ,COL3_PORT ,COL4_PORT };
	u8 Local_Au8ColPins[COL_NUM]  = { COL1_PIN  ,COL2_PIN  ,COL3_PIN  ,COL4_PIN  };

	u8 Local_Au8RawsPorts[ROW_NUM] = { ROW1_PORT ,ROW2_PORT ,ROW3_PORT ,ROW4_PORT };
	u8 Local_Au8RawsPins[ROW_NUM]  = { ROW1_PIN  ,ROW2_PIN  ,ROW3_PIN  ,ROW4_PIN  };

	u8 Local_u8ColIter;
	u8 Local_u8RowIter;
	u8 Local_u8KeyValue;
 for(Local_u8ColIter = 0 ; Local_u8ColIter < COL_NUM ; Local_u8ColIter++)
 {
	//loop for each column then test all rows
   DIO_enuSetPinValue(Local_Au8ColPorts[Local_u8ColIter] ,Local_Au8ColPins[Local_u8ColIter],DIO_u8LOW);

   for(Local_u8RowIter = 0 ; Local_u8RowIter < ROW_NUM; Local_u8RowIter++ )
   {// loop to test the defection

	DIO_enuGetPinValue(Local_Au8RawsPorts[Local_u8RowIter] ,Local_Au8RawsPins[Local_u8RowIter], &Local_u8KeyValue);
	if(!Local_u8KeyValue)
	{// if there is a defection so.. check again to be sure
	 _delay_ms(10);
	 DIO_enuGetPinValue(Local_Au8RawsPorts[Local_u8RowIter] ,Local_Au8RawsPins[Local_u8RowIter], &Local_u8KeyValue);
	 if(!Local_u8KeyValue)//if same after check
	 {

		 while(!Local_u8KeyValue)// wait till the press ends
		 {
			DIO_enuGetPinValue(Local_Au8RawsPorts[Local_u8RowIter] ,Local_Au8RawsPins[Local_u8RowIter], &Local_u8KeyValue);
		 }
		 u8 LocalAu8KeysValues[ROW_NUM][COL_NUM] = KEYPAD_CONFIG_VALUES;//make key values array
		 *Copy_pu8KeyPressed = LocalAu8KeysValues[Local_u8RowIter][Local_u8ColIter];// return the pressed key to the required variable
		 return ES_OK;// exit the loops and the function
	 }
	}
   }//after looping all rows raise the current column again then switch to other column
   DIO_enuSetPinValue(Local_Au8ColPorts[Local_u8ColIter] ,Local_Au8ColPins[Local_u8ColIter],DIO_u8HIGH);
   *Copy_pu8KeyPressed = KEYPAD_NOT_PRESSED;
 }

	return Local_u8ErorrState;
};


