/*
 * MUART_Interface.h
 *
 *  Created on: Feb 26, 2022
 *      Author: Dell
 */

#ifndef MCAL_MUART_MUART_INTERFACE_H_
#define MCAL_MUART_MUART_INTERFACE_H_

void MUART_VidInit(void);
void MUART_VidSendChar(uint8 copy_uint8Char);
uint8 MUART_uint8ReciverChar(void);
void MUART_vidSendString(uint8 *copy_uint8String);
void MUART_VidReciveString(uint8 *copy_uint8string);

#endif /* MCAL_MUART_MUART_INTERFACE_H_ */
