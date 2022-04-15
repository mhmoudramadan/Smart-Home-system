/*
 * MTIMER1_Interface.h
 *
 *  Created on: Feb 15, 2022
 *      Author: Dell
 */

#ifndef MCAL_MTIMER1_MTIMER1_INTERFACE_H_
#define MCAL_MTIMER1_MTIMER1_INTERFACE_H_


void MTIMER1_VidInit(void);

void MTIMER1_VidSetCTCRegister_CHB(uint16 copy_uint16CTCValue);
void MTIMER1_VidSetCTCRegister_CHA(uint16 copy_uint16CTCValue);
void MTIMER1_VidSetCTCRegister_ICR1(uint16 copy_uint16CTCValue);
void MTIMER1_VidTimer1_OverFlow_SetCallBack(void (*PtrToFun)(void));
void MTIMER1_VidTimer1_CTC_SetCallBack(void (*PtrToFun)(void));
uint32 MTIMER1_uint32Read_ICR1(void);

#endif /* MCAL_MTIMER1_MTIMER1_INTERFACE_H_ */
