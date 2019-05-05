#define F_CPU 8000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <math.h>  //include libm

#include "mpu6050/mpu6050.h"
//#include "mpu6050/mpu6050dmp6.c"
//#include "uart/uart.h"
#define UART_BAUD_RATE 9600L
#define UBRRL_VAL (F_CPU / (UART_BAUD_RATE*16))-1

//#define MPU6050_GETATTITUDE 2

void init_UART()
{
	UBRRL = UBRRL_VAL;
	UBRRH = UBRRL_VAL >> 8;
	UCSRB = (1 << TXEN)|(1 << RXEN);
	UCSRC = (1 << URSEL)|(1 << UCSZ1)|(1 << UCSZ0);
}

void uart_putcc(char c)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = c;
}

void send_str_UART(char str[])
{
	unsigned char i = 0;
	 
	while (str[i]!='\0')
	{
		uart_putcc(str[i]);
		i++;
	}
}

int main(void) {

	//init uart
	init_UART();
	#if MPU6050_GETATTITUDE == 0
    int16_t ax = 0;
    int16_t ay = 0;
    int16_t az = 0;
    int16_t gx = 0;
    int16_t gy = 0;
    int16_t gz = 0;
    double axg = 0;
    double ayg = 0;
    double azg = 0;
    double gxds = 0;
    double gyds = 0;
    double gzds = 0;
	#endif

	#if MPU6050_GETATTITUDE == 1 || MPU6050_GETATTITUDE == 2
    long *ptr = 0;
    double qw = 1.0f;
	double qx = 0.0f;
	double qy = 0.0f;
	double qz = 0.0f;
	double roll = 0.0f;
	double pitch = 0.0f;
	double yaw = 0.0f;
	#endif

    

	sei();

	//init mpu6050
	mpu6050_init();
	_delay_ms(50);

	//init mpu6050 dmp processor
	#if MPU6050_GETATTITUDE == 2
	mpu6050_dmpInitialize();
	mpu6050_dmpEnable();
	_delay_ms(10);
	#endif

	for(;;) {
		#if MPU6050_GETATTITUDE == 0
		mpu6050_getRawData(&ax, &ay, &az, &gx, &gy, &gz);
		//mpu6050_getConvData(&axg, &ayg, &azg, &gxds, &gyds, &gzds);
		#endif

		#if MPU6050_GETATTITUDE == 1
		mpu6050_getQuaternion(&qw, &qx, &qy, &qz);
		mpu6050_getRollPitchYaw(&roll, &pitch, &yaw);
		
		_delay_ms(20);
		#endif

		#if MPU6050_GETATTITUDE == 2
		if(mpu6050_getQuaternionWait(&qw, &qx, &qy, &qz)) 
		{
			mpu6050_getRollPitchYaw(qw, qx, qy, qz, &roll, &pitch, &yaw);
			
			/*yaw = atan2(2*qx*qy - 2*qw*qz, 2*qw*qw + 2*qx*qx - 1);
			pitch = -asin(2*qx*qz + 2*qw*qy);
			roll = atan2(2*qy*qz - 2*qw*qx, 2*qw*qw + 2*qz*qz - 1);*/
		}
		_delay_ms(10);
		#endif

		#if MPU6050_GETATTITUDE == 0
		char itmp[10];
		ltoa(ax, itmp, 10); uart_putcc(' '); send_str_UART(itmp); uart_putcc(' ');
		ltoa(ay, itmp, 10); uart_putcc(' '); send_str_UART(itmp); uart_putcc(' ');
		ltoa(az, itmp, 10); uart_putcc(' '); send_str_UART(itmp); uart_putcc(' ');
		ltoa(gx, itmp, 10); uart_putcc(' '); send_str_UART(itmp); uart_putcc(' ');
		ltoa(gy, itmp, 10); uart_putcc(' '); send_str_UART(itmp); uart_putcc(' ');
		ltoa(gz, itmp, 10); uart_putcc(' '); send_str_UART(itmp); uart_putcc(' ');
		send_str_UART("\r\n");

/*
		dtostrf(axg, 3, 5, itmp); send_str_UART(itmp); uart_putcc(' ');
		dtostrf(ayg, 3, 5, itmp); send_str_UART(itmp); uart_putcc(' ');
		dtostrf(azg, 3, 5, itmp); send_str_UART(itmp); uart_putcc(' ');
		dtostrf(gxds, 3, 5, itmp); send_str_UART(itmp); uart_putcc(' ');
		dtostrf(gyds, 3, 5, itmp); send_str_UART(itmp); uart_putcc(' ');
		dtostrf(gzds, 3, 5, itmp); send_str_UART(itmp); uart_putcc(' ');
		send_str_UART("\r\n");
*/

		_delay_ms(50);
		#endif

		#if MPU6050_GETATTITUDE == 1 || MPU6050_GETATTITUDE == 2

		//quaternion
		ptr = (long *)(&qw);
		uart_putcc(*ptr);
		uart_putcc(*ptr>>8);
		uart_putcc(*ptr>>16);
		uart_putcc(*ptr>>24);
		ptr = (long *)(&qx);
		uart_putcc(*ptr);
		uart_putcc(*ptr>>8);
		uart_putcc(*ptr>>16);
		uart_putcc(*ptr>>24);
		ptr = (long *)(&qy);
		uart_putcc(*ptr);
		uart_putcc(*ptr>>8);
		uart_putcc(*ptr>>16);
		uart_putcc(*ptr>>24);
		ptr = (long *)(&qz);
		uart_putcc(*ptr);
		uart_putcc(*ptr>>8);
		uart_putcc(*ptr>>16);
		uart_putcc(*ptr>>24);

		//roll pitch yaw
		ptr = (long *)(&roll);
		uart_putcc(*ptr);
		uart_putcc(*ptr>>8);
		uart_putcc(*ptr>>16);
		uart_putcc(*ptr>>24);
		ptr = (long *)(&roll);
		uart_putcc(*ptr);
		uart_putcc(*ptr>>8);
		uart_putcc(*ptr>>16);
		uart_putcc(*ptr>>24);
		ptr = (long *)(&roll);
		uart_putcc(*ptr);
		uart_putcc(*ptr>>8);
		uart_putcc(*ptr>>16);
		uart_putcc(*ptr>>24);

		uart_putcc('\n');
		//_delay_ms(10);
		#endif
		
		

	}

}
