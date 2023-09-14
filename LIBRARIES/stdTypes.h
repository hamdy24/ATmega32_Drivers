/*
 *      stdTypes.h
 *
 *      Created on: Oct 13, 2021
 *      Author: hamdy
 */

#ifndef STDTYPES_H_
#define STDTYPES_H_

/*typedef <dataType> <newName>*/

typedef unsigned char         u8   ;
typedef unsigned short int    u16  ;
typedef unsigned long int     u32  ;

typedef signed char           s8   ;
typedef signed short int      s16  ;
typedef signed long int       s32  ;

typedef float                 f32  ;
typedef double                f64  ;
typedef long double           f80  ;

#define NULL 		     		(void*)0

#ifndef F_CPU
#define F_CPU					16000000
#endif

#ifndef MASK_BIT
#define MASK_BIT			  1
#endif

typedef enum{
	false,
	true,
}bool;




#ifndef F_CPU
#define F_CPU				16000000ul
#endif

#endif /* STDTYPES_H_ */
