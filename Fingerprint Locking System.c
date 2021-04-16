/*
 * Project 1.c
 *
 * Created: 14-04-2021 3.40.19 PM
 * Author : mintu
 */ 

#define F_CPU 16000000UL //16 MHz clock speed
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA PORTB
#define LCD_ctrl PORTA
#define en 5
#define rw 7
#define rs 2
/*
void init_LCD(void);
void LCD_cmd(unsigned char cmd);
void LCD_write(unsigned char data);
char usart_rx(void);
void usart_init(void);

void init_LCD(void)

{

	LCD_cmd(0x38);           // initialization in 8bit mode of 16X2 LCD

	_delay_ms(1);

	LCD_cmd(0x01);          // make clear LCD

	_delay_ms(1);

	LCD_cmd(0x02);          // return home

	_delay_ms(1);

	LCD_cmd(0x06);          // make increment in cursor

	_delay_ms(1);

	LCD_cmd(0x80);          // force cursor to the beginning of first line

	_delay_ms(1);

	

	return;

}*/
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
void LCD_cmd(unsigned char cmd)
{

	LCD_DATA = cmd;      // data lines are set to send command

	PORTA  &= ~(1<<rs);  // RS sets 0

	PORTA  &= ~(1<<rw);  // RW sets 0

	PORTA  |= (1<<en);   // make enable from high to low

	_delay_ms(10);

	PORTA  &= ~(1<<en);

	

	return;

}



void LCD_write(unsigned char data)

{

	PORTA  |= (1<<rs);    // RS sets 1

	PORTA  &= ~(1<<rw);   // RW sets 0

	PORTA  |= (1<<en);    // make enable from high to low
	
	LCD_DATA = data;    // data lines are set to send command

	_delay_ms(20);

	PORTA &= ~(1<<en);

	

	return ;

}


char tx_data;
int main(void)
{
	
	DDRB=0b11111111;

	DDRA|=(1<<rs)|(1<<rw)|(1<<en);
	//init_LCD();
	 usart_init();
     _delay_ms(20);
	 while(1){
	// usart_tx('s');
      tx_data=usart_rx();
	_delay_ms(20);
	//usart_tx(tx_data);

/*	LCD_cmd(0x0C);          // display on, cursor off

_delay_ms(20);

	LCD_write(tx_data);

    _delay_ms(1);

	LCD_cmd(0x0C);*/
	if(tx_data=='T'){
	LCD_cmd(0x0C);          // display on, cursor off
	
	_delay_ms(20);
	LCD_write('U');

	_delay_ms(1);
	LCD_write('n');

	_delay_ms(20);

	LCD_write('L');

	_delay_ms(1);
	LCD_write('O');

	_delay_ms(1);
     LCD_write('C');

    _delay_ms(1);
    LCD_write('K');

    _delay_ms(1);
	LCD_cmd(0x0C);
		}else{
		LCD_cmd(0x0C);          // display on, cursor off

		_delay_ms(1);
		LCD_write('l');

		_delay_ms(1);
		LCD_write('O');

		_delay_ms(1);
		LCD_write('C');

		_delay_ms(1);
		LCD_write('K');

		_delay_ms(1);
		LCD_cmd(0x0C);
		}
	}return 0;

}