#include <avr/io.h>
int main(void) { 
	DDRB = 0xFF;

	while(1) 
	{ 
		PORTB = 0b00000001;
	} 
	return 0;
}
  