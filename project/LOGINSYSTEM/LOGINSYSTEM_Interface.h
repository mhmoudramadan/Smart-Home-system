/*
 * LOGINSYSTEM_Interface.h
 *
 *  Created on: Apr 12, 2022 1:49:15 AM
 *      Author: mahmoud ramadan 
 */

#ifndef LOGINSYSTEM_LOGINSYSTEM_INTERFACE_H_
#define LOGINSYSTEM_LOGINSYSTEM_INTERFACE_H_
#include"../main_Config.h"
ErrorState RemoteLogin_UART_Option(uint8 *copy_UserName,uint8 *copy_Password);
ErrorState SaveUser_Login(User_t copy_Strusername,uint8 *copy_NooFRegister);
ErrorState LOGIN_USERDATA_KEYPAD(uint8 *Copy_Username,uint8 *Copy_Password);
uint8 RemoteLogin_uint8Compare(uint8 *Copy_uint8User1,uint8 *Copy_uint8User2);
uint8 RemoveUser_Login(User_t *username,uint8 *copy_NooFRegister);
#endif /* LOGINSYSTEM_LOGINSYSTEM_INTERFACE_H_ */
