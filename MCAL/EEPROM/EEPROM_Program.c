/*
 * EEPROM_Program.c
 *
 *  Created on:  Sep 20, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the Internal EEPROM
 */

#include "EEPROM_Private.h"


ES_t EEPROM_enuWriteByte(u16 Copy_u16DesiredLocation, u8 Copy_u8Data) {
    ES_t Local_ErrorState = ES_NOK;

    /** Check if the input location is valid **/
    if (MAX_ADDRESS_SIZE >= Copy_u16DesiredLocation && MIN_ADDRESS_SIZE <= Copy_u16DesiredLocation) {
        /** Wait for completion of previous write if exists **/
        while (EECR & (1 << EEWE));

        /** Set up address and data registers **/
        EEAR = Copy_u16DesiredLocation;

        /** Start reading existed data **/
        EECR |= (1 << EERE);
        /** Write only if needed **/
        if(EEDR != Copy_u8Data ){

            EEDR = Copy_u8Data;

            /** Disable global interrupts to ensure no interrupt occurs while writing **/
            asm volatile("cli");

            /** Write logical one to EEMWE **/
            EECR |= (1 << EEMWE);

            /** Start EEPROM write by setting EEPE **/
            EECR |= (1 << EEWE);
        }

        Local_ErrorState = ES_OK;
    } else {
        Local_ErrorState = ES_OUT_OF_RANGE;
    }

    return Local_ErrorState;
}

ES_t EEPROM_enuReadByte(u16 Copy_u16DesiredLocation , u8 * Copy_pu8Data){
	ES_t Local_ErorrState = ES_NOK;
	if(NULL != Copy_pu8Data){
		if(MAX_ADDRESS_SIZE >= Copy_u16DesiredLocation && MIN_ADDRESS_SIZE <= Copy_u16DesiredLocation){
			/** Wait for completion of previous write if exists **/
			while(EECR & (MASK_BIT<<EEWE));

			/** Set up address register **/
			EEAR = Copy_u16DesiredLocation;

			/** Start EEPROM read by writing EERE **/
			EECR |= (MASK_BIT<<EERE);

			/** Return data from data register **/
			*Copy_pu8Data = EEDR;
			Local_ErorrState = ES_OK;
		}else{
			Local_ErorrState = ES_OUT_OF_RANGE;
		}
	}else{
		Local_ErorrState = ES_POINTER_TO_VOID;
	}

	return Local_ErorrState;
}
ES_t EEPROM_enuWriteBlock(u16 Copy_u16DesiredLocation , u8 * Copy_pu8ArrayOfData , u8 Copy_u8BlockSize){
	ES_t Local_ErorrState = ES_NOK;

	/** Check if the input location is valid **/
	if(MAX_ADDRESS_SIZE >= Copy_u16DesiredLocation && MIN_ADDRESS_SIZE <= Copy_u16DesiredLocation ){
		if(Copy_u8BlockSize > 0){
			u8 Local_u8DataIterator = 0;
			// loop in range of the block size
			while(Local_u8DataIterator < Copy_u8BlockSize ){
				/** Wait for completion of previous write if exists **/
				/** Also we need to set the EEMWE first before setting EEWE again **/
				while(EECR & (MASK_BIT<<EEWE));
				/** Set up address and data registers **/
				EEAR = Copy_u16DesiredLocation++;
				EEDR = Copy_pu8ArrayOfData[Local_u8DataIterator];
				/** Write logical one to EEMWE **/
				EECR |= (MASK_BIT<<EEMWE);
				/** Start EEPROM write by setting EEWE **/
				EECR |= (MASK_BIT<<EEWE);
			}
			Local_ErorrState = ES_OK;
		}else{
			Local_ErorrState = ES_NOK;
		}
	}else{
		Local_ErorrState = ES_OUT_OF_RANGE;
	}

	return Local_ErorrState;
}
ES_t EEPROM_enuReadBlock(u16 Copy_u16DesiredLocation , u8 * Copy_pu8ArrayOfDataReturned , u8 Copy_u8ReadingSize){
	ES_t Local_ErorrState = ES_NOK;

	if(NULL != Copy_pu8ArrayOfDataReturned){
		if(MAX_ADDRESS_SIZE >= Copy_u16DesiredLocation && MIN_ADDRESS_SIZE <= Copy_u16DesiredLocation){
			/** Check if the block intended to be read will exceed the EEPROM boundaries **/
			if(MAX_ADDRESS_SIZE < (Copy_u16DesiredLocation + Copy_u8ReadingSize)){
				return ES_OUT_OF_RANGE;
			}
			u8 Local_u8DataIterator = 0;
			// loop in range of the block size
			while(Local_u8DataIterator < Copy_u8ReadingSize ){
				/** Wait for completion of previous write if exists **/
				while(EECR & (MASK_BIT<<EEWE));
				/** Set up address register **/
				EEAR = Copy_u16DesiredLocation++;
				/** Start EEPROM read by writing EERE **/
				EECR |= (MASK_BIT<<EERE);
				/** Return data from data register into the array **/
				Copy_pu8ArrayOfDataReturned[Local_u8DataIterator++] = EEDR;
			}
		}else{
			Local_ErorrState = ES_OUT_OF_RANGE;
		}
	}else{
		Local_ErorrState = ES_POINTER_TO_VOID;
	}
	return Local_ErorrState;
}
ES_t EEPROM_enuSetInterrupt_EN(bool Copy_enuIsEnabled){
	ES_t Local_ErorrState = ES_NOK;
	if(true == Copy_enuIsEnabled){
		EECR |=  (MASK_BIT<<EERIE);
	}else if(false == Copy_enuIsEnabled){
		EECR &= ~(MASK_BIT<<EERIE);
	}
	return Local_ErorrState;
}
ES_t EEPROM_enuSetAppCallBack(CallBackFunc_t Copy_pfunAppFunc){
	ES_t Local_ErorrState = ES_NOK;
	if(NULL != Copy_pfunAppFunc){
		EEPROM_pfunISR_FUNC = Copy_pfunAppFunc;
		Local_ErorrState = ES_OK;
	}
	return Local_ErorrState;
}

ISR(VECT_EEPROM_READY){

	if(NULL != EEPROM_pfunISR_FUNC){
		EEPROM_pfunISR_FUNC();
	}
}

