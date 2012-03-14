/**
@file main.c
@brief Lab 6 Starter Code
@version .01 
@mainpage Lab 6 Starter Code

Modified by Marshal Horn

@section intro Code Overview
create an image that is displayed

@section hw Hardware Pin Out
PORTA:
Switches A7 - A0



 
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


/*
 * This function displays a single row of LEDs.
 * If you need to use it to display multiple rows at the same time, it should
 * be placed in a loop so it can cycle through the rows quick enough that
 * the user doesn't notice the flicker.
 */
void display_row( char red, char green, char column ) {
	/* Clear both colors before changing the column */
	PORTC = 0x00;
	PORTB |= 0xc0;
	PORTE = column & 0x07;

	/*
	 * Set the red bits.
	 * Since the red is already enabled, we simply disabled the green
	 * Then we set PORTC.
	 */
	PORTB &= 0x7f;
	PORTC = red;

	/*
	 * Set the green bits.
	 * We disable the red so we don't overwrite what we just did.
	 * Then we set PORTC.
	 * Now we can enable the green without the wrong thing flashing up.
	 */
	PORTB &= 0xbf;
	PORTC = green;
	PORTB |= 0x80;

	/*
	 * Now we wait so the user has time to see the result.
	 */
	_delay_us(100);

}


/*
 * This is a list of numbers, each displayable on a 3x5 raster grid.
 * The first index is the number, from 0 to 9.
 * The second index is the column of the number, from 0 to 2.
 */
char numraster[10][3] = {
	{0x1F, 0x11, 0x1F},
	{0x01, 0x1F, 0x09},
	{0x0D, 0x13, 0x09},
	{0x0E, 0x15, 0x15},
	{0x1F, 0x04, 0x1C},
	{0x17, 0x15, 0x18},
	{0x02, 0x15, 0x0E},
	{0x1C, 0x13, 0x10},
	{0x1F, 0x15, 0x1F},
	{0x1F, 0x14, 0x0C}
};


void display_number( ) {
	for( int count = 0; ;  ++count ) {
		for( int repeat = 0; repeat < 200; ++repeat ) {
			for( int i = 0; i < 3; ++i ) {
				display_row( numraster[count%10][2-i] << 3,
						numraster[ (count + 1)%10][2-i], i );
			}
		}
	}
}



/** Main Function */

int main (void) {
	/** Local Varibles */
	
	initialize();
	clearArray();
	
	display_number();

	return 0;

}//main
