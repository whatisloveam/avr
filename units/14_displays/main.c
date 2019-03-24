#define F_CPU 8000000UL

#define __AVR__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <src/u8g.h>

u8g_t u8g;

void u8g_setup(void)
{  
  u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x64_i2c, U8G_I2C_OPT_NONE);  
}

void draw(void)
{
	u8g_DrawLine(&u8g, 0, 0, 128, 64);
}


int main(void)
{
  u8g_setup();
  for(;;)
  {
    u8g_FirstPage(&u8g);
    do
    {
      draw();
    } while ( u8g_NextPage(&u8g) );
	_delay_ms(100);
  }
}
