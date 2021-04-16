/*
 * UART 3.c
 *
 * Created: 14-04-2021 11.37.30 PM
 * Author : mintu
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL

void usart_init(void);		//--- Usart Initialize
void usart_tx(char x);		//--- Usart Transmit
char usart_rx(void);		//--- Usart Receive
void usart_msg(char *c);	//--- Usart Transmit String
char tx_data;

int main(void)
{
	usart_init();

	char r='e';						//--- Usart initializing
	usart_tx(r);	//--- Send a set of String
	//while(1)
	//{
	tx_data = usart_rx();			//--- Receive the data from rxd
	usart_tx(tx_data);				//--- send the received data back
	//}
}

void usart_init()
{	UCSRC &= ~(1 << UMSEL); //setting the UMSEL bit to 0 for asynchronous mode
	int UBBR_Value=25;
	//Put the upper part of the baud number here (bits 8 to 11)
	UBRRH = (unsigned char) (UBBR_Value >> 8);

	//Put the remaining part of the baud number here
	UBRRL = (unsigned char) UBBR_Value;
	UCSRB |= (1 << RXEN) | (1 << TXEN);	/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (3 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit char size */

	
}

void usart_tx(char x)
{
	//Wait until the Transmitter is ready
	while (! (UCSRA & (1 << UDRE)) );
	UDR = x;//Get that data outa here!
}

char usart_rx()
{		char ch;
	while ((UCSRA & (1<<RXC))==0){
		
	};		//--- Check whether Receive is complete
	ch=UDR;
	return ch;						//--- Return Data from UDR
}

void usart_msg(char *c)
{
	while (*c != 0)						//--- Check for null
	usart_tx(*c++);
}