
#include <avr/io.h>
#include <avr/interrupt.h>

void UART_putchar(unsigned char data)
{
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = data;
}
void UART_putstring(unsigned char *txt)
{
	uint8_t i;

	for(i=0;i<255;i++)
	{
		if(!txt[i])	break;
		UART_putchar(txt[i]);
	}
}

unsigned char UART_getchar(void)
{
	while ( !(UCSRA & (1<<RXC)) );
	return UDR;
} 

void UART_init(unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;

	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}
ISR(USART_RXC_vect )
{
	//unsigned char c;
	//c = UDR;
}


