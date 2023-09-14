/*
 * interrupt.h
 *
 *  Created on: Nov 15, 2021
 *      Author: hamdy
 */

#ifndef MCAL_INTERRUPT_H_
#define MCAL_INTERRUPT_H_

#define ISR(vect_num) 			void vect_num (void)__attribute__((signal));\
								void vect_num (void)

#define VECT_INT0				__vector_1
#define VECT_INT1				__vector_2
#define VECT_INT2				__vector_3

#define VECT_TIMER2_COM			__vector_4
#define VECT_TIMER2_OVF			__vector_5

#define VECT_ICU1_CAPT			__vector_6

#define VECT_TIMER1_COMA		__vector_7
#define VECT_TIMER1_COMB		__vector_8
#define VECT_TIMER1_OVF			__vector_9

#define VECT_TIMER0_COM			__vector_10
#define VECT_TIMER0_OVF			__vector_11

#define VECT_SPI_TRANSFER		__vector_12

#define VECT_UART_RECIEVE		__vector_13
#define VECT_UART_DATA_EMPTY	__vector_14
#define VECT_UART_TRANSMIT		__vector_15

#define VECT_ADC				__vector_16

#define VECT_EEPROM_READY		__vector_17

#define VECT_ANALOG_COMP		__vector_18

#define VECT_IIC				__vector_19

#define VECT_STORE_PROG_RDY		__vector_20

#define VECT_RESET				__vector_0



#endif /* MCAL_INTERRUPT_H_ */
