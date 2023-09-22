/*
 * UART_config.h
 *
 *  Created on: Nov 9, 2021
 *	Description: File of all needed parameters or configurations would be used to control the UART
 */
#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_
/***************************************************************************
 ***** Change This Macro According to if the other device can **************
 ************* handle a carriage/new line chars or not ******************
 ***************************************************************************/
#define NEW_LINE	NO	// YES or NO


/***************	Configurations Helper	***************************/

typedef enum{
	RxTxDisabled,
	Transmitter,
	Receiver,
	TransmittReceive
}UART_Role_t;

typedef enum{
	Synchronous,
	Asynchronous
}UART_Mode_t;

typedef enum{
	NormalSpeed, /** For normal speed or for Synchronous Mode**/
	DoubledSpeed /** Has Effect For Asynchronous Mode */
}TX_SpeedMode_t;

typedef enum{
	FiveBits,
	SixBits,
	SevenBits,
	EightBits,
	NineBits = 7,
}CharSize_t;

typedef enum{
	OneBit,
	TwoBits
}StopBits_t;

typedef enum{
	ParityDisabled,
	Even = 2,
	Odd,
}Parity_t;



typedef struct{

	UART_Role_t RxTxMode 		: 2;
	UART_Mode_t OperationMode 	: 1;
	TX_SpeedMode_t SpeedMode	: 1;
	CharSize_t FrameChars		: 3;
	StopBits_t FrameStopBits	: 1;
	Parity_t FrameParityMode	: 2;

}UART_Config_t;



#endif /* MCAL_UART_UART_CONFIG_H_ */
