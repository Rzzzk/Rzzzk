/*
 * mic2.c
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */


#include"uart.h"
#include"lcd.h"
#include"keypad.h"



	void PWM_Timer0_Init(unsigned char set_duty_cycle){

		TCNT0 = 0; //initial timer value

		OCR0  = set_duty_cycle;

		DDRB  = DDRB | (1<<PB3); //set OC0 as output pin --> pin where the PWM signal is generated from MC.

		/* Configure timer control register
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
		 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
		 */
		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
	}

int main(void){

	/*  functions initialize */

	UART_init();
	EEPROM_init();


	/* buzzer bin */
    DDRD|=(1<<PD7);

    /* variable */

	uint8 x1,x2,x3,x4,x5,x6,x7,x8;
	uint8 s1, s2, s3, s4, s5, s6, s7, s8;

/****************************************************************/
    uint8 m = 0 ;
/****************************************************************/

	    /******************************************/
		/****read the last password from EEPROM****/
		/******************************************/

		    EEPROM_readByte(0x01,&x1);
		    _delay_ms(10);
		    EEPROM_readByte(0x02,&x2);
		    _delay_ms(10);
		    EEPROM_readByte(0x03,&x3);
		    _delay_ms(10);
		    EEPROM_readByte(0x04,&x4);
		    _delay_ms(10);
		    EEPROM_readByte(0x05,&x5);
		    _delay_ms(10);
		    EEPROM_readByte(0x06,&x6);
		    _delay_ms(10);
		    EEPROM_readByte(0x07,&x7);
		    _delay_ms(10);
		    EEPROM_readByte(0x08,&x8);
		    _delay_ms(10);

		/************************************************************/
		/*** send the last password to the other micro-controller ***/
		/************************************************************/

		    UART_sendByte(x1);
		    _delay_ms(1);
		    UART_sendByte(x2);
		    _delay_ms(1);
		    UART_sendByte(x3);
		    _delay_ms(1);
		    UART_sendByte(x4);
		    _delay_ms(1);
		    UART_sendByte(x5);
		    _delay_ms(1);
		    UART_sendByte(x6);
		    _delay_ms(1);
		    UART_sendByte(x7);
		    _delay_ms(1);
		    UART_sendByte(x8);
		    _delay_ms(1);


/****************************************************************/

	while(1){

		m = UART_reseiveByte();

		if(m==1){
//if the press == 1 we rotate the motor clockwise (open the door)
			PWM_Timer0_Init(128);

			DDRA|=(1<<PA0)|(1<<PA1);
			PORTA=(1<<PA0);
			PORTA&=~(1<<PA1);

			_delay_ms(2000);
			/*stop*/
			PORTA&=~(1<<PA0);
			PORTA&=~(1<<PA1);

		}
		else if(m==2){
			//if the press == 1 we rotate the motor counter clockwise (close the door)
			PWM_Timer0_Init(128);

				DDRA|=(1<<PA0)|(1<<PA1);
				PORTA=(1<<PA1);
				PORTA&=~(1<<PA0);
				_delay_ms(2000);
				/*stop*/
				PORTA&=~(1<<PA1);
				PORTA&=~(1<<PA0);

		}
		else if(m==3){ // change password
/*receive the new password */
			s1=UART_reseiveByte();
			_delay_ms(10);
			s2=UART_reseiveByte();
			_delay_ms(10);
			s3=UART_reseiveByte();
			_delay_ms(10);
			s4=UART_reseiveByte();
			_delay_ms(10);
			s5=UART_reseiveByte();
			_delay_ms(10);
			s6=UART_reseiveByte();
			_delay_ms(10);
			s7=UART_reseiveByte();
			_delay_ms(10);
			s8=UART_reseiveByte();
			_delay_ms(10);
 /*write the new password in WWPROM*/
			EEPROM_writeByte(0x1,s1);
			_delay_ms(10);
			EEPROM_writeByte(0x2,s2);
			_delay_ms(10);
			EEPROM_writeByte(0x3,s3);
			_delay_ms(10);
			EEPROM_writeByte(0x4,s4);
			_delay_ms(10);
			EEPROM_writeByte(0x5,s5);
			_delay_ms(10);
			EEPROM_writeByte(0x6,s6);
			_delay_ms(10);
			EEPROM_writeByte(0x7,s7);
			_delay_ms(10);
			EEPROM_writeByte(0x8,s8);
			_delay_ms(10);




		    /******************************************/
			/****read the last password from EEPROM****/
			/******************************************/

			    EEPROM_readByte(0x01,&x1);
			    _delay_ms(10);
			    EEPROM_readByte(0x02,&x2);
			    _delay_ms(10);
			    EEPROM_readByte(0x03,&x3);
			    _delay_ms(10);
			    EEPROM_readByte(0x04,&x4);
			    _delay_ms(10);
			    EEPROM_readByte(0x05,&x5);
			    _delay_ms(10);
			    EEPROM_readByte(0x06,&x6);
			    _delay_ms(10);
			    EEPROM_readByte(0x07,&x7);
			    _delay_ms(10);
			    EEPROM_readByte(0x08,&x8);
			    _delay_ms(10);

		}

		else if(m==4){

			PORTD|=(1<<PD7); // buzzer on

		}



}
}
