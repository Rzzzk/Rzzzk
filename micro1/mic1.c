/*
 * mic1.c
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */


#include"lcd.h"
#include"keypad.h"
#include"uart.h"
#include"i2c.h"
#include"external_eeprom.h"

int main(void){

	/*****************************************************************/
	/*****************************************************************/

	/**************   password = 55 11 22 33 *************************/

	/*****************************************************************/
	/*****************************************************************/

	/*  functions initialize */
	LCD_init();
	UART_init();

	/* variables */
	uint8 key , press;
	uint8 pass[9];
	uint8 i=0;
	uint8 count=0;
	uint8 s1, s2, s3, s4, s5, s6, s7, s8;
	uint8 lastPass[9];
	uint8 newPass[9];
	uint8 key2;
	uint8 loop = 0 ;
	uint8 c = 0 ;
	uint8 buzzer = 0 ;

	/*****************************************************************/
	/******** receive the last password from micro-controller (2)*****/
	/*****************************************************************/
	s1=UART_reseiveByte();
	_delay_ms(1);
	s2=UART_reseiveByte();
	_delay_ms(1);
	s3=UART_reseiveByte();
	_delay_ms(1);
	s4=UART_reseiveByte();
	_delay_ms(1);
	s5=UART_reseiveByte();
	_delay_ms(1);
	s6=UART_reseiveByte();
	_delay_ms(1);
	s7=UART_reseiveByte();
	_delay_ms(1);
	s8=UART_reseiveByte();
	_delay_ms(1);

	/******************************/
	/* put the last pass in array */
	/******************************/
	lastPass[0]=s1;
	lastPass[1]=s2;
	lastPass[2]=s3;
	lastPass[3]=s4;
	lastPass[4]=s5;
	lastPass[5]=s6;
	lastPass[6]=s7;
	lastPass[7]=s8;

	LCD_displayString("power on .... ");
	_delay_ms(1000);
	LCD_clearScreen();

	while(1){


		key = keypad_getpressed_key();  // read the pressed key
		_delay_ms(400);

		if(key>0 && key!='#'){
			LCD_displayCharacter('*');   // display '*'
			pass[i]=key;                 // put the pressed keys in array to check
			i++;
		}
		else if (key=='#'){
			for(uint8 j=0 ; j<8 ; j++){  // check the pressed keys array whit the last password array
				if(pass[j]==lastPass[j]) count++;
			}

			/*******************************************************************/
			/* if the password is correct */

			if(count==8){
				LCD_clearScreen();
				LCD_displayString("correct password");

				/* write the code in while loop to ask again and again
				 * what the user want
				 */


				while(count==8){

					LCD_displayStringRowColumn(1,0,"wait ..... ");
					_delay_ms(1000);
					LCD_clearScreen();
					/***************************/
					LCD_displayString("(1)open,(2)close");
					LCD_displayStringRowColumn(1,0,"(3)change pass");
					_delay_ms(1000);
					LCD_clearScreen();

					press = keypad_getpressed_key();  // get the press to know what is the user want

					if(press == 1)        UART_sendByte(1); // send the press number to the other micro-cntr
					else if (press == 2)  UART_sendByte(2); // send the press number to the other micro-cntr
					/*
					 * if user want to change the password we do :
					 */
					else if(press == 3){
						loop=0;
						/* send the press number to the other micro-cntr
						 * to know
						 */
						UART_sendByte(3);
						LCD_displayString("enter password");
						LCD_displayStringRowColumn(1,0,"without (0 or #)");
						_delay_ms(1000);
						LCD_clearScreen();

						while(loop == 0 ){ // use while loop to can save the all pressed key (new pass) from user

							key2 = keypad_getpressed_key();
							_delay_ms(400);
							if(key2>0 && key2!='#'){
								LCD_displayCharacter('*');
								newPass[c]=key2;
								c++;
							}
							else if(key2 == '#'){
								/* send the new pass byte by byte thats easier for me (: */
								s1=newPass[0];
								s2=newPass[1];
								s3=newPass[2];
								s4=newPass[3];
								s5=newPass[4];
								s6=newPass[5];
								s7=newPass[6];
								s8=newPass[7];

								UART_sendByte(s1);
								_delay_ms(10);
								UART_sendByte(s2);
								_delay_ms(10);
								UART_sendByte(s3);
								_delay_ms(10);
								UART_sendByte(s4);
								_delay_ms(10);
								UART_sendByte(s5);
								_delay_ms(10);
								UART_sendByte(s6);
								_delay_ms(10);
								UART_sendByte(s7);
								_delay_ms(10);
								UART_sendByte(s8);
								_delay_ms(10);

								LCD_clearScreen();
								LCD_displayString("password changed");
								_delay_ms(1000);
								LCD_clearScreen();
								loop=1; // to get out from while loop

							}
						}
					}
					/***************************/


					i=0;
					c=0;
				}
			}
			/**********************************************************************/
			else{
				/*
				 * if the password is wrong we :
				 * increment the counter (buzzer)
				 * repeat the code
				 * if (buzzer == 3) stop every thing using infinite loop
				 *
				 */
				while(buzzer==3){
					LCD_clearScreen();
					LCD_displayString("restart");
					LCD_displayStringRowColumn(1, 0 ,"wrong password" );
					UART_sendByte(4);
				}
				LCD_clearScreen();
				LCD_displayString("wrong password");
				LCD_displayStringRowColumn(1, 0 ,"try again" );
				_delay_ms(1000);
				LCD_clearScreen();
				buzzer++ ;
				i=0;
				count=0;
			}

		}


	}
}
