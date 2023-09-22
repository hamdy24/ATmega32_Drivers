/*
 * UART_config.c
 *
 *  Created on: Nov 9, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */

#include "UART_config.h"

UART_Config_t UART_Configs = {
	.RxTxMode = TransmittReceive,
	.OperationMode = Asynchronous,
	.SpeedMode = NormalSpeed,
	.FrameChars = EightBits,
	.FrameStopBits = OneBit,
	.FrameParityMode = ParityDisabled,
};
