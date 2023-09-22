/*
 * GIE_int.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control Global Interrupts of the ATmega32
 */

#ifndef MCAL_GIE_GIE_INT_H_
#define MCAL_GIE_GIE_INT_H_

#include "../../LIBRARIES/errorstate.h"
/*
 * Global Interrupt Control for all Interrupts
 */
ES_t GIE_enuInit(void);

ES_t GIE_enuEnable(void);

ES_t GIE_enuDisable(void);

#endif /* MCAL_GIE_GIE_INT_H_ */
