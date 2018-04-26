/*
 * orientation.c
 *
 * Created: 21/04/2018 12:00:10 PM
 * Author : yonas
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "I2C_Master_H_file.h"
#define PI 3.14159265359
#define declination 0.1916953295

#define LED PA0
#define SWITCH PC0

int Magneto_GetHeading()
{
	int x, y, z;
	double Heading;
	I2C_Start_Wait(0x3C); // Start and Wait for Acknowledgement
	I2C_Write(0x03); // Write Memory Location address
	I2C_Repeated_Start(0x3D); // Generate Repeat Start Condition with SLA+R
	x = (((int)I2C_Read_Ack() << 8) | (int)I2C_Read_Ack());
	y = (((int)I2C_Read_Ack() << 8) | (int)I2C_Read_Ack());
	z = (((int)I2C_Read_Ack() << 8) | (int)I2C_Read_Ack());
	I2C_Stop();
	Heading = atan2((double)y, (double)x) + declination;
	if (Heading > 2*PI) // Due to Declination, check for > 360 degrees
		Heading = Heading - 2*PI;
	if (Heading < 0) // Check For Sign
		Heading = Heading + 2*PI;
	return (Heading*180/PI);
}


int main(void)
{
    /*char buffer[10];
	I2C_Init();
	Magneto_init();
	
	splashscreen();*/
	// Set Up LED with Switch
    while (1) 
    {
		
		DDRA = (1 << LED); // Configure PORTA as output to connect LEDs
		DDRC = (0 << SWITCH); // Configure PORTC as Input to connect switch
		PORTC = (1 << SWITCH); // Enable the Pullups of PORTC
		/* Replace with your application code */
		while (1)
		{
			
			while (((PINC) & (1 << SWITCH)) == 1) // Check the Status of the Switch
			{
				PORTA |= (1 << LED);
				printf("Hello");
			}
			PORTA &= ~(1 << LED);
		}
		
		return 0;
    }
}