/*
 * WDT_Config.h
 *
 *  Created on:  Sep 12, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: File of all needed parameters or configurations would be used to control the Watch Dog Timer
 */

#ifndef MCAL_WDT_WDT_CONFIG_H_
#define MCAL_WDT_WDT_CONFIG_H_

#include "../../LIBRARIES/errorstate.h"

typedef enum{
	 WDT_Pres_16K,
	 WDT_Pres_32K,
	 WDT_Pres_64K,
	 WDT_Pres_128K,
	 WDT_Pres_256K,
	 WDT_Pres_512K,
	 WDT_Pres_1024K,
	 WDT_Pres_2048K
}WDT_Prescaler;

/*
|  	Time-out at  	 |  VCC=5.0V  |  VCC=3.0V  |

|   WDT_Pres_16K,    |  16.3 ms   |  17.1 ms   |
|   WDT_Pres_32K,    |  32.5 ms   |  34.3 ms   |
|   WDT_Pres_64K,    |  65   ms   |  68.5 ms   |
|   WDT_Pres_128K,   |  0.13 s    |  0.14 s    |
|   WDT_Pres_256K,   |  0.26 s    |  0.27 s    |
|   WDT_Pres_512K,   |  0.52 s    |  0.55 s    |
|   WDT_Pres_1024K,  |  1.0  s    |  1.1  s    |
|   WDT_Pres_2048K   |  2.1  s    |  2.2  s    |
*/


#endif /* MCAL_WDT_WDT_CONFIG_H_ */
