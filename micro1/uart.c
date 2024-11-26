/*
 * uart.c
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */


#include "uart.h"

#define BAUD_RRESCALE ((( F_CPU) / (USART_BAUDRATE * 8UL))-1)

void UART_init(void){

	UCSRA |=(1<<U2X); // double speed
	/*
	 * disable RX Complete Interrupt Enable [RXCIE=0]
	 * disable TX Complete Interrupt Enable [TXCIE=0]
	 * disable USART Data Register Empty Interrupt Enable  [UDRIE=0]
	 *
	 *++++++++>>>>> Receiver    Enable [RXEN=1]
	 *++++++++>>>>> Transmitter Enable [TXEN=1]
	 *
     * disable Transmit Data Bit 8  [TXB8=0]
     * disable Receive  Data Bit 8  [RXB8=0]
     * Character Size --> 8bit [UCSZ2=0]
	 */

	UCSRB |=(1<<RXEN)|(1<<TXEN);

	/* Register Select [RXEN=1]
	 * Asynchronous Operation [UMSEL=0]
	 * disable parity [UPM1=0 & UPM0=0]
	 * 1 stop bit [USBS=0]
	 * 8 bit [UCSZ2=0 , UCSZ1=1 & UCSZ0=1]
	 * disable clock polarity [UCPOL=0]
	 */

	UCSRC |=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

    // write the baud pre-scaler on Baud Rate Registers
	UBRRH = BAUD_RRESCALE >> 8;
	UBRRL = BAUD_RRESCALE ;

}

void UART_sendByte(uint8 data){

	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	UDR=data;

}

uint8 UART_reseiveByte(void){

	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	return UDR ;
}


void UART_sendString(const uint8 *str){
	uint8 i=0;
	while(str[i]!='\0'){
		UART_sendByte(str[i]);
		i++;
	}
}

void UART_reseiveString(uint8 *str){
	uint8 i=0;
	str[i]= UART_reseiveByte();
	while(str[i]!= '*'){
		i++;
		str[i]= UART_reseiveByte();
	}
	str[i]='\0';
}

void UART_sendPass(uint8 arr[]){
	uint8 i=0;
	while(arr[i]!='\0'){
		UART_sendByte(arr[i]);
		i++;
	}
}


void UART_reseivePass(uint8 arr[]){

	    uint8 i=0;
		arr[i]= UART_reseiveByte();
		while(arr[i]!='*'){
			i++;
			arr[i]= UART_reseiveByte();
		}
		arr[i]='\0';
}





