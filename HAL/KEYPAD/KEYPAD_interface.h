/*
 * KEYPAD_interface.h
 *
 *  Created on: Nov 12, 2021
 *      Author: hamdy
 */

#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorstate.h"

ES_t KEYPAD_enuInit(void);

ES_t KEYPAD_enuGetCalledKey(u8 * Copy_pu8KeyValue);


#endif /* HAL_KEYPAD_KEYPAD_INTERFACE_H_ */
