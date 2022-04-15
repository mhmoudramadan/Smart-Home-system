/*
 * MTIMER1_Private.h
 *
 *  Created on: Feb 15, 2022
 *      Author: Dell
 */

#ifndef MCAL_MTIMER1_MTIMER1_PRIVATE_H_
#define MCAL_MTIMER1_MTIMER1_PRIVATE_H_

#define TCCR1A  *((volatile uint8*)0x4F)
#define TCCR1B  *((volatile uint8*)0x4E)
#define TIMSK   *((volatile uint8*)0x59)

#define TCNT1  *((volatile uint16*)0x4C)

#define OCR1A  *((volatile uint16*)0x4A)

#define OCR1B  *((volatile uint16*)0x48)

#define ICR1  *((volatile uint16*)0x46)


#define TIMER1_CTCMODE_OC1A_OC1BPIN_NOTCONNECTED  0
#define TIMER1_CTCMODE_TOGGLEOC1A_OC1BPIN         1
#define TIMER1_CTCMODE_CLROC1A_OC1BPIN            2
#define TIMER1_CTCMODE_SETOC1A_OC1BPIN            3

#define TIMER1_PWMMODE_NON_INVERTING  0
#define TIMER1_PWMMODE_INVERTING      1

#define TIMER1_NORMALMODE                                     0
#define TIMER1_CTCMODE                                        1
#define TIMER1_PWMPHASECOORECT_8_BIT_MODE                     2
#define TIMER1_PWMPHASECOORECT_9_BIT_MODE                     3
#define TIMER1_PWMPHASECOORECT_10_BIT_MODE                    4
#define TIMER1_FASTPWM_8_BIT_MODE                             5
#define TIMER1_FASTPWM_9_BIT_MODE                             6
#define TIMER1_FASTPWM_10_BIT_MODE                            7
#define TIMER1_PWMPHASECOORECT_FREQUENCYCORRECT_MODE_ICR      8
#define TIMER1_PWMPHASECOORECT_FREQUENCYCORRECT_MODE_OCR1A    9
#define TIMER1_PWMPHASECOORECT_MODE_ICR                       10
#define TIMER1_PWMPHASECOORECT_MODE_OCR1A                     11
#define TIMER1_CTC_MODE                                       12
#define TIMER1_FASTPWM_MODE_ICR                               13
#define TIMER1_FASTPWM_MODE_OCR1A                             14

#define TIMER1_NOPRESCALER                 1
#define TIMER1_PRESCALER_8                 2
#define TIMER1_PRESCALER_64                3
#define TIMER1_PRESCALER_256               4
#define TIMER1_PRESCALER_1024              5
#define TIMER1_EXTRERNALCLOCK_FALLINGEDGE  6
#define TIMER1_EXTRERNALCLOCK_RISINGEDGE   7

#define ICU_FALLING_EDGE  0
#define ICU_RISING_EDGE   1

#endif /* MCAL_MTIMER1_MTIMER1_PRIVATE_H_ */
