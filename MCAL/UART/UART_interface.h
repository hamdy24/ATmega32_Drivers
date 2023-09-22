/*
 * UART_interface.h
 *
 *  Created on: Nov 9, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the UART
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include "UART_config.h"

/*************** Use This in UART Initialization in main APP ******************/
extern UART_Config_t UART_Configs;

ES_t UART_enuUART_Init(UART_Config_t * Copy_pstrUART_Configs,u32 Copy_u32BAUD_Rate);
ES_t UART_enuSendChar( u8 Copy_u8CharData);
ES_t UART_enuSendString(u8 * Copy_Au8StringData[]);
ES_t UART_enuRecieveChar(u8 * Copy_u8RxChar);
ES_t UART_enuRecieveString(u8 * Copy_Au8RxString[]);
ES_t UART_enuEnable_UART_RXEN(bool Copy_enuIsEnabled);
ES_t UART_enuEnable_UART_TXEN(bool Copy_enuIsEnabled);
ES_t UART_enuEnable_UART_RX_INT(bool Copy_enuIsEnabled);
ES_t UART_enuCall_Back(CallBackFunc_t Copy_pfun_AppFun);
/*** This function is used to detect if someone tried to use the terminal so we can do action depend on that ***/
ES_t UART_enuCheck_Connection(bool * Copy_enuIsConnected);

/*
 * ES_t UART_enuFlush();
 */

#endif /* MCAL_UART_UART_INTERFACE_H_ */
