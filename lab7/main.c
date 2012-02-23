/**
@file main.c
@brief Lab 6 Starter Code
@version .01 
@mainpage Lab 6 Starter Code

Modified by Marshal Horn

@section intro Code Overview
 
@section hw Hardware Pin Out
PORTA:
Switches A7 - A0

PORTB:


 
 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>

/** Constants */
#define F_CPU 1000000U

/** Global Variables */

/** Functions */

/** The initialize() function initializes all of the Data Direction Registers for the Wunderboard. Before making changes to DDRx registers, ensure that you have read the peripherals section of the Wunderboard user guide.*/
void initialize (void) {
	/** Port A is the switches and buttons. They should always be inputs. ( 0 = Input and 1 = Output )*/
	DDRA=0b00000000;

	/** Port B has the LED Array color control, SD card, and audio-out on it. Leave DDRB alone. ( 0 = Input and 1 = Output )*/
	DDRB=0b11000000;

	/** Port C is for the 'row' of the LED array. They should always be outputs. ( 0 = Input and 1 = Output )*/
	DDRC=0b11111111;

	/** Port D has the Serial on it. Leave DDRB alone. ( 0 = Input and 1 = Output )*/
	DDRD=0b00000000;

	/** Port E has the LED Array Column control out on it. Leave DDRE alone. ( 0 = Input and 1 = Output )*/
	DDRE=0b00000111;

	/** Port F has the accelerometer and audio-in on it. Leave DDRF alone. ( 0 = Input and 1 = Output )*/
	DDRF=0b00000000;
}

void clearArray(void)
{
	PORTB &= ~((1 << PB6) | (1 << PB7));	// Disable latches
	PORTC = 0x01;
	PORTB |= (1 << PB6) | (1 << PB7);		// Enable latches
	PORTB &= ~((1 << PB6) | (1 << PB7));	// Disable latches
}


void eight_bit_glory( int wait ) {
	char number = 0;
	while( 1 ) {
		if( PINA & 0x10 ) {
			PORTC = ++number;
			_delay_ms( wait );
		}
	}
}


/** Main Function */

int main (void) {
	/** Local Varibles */
	unsigned char temp;
	
	initialize();
	clearArray();
	
	PORTB = 0b11000000;

	eight_bit_glory( 50 );

	return 0;

}//main
