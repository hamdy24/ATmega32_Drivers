/*
 * UART_private.h
 *
 *  Created on: Nov 9, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the UART
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#include "UART_config.h"

#include "../interrupt.h"
#include "../AVR_REG.H"

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/common.h"

u8 UART_First_ConnectionFlag=0;

static CallBackFunc_t UART_pfunISR_Fun = NULL;


/*
 * UCSRA
 */
#define	RXC				7
#define	TXC				6
#define	UDRE			5
#define	FE				4
#define	DOR				3
#define	PE				2
#define	U2X				1
#define	MPCM			0
/*
 * UCSRB
 */
#define	RXCIE			7
#define	TXCIE			6
#define	UDRIE			5
#define	RXEN			4
#define	TXEN			3
#define	UCSZ2			2
#define	RXB8			1
#define	TXB8			0
/*
 * UCSRC
 */
#define	URSEL			7
#define	UMSEL			6
#define	UPM1			5
#define	UPM0			4
#define	USBS			3
#define	UCSZ1			2
#define	UCSZ0			1
#define	UCPOL			0


#define YES			55
#define NO			77

#ifndef MCAL_AVR_REG_H_
#define MCUCR		*((volatile u8*)0x55)
#define MCUCSR		*((volatile u8*)0x54)

#define UBRRL		*((volatile u8*)0x29)
#define UBRRH		*((volatile u8*)0x40)

#define UCSRC		*((volatile u8*)0x40)
#define UCSRA		*((volatile u8*)0x2B)
#define UCSRB		*((volatile u8*)0x2A)

#define UDR			*((volatile u8*)0x2C)
#endif


#endif /* MCAL_UART_UART_PRIVATE_H_ */
