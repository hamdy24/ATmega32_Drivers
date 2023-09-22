/*
 * UART_program.c
 *
 *  Created on: Nov 9, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the UART
 */

#include "UART_private.h"

/*				Watch Window	.
 *  UCSRA
 * RXC	 TXC 	UDRE 	FE 		DOR 	PE 		U2X 	MPCM
 *		 R/W									R/W		R/W
 * UCSRB
 * RXCIE TXCIE 	UDRIE 	RXEN 	TXEN 	UCSZ2 	RXB8 	TXB8
 *
 * UCSRC => write whole register
 * URSEL UMSEL 	UPM1 	UPM0 	USBS 	UCSZ1 	UCSZ0 	UCPOL
 */

ES_t UART_enuUART_Init(UART_Config_t * Copy_pstrUART_Configs,u32 Copy_u32BAUD_Rate)
{
	ES_t Local_ErorrState = ES_NOK;

	u8 Local_u8UCSRC_TempValue = 0x00;
	u16 Local_u16UBBR_TempValue=0;
/****	Synchronous Asynchronous Initialization ****/
	if(Copy_pstrUART_Configs->OperationMode == Asynchronous){
		Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UMSEL);

		/****	U2X Double Speed Initialization ****/
		if(Copy_pstrUART_Configs->SpeedMode == DoubledSpeed){
			UCSRA |= (MASK_BIT<<U2X); // => U2X=1
		}
		else{
			UCSRA &= ~(MASK_BIT<<U2X);
		}
	}
	else if(Copy_pstrUART_Configs->OperationMode == Synchronous){
		Local_u8UCSRC_TempValue |= (MASK_BIT<<UMSEL);
	}
	else
		Local_ErorrState = ES_OUT_OF_RANGE;

	if(ES_OUT_OF_RANGE != Local_ErorrState){

		/****	UART RX/TX Enable Initialization ****/
		switch(Copy_pstrUART_Configs->RxTxMode){
		case RxTxDisabled:
			UCSRB &= ~(MASK_BIT<<RXEN);
			UCSRB &= ~(MASK_BIT<<TXEN);
			break;
		case Transmitter:
			UCSRB &= ~(MASK_BIT<<RXEN);
			UCSRB |=  (MASK_BIT<<TXEN);
			break;
		case Receiver:
			UCSRB |=  (MASK_BIT<<RXEN);
			UCSRB &= ~(MASK_BIT<<TXEN);
			break;
		case TransmittReceive:
			UCSRB |=  (MASK_BIT<<RXEN);
			UCSRB |=  (MASK_BIT<<TXEN);
			break;
		default:
			Local_ErorrState = ES_OUT_OF_RANGE;
			break;
		}

		if(ES_OUT_OF_RANGE != Local_ErorrState){

			/****	Frame Data Characters Initialization ****/
			switch(Copy_pstrUART_Configs->FrameChars){
			case FiveBits:
				Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UCSZ0);
				Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UCSZ1);
				UCSRB 					&= ~(MASK_BIT<<UCSZ2);
				break;
			case SixBits:
				Local_u8UCSRC_TempValue |=  (MASK_BIT<<UCSZ0);
				Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UCSZ1);
				UCSRB 					&= ~(MASK_BIT<<UCSZ2);
				break;
			case SevenBits:
				Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UCSZ0);
				Local_u8UCSRC_TempValue |=  (MASK_BIT<<UCSZ1);
				UCSRB 					&= ~(MASK_BIT<<UCSZ2);
				break;
			case EightBits:
				Local_u8UCSRC_TempValue |=  (MASK_BIT<<UCSZ0);
				Local_u8UCSRC_TempValue |=  (MASK_BIT<<UCSZ1);
				UCSRB 					&= ~(MASK_BIT<<UCSZ2);
				break;
			case NineBits:
				Local_u8UCSRC_TempValue |= (MASK_BIT<<UCSZ0);
				Local_u8UCSRC_TempValue |= (MASK_BIT<<UCSZ1);
				UCSRB 					|= (MASK_BIT<<UCSZ2);
				break;
			default:
				Local_ErorrState = ES_OUT_OF_RANGE;
				break;
			}

			if(ES_OUT_OF_RANGE != Local_ErorrState){

				/****	Frame Stop Bits Initialization ****/
				if(Copy_pstrUART_Configs->FrameStopBits == OneBit){
					Local_u8UCSRC_TempValue &= ~(MASK_BIT<<USBS);
				}
				else if(Copy_pstrUART_Configs->FrameStopBits == TwoBits){
					Local_u8UCSRC_TempValue |=  (MASK_BIT<<USBS);
				}
				else
					Local_ErorrState = ES_OUT_OF_RANGE;

				if(ES_OUT_OF_RANGE != Local_ErorrState){

					/****	Frame Parity Bits Initialization ****/
					switch(Copy_pstrUART_Configs->FrameParityMode){
					case ParityDisabled:
						Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UPM0);
						Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UPM1);
						break;
					case Even:
						Local_u8UCSRC_TempValue &= ~(MASK_BIT<<UPM0);
						Local_u8UCSRC_TempValue |=  (MASK_BIT<<UPM1);
						break;
					case Odd:
						Local_u8UCSRC_TempValue |= (MASK_BIT<<UPM0);
						Local_u8UCSRC_TempValue |= (MASK_BIT<<UPM1);
						break;
					default:
						Local_ErorrState = ES_OUT_OF_RANGE;
					}
				}
			}
		}
	}


	if(ES_OUT_OF_RANGE != Local_ErorrState){

		/****	UCSRC Initialization ****/
		Local_u8UCSRC_TempValue |= (MASK_BIT<<URSEL); // Must be one when writing to UCSRC
		UCSRC = Local_u8UCSRC_TempValue;


		/**** BAUD Rate Initialization ****/
		if(Copy_pstrUART_Configs->OperationMode == Asynchronous){
			if(Copy_pstrUART_Configs->SpeedMode == NormalSpeed){
				Local_u16UBBR_TempValue = (F_CPU/(16*Copy_u32BAUD_Rate))-1;

			}
			else if(Copy_pstrUART_Configs->SpeedMode == DoubledSpeed){
				Local_u16UBBR_TempValue =  (F_CPU/(8*Copy_u32BAUD_Rate))-1;
			}
		}
		else if(Copy_pstrUART_Configs->OperationMode == Synchronous){
			Local_u16UBBR_TempValue =  (F_CPU/(2*Copy_u32BAUD_Rate))-1;
		}
		else
			Local_ErorrState = ES_OUT_OF_RANGE;

		if(ES_OUT_OF_RANGE != Local_ErorrState){
			UBRRH = (u8)(Local_u16UBBR_TempValue>>8);
			UBRRL = (u8)(Local_u16UBBR_TempValue);
			Local_ErorrState = ES_OK;
		}
	}


	return Local_ErorrState;
}

ES_t UART_enuSendChar( u8 Copy_u8CharData)
{
	ES_t Local_ErorrState = ES_NOK;
	// check if UDR ready(empty)for write or not using UDRE bit--> if ready..go else wait.

	while(! ((UCSRA >> UDRE) &MASK_BIT)); // (UCSRA >> 5) -> UDRE
	UDR = Copy_u8CharData;

/*
 * previous is polling with (UDRE)
 * next is polling with (TXCIE)
// we will send data to UDR then wait in while until all data is transmitted then we put the TXc flag down again.

	  UDR = Copy_u8CharData;
	  while(!((UCSRA >> TXCIE) & MASK_BIT));
	  UCSRA |= (MASK_BIT>>TXCIE);

*/
	return Local_ErorrState;
}

ES_t UART_enuRecieveChar(u8 * Copy_u8RxChar)
{
	ES_t Local_ErorrState = ES_NOK;

// As long the RXc is 0 so there is no received data at that moment --> receive the new data

	while(((UCSRA >> RXC) & MASK_BIT) == 0);
	*Copy_u8RxChar = UDR;

	return Local_ErorrState;
}

ES_t UART_enuSendString(u8 * Copy_Au8StringData)
{
	ES_t Local_ErorrState = ES_NOK;

	u8 Local_u8Iter = 0;

	while(Copy_Au8StringData[Local_u8Iter] != 0) // check if data not equal  NULL
	{
		while(! ((UCSRA>>UDRE) & MASK_BIT )); // wait until the UDR is empty
		UDR = (Copy_Au8StringData[Local_u8Iter]);
		UART_First_ConnectionFlag=1;
		Local_u8Iter++;
	}

	return Local_ErorrState;
}

ES_t UART_enuRecieveString(u8 * Copy_Au8RxString)
{
	ES_t Local_ErorrState = ES_NOK;

#if NEW_LINE == NO
	u8 Local_u8EndChar , Local_u8TempChar, Local_u8Iter = 0;

	while(((UCSRA >> RXC) & MASK_BIT) == 0); // (UCSRA >> 7)-> RXc
	Local_u8EndChar = UDR;

//to display what is typed

	while(! ((UCSRA>>UDRE) & MASK_BIT ));
	UDR = Local_u8EndChar;

	while(1)
	{

		while(((UCSRA >> RXC) & MASK_BIT) == 0); // (UCSRA >> 7)-> RXc
		Local_u8TempChar = UDR ;

//to display what is typed

		while(! ((UCSRA>>UDRE) & MASK_BIT )); // (UCSRA>>5)-> UDRE
		UDR = Local_u8TempChar;

		if(Local_u8EndChar == Local_u8TempChar )
		{
			(Copy_Au8RxString[Local_u8Iter++]) = 0;
			break;
		}

	(Copy_Au8RxString[Local_u8Iter++]) = Local_u8TempChar;

	}
#elif NEW_LINE == YES
	u8 Local_u8Iter = 0;

	while(1)
	{

		while(((UCSRA >> RXC) & MASK_BIT) == 0); // (UCSRA >> 7)-> RXc
		(Copy_Au8RxString[Local_u8Iter]) = UDR ;

//to display what is typed

		while(! ((UCSRA>>UDRE) & MASK_BIT )); // (UCSRA>>5)-> UDRE
		UDR = (Copy_Au8RxString[Local_u8Iter]);

		if( (Copy_Au8RxString[Local_u8Iter])=='\r' || (Copy_Au8RxString[Local_u8Iter])=='\n')
		{
			(Copy_Au8RxString[Local_u8Iter++]) = 0;
			break;
		}

		Local_u8Iter++;
	}

#endif
	return Local_ErorrState;
}

ES_t  UART_enuEnable_UART_RXEN(bool Copy_enuIsEnabled)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(true == Copy_enuIsEnabled){
		UCSRB |= (MASK_BIT << RXEN);
	}
	else{
		UCSRB &= ~(MASK_BIT << RXEN);
	}

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

ES_t  UART_enuEnable_UART_TXEN(bool Copy_enuIsEnabled)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(true == Copy_enuIsEnabled){
		UCSRB |= (MASK_BIT << TXEN);
	}
	else{
		UCSRB &= ~(MASK_BIT << TXEN);
	}

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

ES_t  UART_enuEnable_UART_RX_INT(bool Copy_enuIsEnabled)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(true == Copy_enuIsEnabled){
		UCSRB |= (MASK_BIT << RXCIE);
	}
	else{
		UCSRB &= ~(MASK_BIT << RXCIE);
	}

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t UART_enuCheck_Connection(bool * Copy_enuIsConnected)
{
	ES_t Local_enuErorrState = ES_NOK;
	if(NULL != Copy_enuIsConnected){
		if(UART_First_ConnectionFlag!=0 )
		{
			*Copy_enuIsConnected = true;
		}
		else{
			*Copy_enuIsConnected = false;
		}
		Local_enuErorrState = ES_OK;
	}
	else
		Local_enuErorrState = ES_POINTER_TO_VOID;
	return Local_enuErorrState;
}

ES_t  UART_enuCall_Back(CallBackFunc_t Copy_pfun_AppFun)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pfun_AppFun != NULL)
	{
		UART_pfunISR_Fun = Copy_pfun_AppFun;
		Local_enuErrorState = ES_OK;
	}
	else
	Local_enuErrorState = ES_POINTER_TO_VOID;

	return Local_enuErrorState;
}

ISR(VECT_UART_RECIEVE)
{

	if(UART_pfunISR_Fun != NULL)
	{
		UART_pfunISR_Fun();
	}

}

