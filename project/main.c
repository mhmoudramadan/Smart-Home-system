/*
 * main.c
 *
 *  Created on: Apr 13, 2022 6:20:42 AM
 *      Author: mahmoud ramadan 
 */
#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"MCAL/MEEPROM/MEEPROM_Interface.h"
#include"MCAL/MUART/MUART_Interface.h"
#include"MCAL/MGIE/MGIE_Interface.h"
#include"MCAL/MEXTI/MEXTI_Interface.h"
#include"HAL/HCLCD/HCLCD_Config.h"
#include"HAL/HCLCD/HCLCD_Interface.h"
#include"HAL/HKPD/HKPD_Config.h"
#include"HAL/HKPD/HKPD_Interface.h"
#include"HAL/HTEMPERATURE/HTEMPERATURE_Interface.h"
#include"HAL/HSERVO/HSERVO_Interface.h"
#include"HAL/HBUTTON/HBUTTON_Interface.h"
#include"LOGINSYSTEM/LOGINSYSTEM_Config.h"
#include"LOGINSYSTEM/LOGINSYSTEM_Interface.h"

#include<util/delay.h>
#define F_CPU  16000000UL
/*Global Variables and Flag*/
Button_t Global_ButtonInterrupt={MDIO_PORTD,PIN2,PULL_UP};
uint8 Global_LoginAdminFlag=0;
uint8 Global_LoginPromotedFlag=0;
uint8 Global_SysFlag=0;
uint8 Global_BlockFlag=0;
uint8 Global_ButtonPressed;
/*Fun for interrupt*/
void App_ButtonPressed(void);
int main(void)
{
	/*Local Variable*/
	User_t Loc_LoginAdmin;
	User_t Loc_SysUsers[MAX_OFUSERS];
	uint8 Loc_SysNo_OfUsers=0;
	uint8 Loc_UserName[MAX_LEETEROF_USER+NULL_CHARACTER_COUNT];
	uint8 Loc_Password[MAX_LEETEROF_USER+NULL_CHARACTER_COUNT];
	uint8 Loc_Sys_Try=3;
	uint8 Loc_KeyPadStatus;
	uint8 Loc_Temp;
	uint8 Loc_State;
	/*Initialize LCD Pins*/
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RS_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RW_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,E_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN4,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN5,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN6,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN7,PIN_OUTPUT);
	/*Initialize TX and Rx*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN0,PIN_INPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN1,PIN_OUTPUT);
	/*Initialize ADC Pin As input For Temperature Sensor*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN0,PIN_INPUT);
	/*initialize PIN D6 for DC motor as output */
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN6,PIN_OUTPUT);
	/*Buzzer Signal Pin C7*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTC,PIN7,PIN_OUTPUT);

	/*Initialize Functions*/
	MUART_VidInit();
	HAL_VidHCLCD_4BitModeInit();
	HKPD_VidInit();
	HSERVO_VidInit();
	HTEMP_VidInit();
	HBUTTON_Errorstate_Button_Init(&Global_ButtonInterrupt);
	MGIE_Enable();
	MEXTI_VidInitEXTI0();
	Global_ButtonPressed=HBUTTON_Errorstate_Button_Pressed(&Global_ButtonInterrupt);
	MEXTI0_VidSetCallBack(App_ButtonPressed);

	/*Welcome Message*/
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"WelcomeToSmart");
	HAL_VidHCLCD_4BitModeSetPosition(2,0);
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"Home..");
	_delay_ms(5000);
	MEEPROM_uint8ReadByteFromAddress(INITIAL_PROGRAMSTATE_ADD,&Global_SysFlag);
	_delay_ms(1000);
	HAL_VidHCLCD_4BitModeSendCommand(0x01);
	/*For First Time Using*/
	if(Global_SysFlag==FIRST_TIME_STATE)
	{
		MEEPROM_VidWriteByteToAddress(NO_OFREGISTERUSER,Loc_SysNo_OfUsers);
		_delay_ms(100);
		HAL_VidHCLCD_4BitModeWriteString((uint8*)"FirstTimeUse");
		_delay_ms(1000);
		HAL_VidHCLCD_4BitModeSendCommand(0x01);
		HAL_VidHCLCD_4BitModeWriteString((uint8*)"RegisterAdmin");
		HAL_VidHCLCD_4BitModeSetPosition(2,0);
		HAL_VidHCLCD_4BitModeWriteString((uint8*)"ByKeyPad");
		_delay_ms(1000);
		/*Get Data*/
		LOGIN_USERDATA_KEYPAD(Loc_LoginAdmin.username,Loc_LoginAdmin.password);
		Loc_LoginAdmin.priorty=ADMIN_PRIORTY;
		/*Save Data of Admin*/
		MEEPROM_VidWriteBlockToAddress(SAVED_ADMIN_ADDRESS,Loc_LoginAdmin.username,MAX_LEETEROF_USER);
		_delay_ms(100);
		MEEPROM_VidWriteBlockToAddress(SAVED_ADMIN_ADDRESS+MAX_LEETEROF_USER,Loc_LoginAdmin.password,MAX_LEETEROF_USER);
		_delay_ms(100);
		MEEPROM_VidWriteByteToAddress(INITIAL_PROGRAMSTATE_ADD,LOAD_SYS_DATABASE);
		_delay_ms(100);
		HAL_VidHCLCD_4BitModeSendCommand(0x01);
		HAL_VidHCLCD_4BitModeWriteString((uint8*)"Saved");
		Global_SysFlag=IDLE_STATE;
	}
	else if(Global_SysFlag==LOAD_SYS_DATABASE)
	{
		MEEPROM_uint8ReadByteFromAddress(NO_OFREGISTERUSER,&Loc_SysNo_OfUsers);
		_delay_ms(50);
		MEEPROM_VidReadBlockFromAddress(SAVED_ADMIN_ADDRESS,Loc_LoginAdmin.username,MAX_LEETEROF_USER);
		Loc_LoginAdmin.username[MAX_LEETEROF_USER]= NULL_CHARACTER;
		MEEPROM_VidReadBlockFromAddress(SAVED_ADMIN_ADDRESS+MAX_LEETEROF_USER,Loc_LoginAdmin.password,MAX_LEETEROF_USER);
		Loc_LoginAdmin.password[MAX_LEETEROF_USER]=NULL_CHARACTER;
		Loc_LoginAdmin.priorty=ADMIN_PRIORTY;
		static uint16 Loc_address=0;
		for(uint8 Loc_Counter=0;Loc_Counter<Loc_SysNo_OfUsers;Loc_Counter++)
		{
			Loc_address=SAVED_USER_ADDRESS+(Loc_Counter*(2*MAX_LEETEROF_USER+1));
			MEEPROM_VidReadBlockFromAddress(Loc_address, Loc_SysUsers[Loc_Counter].username,MAX_LEETEROF_USER);
			_delay_ms(50);
			MEEPROM_VidReadBlockFromAddress(Loc_address+MAX_LEETEROF_USER,Loc_SysUsers[Loc_Counter].password,MAX_LEETEROF_USER);
			_delay_ms(50);
			MEEPROM_uint8ReadByteFromAddress(Loc_address+(2*MAX_LEETEROF_USER),&Loc_SysUsers[Loc_Counter].priorty);
			Loc_SysUsers[Loc_Counter].username[MAX_LEETEROF_USER]=NULL_CHARACTER;
			Loc_SysUsers[Loc_Counter].password[MAX_LEETEROF_USER]=NULL_CHARACTER;
		}
		Global_SysFlag=IDLE_STATE;
	}

	while(1)
	{
		/*While LCD & KEYPAD And Remote NOT Used IDLE STATE*/
		if(Global_SysFlag==IDLE_STATE)
		{
			MUART_vidSendString((uint8*)"Enter Key (1) To Login To Smart System ");
			HAL_VidHCLCD_4BitModeSendCommand(0x01);
			uint8 Loc_CheckUART=0;
			if(Loc_State==0)
			{
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"ALL DEVICES");
				HAL_VidHCLCD_4BitModeSetPosition(2,0);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"OFF");
			}
			while(Global_SysFlag==IDLE_STATE)
			{
				Loc_CheckUART=MUART_uint8ReciverChar();
				if(Loc_CheckUART==1)
				{
					Global_SysFlag=REMOTE_STATE;
				}
				else
				{
					MUART_vidSendString((uint8*)"Press Push button to enter keypad mode");
					Global_SysFlag=KEYPAD_STATE;
				}
			}
		}
		/*First State Remote State login*/
		while(Global_SysFlag==REMOTE_STATE)
		{
			uint8 Loc_AdmintrueFlag;
			uint8 Loc_UserRemoteTrueFlag;
			RemoteLogin_UART_Option(Loc_UserName,Loc_Password);
			Loc_AdmintrueFlag = (RemoteLogin_uint8Compare(Loc_UserName,Loc_LoginAdmin.username)) && (RemoteLogin_uint8Compare(Loc_Password,Loc_LoginAdmin.password));
			if(Loc_AdmintrueFlag==1)
			{
				MUART_vidSendString((uint8*)"Admin Login Success");
				Global_LoginAdminFlag=1;
				Global_SysFlag=REMOTE_SYSTEM_SUCCESS;
			}
			else
			{
				for(uint8 i=0;i<Loc_SysNo_OfUsers;i++)
				{
					/*Check For Promoted user*/
					Loc_UserRemoteTrueFlag=(RemoteLogin_uint8Compare(Loc_SysUsers[i].username,Loc_UserName));
					if(Loc_UserRemoteTrueFlag==1)
					{
						if(Loc_SysUsers[i].priorty==PROMOTED_USER)
						{
						MUART_vidSendString((uint8*)"User Logged In Success");
						_delay_ms(1000);
						Global_LoginPromotedFlag=1;
						Global_SysFlag=REMOTE_SYSTEM_SUCCESS;
						}
						break;
					}
					else
					{
						Global_LoginPromotedFlag=0;
					}
					break;
				}
			}
			/*Check for Login system Try*/
			if((Loc_AdmintrueFlag==0) && (Loc_UserRemoteTrueFlag==0))
			{
				Loc_Sys_Try--;
				MUART_vidSendString((uint8*)"\r Wrong User bname Or Password");
				_delay_ms(500);
				MUART_vidSendString((uint8*)"Try again\r");
				if(Loc_Sys_Try==0)
				{
					Global_SysFlag=BLOCK_SYSTEM;
				}
			}
		}
		while(Global_SysFlag==REMOTE_SYSTEM_SUCCESS)
		{
			/*options for user and admin
			 * 1-door
			 * 2-Air Condition
			 * 3-Lamps*/
			uint8 Loc_chekUartOption;
			uint8 Loc_CheckMenu;
			MUART_vidSendString((uint8*)"\r\n1 Door menu ");
			MUART_vidSendString((uint8*)"\r\n2 Air menu ");
			MUART_vidSendString((uint8*)"\r\n3 Lamps menu ");

			/*this option is for admin only*/
			if(Global_LoginAdminFlag==1)
			{
				/*1-Add
				 *2-Remove user*/
				MUART_vidSendString((uint8*)"\r\n4 Add user Press ");
				MUART_vidSendString((uint8*)"\r\n5 Remove user Press ");
				Loc_chekUartOption=MUART_uint8ReciverChar();
			}
			else
			{
				Loc_chekUartOption=MUART_uint8ReciverChar();
			}
			switch(Loc_chekUartOption)
			{
			case DOOR_MENU:
			{

				MUART_vidSendString((uint8*)"\r\n1 press 1 for open \r\n2 press 2 to close");
				Loc_CheckMenu=MUART_uint8ReciverChar();
				switch(Loc_CheckMenu)
				{
				case '1':
				{
					HSERVO_VidSetAngle(90);
					break;
				}
				case '2':
				{
					HSERVO_VidSetAngle(0);
					break;
				}
				}
				break;
			}
			case Air_MENU:
			{
				MUART_vidSendString((uint8*)"\r\n1 press 1 for on \r\n2 press 2 for off");
				Loc_CheckMenu=MUART_uint8ReciverChar();
				switch(Loc_CheckMenu)
				{
				Loc_Temp=HTEMP_uintGetTemp(0);
				case '1':
				{
					if(Loc_Temp>28)
					{
						MDIO_Errorstate_SetPinValue(MDIO_PORTD,PIN6,PIN_HIGH);
						/*Dc on*/
					}
					break;
				}
				case'2':
				{
					if(Loc_Temp<21)
					{
						/*Dc off*/
						MDIO_Errorstate_SetPinValue(MDIO_PORTD,PIN6,PIN_LOW);
					}
					break;
				}
				break;
			}
			case LAMP_MENU:
			{
				MUART_vidSendString((uint8*)"\r\n1 press 1 for L1 \r\n2 press 2 for l2\r\n3 press 3 for l3\r\n2 press 4 for l4\r\n5 press 5 for l5");
				Loc_CheckMenu=MUART_uint8ReciverChar();
				switch(Loc_CheckMenu)
				{
				case '1':
				{
					/*Lamp 1*/
				}
					break;
				}
				case '2':
				{
					/*Lamp 2*/
					break;
				}
				case'3':
				{
					/*Lamp 3*/
					break;
				}
				case'4':
				{
					/*Lamp 4*/
					break;
				}
				case'5':
				{
					/*Lamp 5*/
					break;
				}
				}
				break;
			}
			case ADD_USER:
			{
				MUART_vidSendString((uint8*)"\r\n1 press 1 for Add user");
				Loc_CheckMenu=MUART_uint8ReciverChar();
				switch(Loc_CheckMenu)
				{
				case '1':
				{
					/*Get new data*/
					if(Loc_SysNo_OfUsers < MAX_OFUSERS)
					{
						RemoteLogin_UART_Option(Loc_SysUsers[Loc_SysNo_OfUsers].username,Loc_SysUsers[Loc_SysNo_OfUsers].password);
					}
					else
					{
						MUART_vidSendString((uint8*)"\rReach max user couldn't add new user");
					}
					break;
				}
				}
				break;
			}
			case REMOVE_USER:
			{
				MUART_vidSendString((uint8*)"\r\n1 press 1 for Remove user");
				Loc_CheckMenu=MUART_uint8ReciverChar();
				switch(Loc_CheckMenu)
				{
				case '1':
				{
					/*remove user*/
					if(RemoveUser_Login(Loc_SysUsers,&Loc_SysNo_OfUsers)==1)
					{
						MUART_vidSendString((uint8*)"\r Remove Success");
					}
					else
					{
						MUART_vidSendString((uint8*)"\r user name not found");
					}
					break;
				}
				break;
			}
			default:
				MUART_vidSendString((uint8*)"\r invalid Choice");
				break;
			}
		}
	}
		/*Second State LCD & KEYPAD login*/
		while(Global_SysFlag==KEYPAD_STATE)
		{
			HAL_VidHCLCD_4BitModeSendCommand(0x01);
			HAL_VidHCLCD_4BitModeWriteString((uint8*)"User Login");
			uint8 Loc_LoginTrueFlag;
			_delay_ms(500);
			HAL_VidHCLCD_4BitModeSendCommand(0x01);
			LOGIN_USERDATA_KEYPAD(Loc_UserName,Loc_Password);
			/*Search for validation of user*/
			for(uint8 i=0;i<Loc_SysNo_OfUsers;i++)
			{
				Loc_LoginTrueFlag=RemoteLogin_uint8Compare((Loc_SysUsers[i].username),Loc_UserName) && RemoteLogin_uint8Compare((Loc_SysUsers[i].password),Loc_Password);
				if(Loc_LoginTrueFlag==1)
				{
					if(Loc_SysUsers[i].priorty==KEYPAD_USER)
					{
						Loc_Sys_Try=3;
						HAL_VidHCLCD_4BitModeSendCommand(0x01);
						HAL_VidHCLCD_4BitModeWriteString((uint8*)"Logged In");
						Global_SysFlag=KEYPAD_STATE_SUCCESS;
						break;
					}
					else
					{
						Loc_LoginTrueFlag=0;
					}
				}
			}
			if(Loc_LoginTrueFlag==0)
			{
				Loc_Sys_Try--;
				HAL_VidHCLCD_4BitModeSendCommand(0x01);
				_delay_ms(500);
				HAL_VidHCLCD_4BitModeSetPosition(1,0);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"WrongUserName");
				HAL_VidHCLCD_4BitModeSetPosition(2,0);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"WrongPassword");
				if(Loc_Sys_Try==0)
				{
					Global_SysFlag=BLOCK_SYSTEM;
				}
			}
		}
		/*Check For Admin and user Global flag to set menu options */
		while(Global_SysFlag==KEYPAD_STATE_SUCCESS)
		{
			/*Logic code of servo motor and Air condition*/
			HAL_VidHCLCD_4BitModeSendCommand(0x01);
			HAL_VidHCLCD_4BitModeWriteString((uint8*)"1:Door 2:Air");
			HAL_VidHCLCD_4BitModeSetPosition(2,0);
			HAL_VidHCLCD_4BitModeWriteString((uint8*)"3:Brightness");
			Loc_KeyPadStatus=HKPD_uint8GetPressed();
			switch(Loc_KeyPadStatus)
			{
			case'1':
			{
				HAL_VidHCLCD_4BitModeSendCommand(0x01);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"1:open 2:close");
				Loc_KeyPadStatus=HKPD_uint8GetPressed();
				if(Loc_KeyPadStatus=='1')
				{
					/*Door open*/
					HSERVO_VidSetAngle(90);
				}
				else if(Loc_KeyPadStatus=='2')
				{
					HSERVO_VidSetAngle(0);
				}
				else
				{
					/*Do Nothing*/
					HAL_VidHCLCD_4BitModeSendCommand(0x01);
					HAL_VidHCLCD_4BitModeWriteString((uint8*)"invalid choice");
				}
				break;
			}
			case '2':
			{
				HAL_VidHCLCD_4BitModeSendCommand(0x01);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"1:on 2:off");
				Loc_KeyPadStatus=HKPD_uint8GetPressed();
				Loc_Temp=HTEMP_uintGetTemp(0);
				if(Loc_KeyPadStatus=='1')
				{

					if(Loc_Temp>28)
					{
						/*DC open*/
						MDIO_Errorstate_SetPinValue(MDIO_PORTD,PIN6,PIN_HIGH);
					}

				}
				else if(Loc_KeyPadStatus=='2')
				{
					if(Loc_Temp<21)
					{
						/*DC off*/
						MDIO_Errorstate_SetPinValue(MDIO_PORTD,PIN6,PIN_HIGH);
					}
				}
				else
				{
					/*Do Nothing*/
					HAL_VidHCLCD_4BitModeSendCommand(0x01);
					HAL_VidHCLCD_4BitModeWriteString((uint8*)"invalid choice");
				}
				break;
			}
			case '3':
			{
				HAL_VidHCLCD_4BitModeSendCommand(0x01);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"1:L1 2:L2 3:L3");
				HAL_VidHCLCD_4BitModeSetPosition(2,0);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"4:L1 5:L5");
				Loc_KeyPadStatus=HKPD_uint8GetPressed();
				switch(Loc_KeyPadStatus)
				{
				case'1':
				{
					/*L1*/
					break;
				}
				case'2':
				{
					/*L2*/
					break;
				}
				case'3':
				{
					/*L3*/
					break;
				}
				case'4':
				{
					/*L4*/
					break;
				}
				case'5':
				{
					/*L5*/
					break;
				}
				}
				break;
			}
			default:
				HAL_VidHCLCD_4BitModeSendCommand(0x01);
				HAL_VidHCLCD_4BitModeWriteString((uint8*)"invalid choice");
				break;
			}
		}
		/*Check For Block System*/
		if(Global_SysFlag==BLOCK_SYSTEM)
		{
			/*Buzzer and Freeze system*/
			MEEPROM_VidWriteByteToAddress(INITIAL_PROGRAMSTATE_ADD,BLOCK_SYSTEM);
			HAL_VidHCLCD_4BitModeSendCommand(0x01);
			HAL_VidHCLCD_4BitModeWriteString((uint8*)"YOUAREBLOCKED");
			MDIO_Errorstate_SetPinValue(MDIO_PORTC,PIN7,PIN_HIGH);
			Global_BlockFlag=1;
		}
	}
	return 0;
}
void App_ButtonPressed(void)
{
	if(!(Global_LoginAdminFlag || Global_LoginPromotedFlag || Global_BlockFlag))
	{
		Global_SysFlag=KEYPAD_STATE;
	}
}
