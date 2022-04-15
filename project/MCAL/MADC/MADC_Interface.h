/*
 * MADC_Interface.h
 *
 *  Created on: Feb 5, 2022
 *      Author: Dell
 */

#ifndef MCAL_MADC_MADC_INTERFACE_H_
#define  MCAL_MADC_MADC_INTERFACE_H_

/*Anolog channel*/

 typedef enum
 {
	  MADC0,
	  MADC1,
	  MADC2,
	  MADC3,
	  MADC4,
	  MADC5,
	  MADC6,
	  MADC7
 }Analog_Channel;


void MADC_VidSingleConversion_Init(void);

void MADC_VidADCStartSingleConversion(uint8 copy_uint8Channel);
uint16 MADC_uint16Read(void);
void (*MADC_CALLBACK)(void);
void MADC_SetCallBack(void(*PtrToFun)(void));

#endif /* MCAL_MADC_MADC_INTERFACE_H_ */
