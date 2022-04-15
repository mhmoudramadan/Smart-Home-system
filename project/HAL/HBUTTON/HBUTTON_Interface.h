/*
 * HBUTTOU_Interface.h
 *
 *  Created on: Jan 21, 2022
 *      Author: Dell
 */

#ifndef HAL_HBUTTON_HBUTTON_INTERFACE_H_
#define HAL_HBUTTON_HBUTTON_INTERFACE_H_


#define PULL_UP    1
#define PULL_DOWN  0

typedef struct
{
	uint8 ButtonPort;
	uint8 ButtonPin;
	uint8 ButtonActiveState;
}Button_t;


ErrorState HBUTTON_Errorstate_Button_Init(Button_t* copy_Button_object);
ErrorState HBUTTON_Errorstate_Button_Pressed(Button_t* copy_Button_object);


#endif /* HAL_HBUTTON_HBUTTON_INTERFACE_H_ */
