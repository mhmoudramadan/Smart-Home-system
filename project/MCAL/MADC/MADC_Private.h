/*
 * MADC_Private.h
 *
 *  Created on: Feb 5  2022
 *      Author: Dell
 */

#ifndef MCAL_MADC_MADC_PRIVATE_H_
#define MCAL_MADC_MADC_PRIVATE_H_

#define ADMUX  	*((volatile uint8*)0x27)
#define ADCSRA  *((volatile uint8*)0x26)
#define SFIOR  	*((volatile uint8*)0x50)
#define ADCH  	*((volatile uint8*)0x25)
#define ADCL  	*((volatile uint8*)0x24)

#define MADC_Vref_AVCC             1
#define MADC_Vref_INTERNAL_2_56    0

#define MADC_RIGHT_ADJUST  1
#define MADC_LEFT_ADJUST   0

#define ADC_PRESCALER_2    1
#define ADC_PRESCALER_4    2
#define ADC_PRESCALER_8    3
#define ADC_PRESCALER_16   4
#define ADC_PRESCALER_32   5
#define ADC_PRESCALER_64   6
#define ADC_PRESCALER_128  7

#define MADC_FREERUNNING                     0
#define MADC_ANALOGCOMPARATOR                2
#define MADC_EXTI0                           4
#define MADC_TIMER_COUNTER0_COMPAREMATCH     6
#define MADC_TIMER_COUNTER0_OVERFLOW         8
#define MADC_TIMER_COUNTER0_COMPAREMATCH_B   10
#define MADC_TIMER_COUNTER1_OVERFLOW         12
#define MADC_TIMER_COUNTER1_CAPTUREEVENT     14

#define MADC_SINGLEENDED_CHANNEL  1
#define MADC_DIFFERENTIAL_CHANNEL 0

#endif /* MCAL_MADC_MADC_PRIVATE_H_ */
