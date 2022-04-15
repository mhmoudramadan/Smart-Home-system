/*
 * MTIMER2_Private.h
 *
 *  Created on: Feb 16, 2222
 *      Author: Dell
 */

#ifndef MCAL_MTIMER2_MTIMER2_PRIVATE_H_
#define MCAL_MTIMER2_MTIMER2_PRIVATE_H_

#define TCCR2 *((volatile uint8*)0x45)
#define TIMSK *((volatile uint8*)0x59)
#define TCNT2 *((volatile uint8*)0x44)
#define OCR2 *((volatile uint8*)0x43)

#define TIMER2_CTCMODE                0
#define TIMER2_NORMALMODE             1
#define TIMER2_FASTPWMMODE            2
#define TIMER2_PWMPHASECORRECTMODE    3

#define TIMER2_PWMMODE_NON_INVERTING  2
#define TIMER2_PWMMODE_INVERTING      1

#define TIMER2_CTCMODE_NOTCONNECTED_OC2PIN   0
#define TIMER2_CTCMODE_CLR_OC2PIN            1
#define TIMER2_CTCMODE_SET_OC2PIN            2
#define TIMER2_CTCMODE_TOGGLE_OC2PIN         3

#define TIMER2_NOPRESCALER                 1
#define TIMER2_PRESCALER_8                 2
#define TIMER2_PRESCALER_32                3
#define TIMER2_PRESCALER_64                4
#define TIMER2_PRESCALER_128               5
#define TIMER2_PRESCALER_256               6
#define TIMER2_PRESCALER_1024              7
#define TIMER2_MAXCount  255

#endif /* MCAL_MTIMER2_MTIMER2_PRIVATE_H_ */
