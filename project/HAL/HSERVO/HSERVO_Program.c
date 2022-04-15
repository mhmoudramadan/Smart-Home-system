/*
 * HSERVO_Program.c
 *
 *  Created on: Mar 21, 2022
 *      Author: Dell
 */
#include"../../LIB/LSTD_TYPES.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"
#include"../../MCAL/MTIMER1/MTIMER1_Config.h"
#include"../../MCAL/MTIMER1/MTIMER1_Interface.h"
#include "HSERVO_Interface.h"


void HSERVO_VidInit(void)
{
	/*three is 3 ways to control SERVO motor
	 * 1-SW delay
	 * 2-Timer_interrupt
	 * 3-Timer_PWM MODE*/
	/*we will initialize the third way */
	/*Timer1 Fast PWM Mode Top-->OCR1A or ICR --> to set Frequency of SERVO 50hz
	 * Disconnected OC1A
	 * Set OC1B To use OCR1B*/
	/*to get 50hz --> PWM freq=(sys freq/(Prescaler*(1+Top))
	 * to get 50 set preScaler 8 and top OCR1A--> 40000*/
	MTIMER1_VidSetCTCRegister_CHA(40000);
	/*to get angle zero t=1.5ms*/
	MTIMER1_VidSetCTCRegister_CHB(3000);
	/*initialize timer*/
	MTIMER1_VidInit();
}
void HSERVO_VidSetAngle(uint8 copy_uint8Angle)
{
	uint16 Loc_uint16Result;
	Loc_uint16Result=(((uint32)copy_uint8Angle*1000)/180)+3000;
	MTIMER1_VidSetCTCRegister_CHB(Loc_uint16Result);
}
