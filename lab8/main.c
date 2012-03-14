/**
@file main.c
@brief Lab 8 Starter Code
@version .01 
@mainpage Lab 8 Starter Code

@section intro Code Overview
 
@section hw Hardware Pin Out
Port A:
A0 - A3 : Push Buttons
A4 - A7 : Slide Switches 

Port B:
B0 - B3 : SPI (SD Card)
B4		: Nothing
B5		: Audio Out
B6 		: Red Enable 
B7 		: Green Enable

Port C:
C0 - C7 : LED Array (Row)

Port D:
D0 - D1 : Nothing
D2		: Serial RX
D3		: Serial TX
D4 - D7	: Nothing

Port E:
E0 - E2 : LED Array (Column)
E3		: USB (UID)
E4 - E5	: Nothing
E6		: Relay
E7		: Nothing

Port F:
F0 		: ADC Channel 0
F1 		: ADC Channel 1
F2 		: ADC Channel 2
F3 		: ADC Channel 3
F4		: ADC Channel 4 (Audio In)
F5 		: ADC Channel 5 (Accel X Axis)
F6 		: ADC Channel 6 (Accel Y Axis)
F7 		: ADC Channel 7 (Accel Z Axis (if installed))

 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // for rand()
#include "adc.h"

/** Constants */
#define F_CPU 1000000U
#define X_AXIS 5
#define Y_AXIS 6
#define Z_AXIS 7
#define GREEN 0x80
#define RED 0x40
#define AMBER 0xc0

/** Global Variables */

/** Functions */

/** The initialize() function initializes all of the Data Direction Registers for the Wunderboard. Before making changes to DDRx registers, ensure that you have read the peripherals section of the Wunderboard user guide.*/
void initialize (void) {
	/** Port A is the switches and buttons. They should always be inputs. 
	 * ( 0 = Input and 1 = Output )*/
	DDRA=0b00000000;

	/** Port B has the LED Array color control, SD card, and audio-out on it. 
	 * Leave DDRB alone. ( 0 = Input and 1 = Output )*/
	DDRB=0b11000000;

	/** Port C is for the 'row' of the LED array. They should always be outputs.
	 * ( 0 = Input and 1 = Output )*/
	DDRC=0b11111111;

	/** Port D has the Serial on it. Leave DDRB alone. 
	 * ( 0 = Input and 1 = Output )*/
	DDRD=0b00000000;

	/** Port E has the LED Array Column control out on it. Leave DDRE alone. 
	 * ( 0 = Input and 1 = Output )*/
	DDRE=0b00000111;

	/** Port F has the accelerometer and audio-in on it. Leave DDRF alone. 
	 * ( 0 = Input and 1 = Output )*/
	DDRF=0b00000000;
}

void clear_display(void)
{
	// PORTB &= ~((1 << PB6) | (1 << PB7));	// Disable latches
	PORTC = 0x00;
	PORTB |= RED | GREEN;
	// PORTB &= ~((1 << PB6) | (1 << PB7));	// Disable latches
}


void warning() {
	for( int i = 0; i < 5; ++i ){
		PORTB = RED;
		PORTC = 0xa5;
		_delay_ms(120);
		clear_display();
		_delay_ms(60);
	}
}

void init_accel( char *x, char *y, char *z ) {
	*x = read_adc( X_AXIS );
	*y = read_adc( Y_AXIS );
	*z = read_adc( Z_AXIS );
}


/*
 * This function takes very specific values for x, y, and color.
 * The x and y can range from 0 to 7.
 * The color can be 0x40 (RED), 0x80 (GREEN), or 0xc0 (AMBER)
 * This function doesn't check for valid values, but just uses bit-masking
 * to take care of it.
 */
void display_dot( char x, char y, char color ) {
	clear_display();
	color &= AMBER;		// mask color
	PORTB &= ~color;	// turn off the colors we don't want.
	char dot = 1 << y;
	PORTE = x & 0x07;	// mask column
	PORTC = dot;

}


unsigned char scale_for_graph( unsigned char input ) {
	input = ((input >> 1) - 4) & 7;
	return input;
}


/** Main Function */

int main (void) {
	/** Local Varibles */
	
	initialize();
	clear_display();
	char x_center;
	char y_center;
	char z_center;
	init_accel( &x_center, &y_center, &z_center );

	while( 1 ) {
		unsigned char x_target = random() % 8;
		unsigned char y_target = random() % 8;
		unsigned char x_axis;
		unsigned char y_axis;
		
		do {
			x_axis = read_adc(X_AXIS) - x_center;
			y_axis = read_adc(Y_AXIS) - y_center;

			x_axis = scale_for_graph( x_axis );
			y_axis = scale_for_graph( y_axis );

			display_dot( x_axis, y_axis, GREEN );
			_delay_ms( 1 );
			display_dot( x_target, y_target, RED );
			_delay_ms( 1 );
		} while( (x_axis != x_target) || (y_axis != y_target) );

		display_dot( x_target, y_target, AMBER);
		_delay_ms( 100 );

	}
	return 0;

}//main
