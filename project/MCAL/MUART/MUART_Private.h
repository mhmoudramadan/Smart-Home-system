/*
 * MUART_Private.h
 *
 *  Created on: Feb 26, 2022
 *      Author: Dell
 */

#ifndef MCAL_MUART_MUART_PRIVATE_H_
#define MCAL_MUART_MUART_PRIVATE_H_

#define UCSRC *((volatile uint8*)0x40)
#define UCSRB *((volatile uint8*)0x2A)
#define UBRRL *((volatile uint8*)0x29)
#define UCSRA *((volatile uint8*)0x2B)
#define UDR   *((volatile uint8*)0x2C)

#define CHAR_5Bit    0
#define CHAR_6Bit    1
#define CHAR_7Bit    2
#define CHAR_8Bit    3
#define CHAR_9Bit    4

#define ONE_BIT   0
#define TWO_BIT   1

#define UART_ASYNCHRONOUS  0
#define UART_SYNCHRONOUS   1

#define PARTIYCHECK_DISABLED       0
#define PARTIYCHECK_ENABLED_EVEN   1
#define PARTIYCHECK_ENABLED_ODD    2

#endif /* MCAL_MUART_MUART_PRIVATE_H_ */
