/*
 * main_Config.h
 *
 *  Created on: Apr 15, 2022 6:39:14 AM
 *      Author: mahmoud ramadan 
 */

#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

/*Login Data*/
#define MAX_LEETEROF_USER    4
#define MAX_OFUSERS          4
#define NULL_CHARACTER      '\0'
#define NULL_CHARACTER_COUNT  1
/*Login system*/
#define KEYPAD_USER          0
#define ADMIN_PRIORTY        1
#define REMOTED_USER         2
#define PROMOTED_USER        3


/*EEPROM Saved address*/
#define INITIAL_PROGRAMSTATE_ADD	0x00
#define SAVED_ADMIN_ADDRESS  		0x01
#define SAVED_USER_ADDRESS   		0x12
#define NO_OFREGISTERUSER    		0x11

/*menu option
 * 1-Door
 * 2-Air condition
 * 3-Lamps*/
#define DOOR_MENU		1
#define Air_MENU		2
#define LAMP_MENU		3
#define ADD_USER        4
#define REMOVE_USER     5

/*system Status Flag*/
#define FIRST_TIME_STATE		0xFF
#define LOAD_SYS_DATABASE  		0x00
#define IDLE_STATE      		0x02
#define REMOTE_STATE			0x03
#define KEYPAD_STATE			0x04
#define BLOCK_SYSTEM        	0x05
#define KEYPAD_STATE_SUCCESS	0x06
#define REMOTE_SYSTEM_SUCCESS      0x07

typedef struct
		{
	uint8 username[MAX_LEETEROF_USER+NULL_CHARACTER_COUNT];
	uint8 password[MAX_LEETEROF_USER+NULL_CHARACTER_COUNT];
	uint8 priorty;
		}User_t;


#endif /* MAIN_CONFIG_H_ */
