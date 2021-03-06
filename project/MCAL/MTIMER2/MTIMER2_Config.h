/*
 * MTIMER2_Config.h
 *
 *  Created on: Feb 16, 2222
 *      Author: Dell
 */

#ifndef MCAL_MTIMER2_MTIMER2_CONFIG_H_
#define MCAL_MTIMER2_MTIMER2_CONFIG_H_
/*Timer2 Mode Options
 * 1-TIMER2_CTCMODE
 * 2-TIMER2_NORMALMODE
 * 3-TIMER2_FASTPWMMODE
 * 4-TIMER2_PWMPHASECORRECTMODE*/

#define TIMER2SETMODE TIMER2_FASTPWMMODE

/*Timer 2 OC2 PIN Options
 * 1-TIMER2_CTCMODE_NOTCONNECTED_OC2PIN
 * 2-TIMER2_CTCMODE_CLR_OC2PIN
 * 3-TIMER2_CTCMODE_SET_OC2PIN
 * 4-TIMER2_CTCMODE_TOGGLE_OC2PIN*/

#define TIMER2_CTCMODE_OC2PINMODE  TIMER2_CTCMODE_NOTCONNECTED_OC2PIN

/*Timer2 PRESCALER OPTIONS
 * 1-TIMER2_NOPRESCALER
 * 2-TIMER2_PRESCALER_8
 * 3-TIMER2_PRESCALER_32
 * 3-TIMER2_PRESCALER_64
 * 4-TIMER2_PRESCALER_128
 * 5-TIMER2_PRESCALER_256
 * 6-TIMER2_PRESCALER_1024*/
#define MTIMER2_SET_PRESCALER   TIMER2_PRESCALER_8

/* PWM MODE OC2 Pin mode
 * 1-TIMER2_PWMMODE_NON_INVERTING -->(CLR OC2 On Compare Match and Set OC2 At Top)(CLR OC2-->upcount )
 * 2-TIMER2_PWMMODE_INVERTING -->(SET OC2 On Compare Match and CLR OC2 At Top) (SET OC2-->upcount )*/
#define TIMER2_PWMMODE_OC2PINMODE  TIMER2_PWMMODE_NON_INVERTING

#endif /* MCAL_MTIMER2_MTIMER2_CONFIG_H_ */
