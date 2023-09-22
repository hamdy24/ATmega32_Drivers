/*
 * LCD_int.h
 *
 *  Created on: Oct 13, 2021
 *      Author: hamdy
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"

ES_t LCD_enuInit(void);

ES_t LCD_enuSendData(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuSendString(const char * Copy_pcString);

ES_t LCD_enuJumpCursorTo( u8 Copy_u8StartX_Position , u8 Copy_u8StartY_Position);

ES_t LCD_enuClearDisplay(void);

ES_t LCD_enuDisplayIntNum(s32 Copy_s32IntNumber);

ES_t LCD_enuDisplayCustomArrCharachter(u8 * Copy_u8pAu8CharHEXA , u8 Copy_u8NumOfPattern , u8 Copy_u8InputDirection);

ES_t LCD_enuDisplayCustomSingleCharachter(u8 * Copy_u8pAu8CharHEXA ,u8 Copy_u8PatternPosition,u8 Copy_u8DisplayPosition );

ES_t LCD_enuDisplayFloatNum(f32 Copy_f32FloatNumber, u8 Copy_u8FractionDigits);

ES_t LCD_enuSavePattern(u8 *Copy_u8pAu8CharHEXA,u8 Copy_u8PatternPosition);

ES_t LCD_enuPrintPattern(u8 Copy_u8PatternNum,u8 Copy_u8PositionX,u8 Copy_u8PositionY);

//ES_t LCD_enuShiftDisplay(u8 Copy_u8StartX_Position,u8 Copy_u8StartY_Position, u8 Copy_u8Num_ofShifts)

/******* interfacing input options *******/
#define LEFT_INPUT		0x04
#define RIGHT_INPUT 	0x06

#endif /* LCD_INT_H_ */
