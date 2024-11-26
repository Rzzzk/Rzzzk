/*
 * lcd.c
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */


#include"lcd.h"

void LCD_init(void){

	LCD_DATA_DIR=0xFF; //set data port as output
	LCD_CTR_DIR|=(1<<RS)|(1<<E)|(1<<RW); // set (RS , E & RW ) output

	LCD_sendCommand(TWO_LINE_EIGHT_BIN); // mode 2*8
	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF); // cursor off
	LCD_sendCommand(CLEAR_SCREEN); // clear the display screen

}

void LCD_sendCommand(uint8 command){

	/*control RS & RW*/
	/*clear (RS & RW)*/
	CLEAR_BIT(LCD_CTR_PORT,RS);// RS= LOW -> instruction  mode
	CLEAR_BIT(LCD_CTR_PORT,RW);// RW= LOW -> write        mode

	_delay_ms(1);
	SET_BIT(LCD_CTR_PORT,E);   // set enable
	_delay_ms(1);
	LCD_DATA_PORT= command;    //send command
	_delay_ms(1);
	CLEAR_BIT(LCD_CTR_PORT,E); //clear enable
	_delay_ms(1);

}


void LCD_displayCharacter(uint8 data){

	/*control RS & RW*/
	/*clear (RS & RW)*/
	SET_BIT(LCD_CTR_PORT,RS);   // RS= HIGH -> data  mode
	CLEAR_BIT(LCD_CTR_PORT,RW); // RW= LOW  -> write mode

	_delay_ms(1);
	SET_BIT(LCD_CTR_PORT,E);   // set enable
	_delay_ms(1);
	LCD_DATA_PORT= data;       //send command
	_delay_ms(1);
	CLEAR_BIT(LCD_CTR_PORT,E); //clear enable
	_delay_ms(1);

}

void LCD_displayString(const char *str){
	uint8 i;
	while(str[i]!='\0'){
		LCD_displayCharacter(str[i]);
		i++;
	}
}


void LCD_goToRowColumn(uint8 row , uint8 col){
	uint8 address;
	switch(row){
	case 0 :
		address = col;
		break;
	case 1 :
		address = col+0x40;
		break;
	case 2 :
		address = col+0x10;
		break;
	case 3 :
		address = col+0x50;
	}

	LCD_sendCommand(address | SET_CURSOR_AT_FIRST);

}

void LCD_displayStringRowColumn(uint8 row , uint8 col , const char *str){

	LCD_goToRowColumn(row , col);
	LCD_displayString(str);

}



void LCD_intToStr(int data){
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}

void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_SCREEN);
}
