#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/iom8.h>

void ADC_init()
{
         ADMUX = 0x00;
         ADCSRA = 0x8D;
}

unsigned int ADC_result(unsigned char adc_input)
{
         ADMUX=adc_input | (ADMUX & 0xF0);
         _delay_us(10);
         ADCSRA |= 0x40;
         while((ADCSRA & 0x10)==0);
        ADCSRA|=0x10;
        return ADCW;
}

int main(void)
{
    DDRB = 0x0F; 
	ICR1 = 255;		//Set TOP value 
	
	TCCR1A = 0xA1;//0b 1010 0001 
	TCCR1B = 0x09;//00001001 
	OCR1A = 200;
	OCR1B = 50;
	
	ADC_init();
	DDRD = 0xFF;
	int val;
	
	//(1 << WGM12) | (1 << CS10)	
	//sei();
	
   while (1)
   {
		val = ADC_result(0)/4;
		OCR1A = val;
		val = ADC_result(1)/4;
		OCR1B = val;
		
   }
	return 0;
}