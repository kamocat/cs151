/**
 * Author: Marshal Horn
 * Adapted from code of lab6
 *
 * File: morse_code.h
 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "char_lookup.h"

#ifndef HORNM_MORSE_CODE
#define HORNM_MORSE_CODE
/** Constants */
#define F_CPU 1000000U

/** Global Variables */

/** Functions */


/** The initialize() function initializes all of the Data Direction 
 * Registers for the Wunderboard. Before making changes to DDRx registers, 
 * ensure that you have read the peripherals section of the Wunderboard 
 * user guide.*/
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
	PORTB |= (1 << PB6) | (1 << PB7);		// Enable latches
	PORTC = 0x00;	// clear the display
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
 * This function prints an ASCII character on the display, starting
 * at 'column'.  (For the whole character to be displayed, column should
 * be between 0 and 5).
 * If the column is outside this range, part or all of the character may
 * be clipped.  This may be useful for scrolling.
 */
void print_ascii( char character, signed char column ) {
	if( ( character <= 'Z' ) && ( character >= 'A' ) ) {
		character -= 'A';
		for( int i = 0; i < 3; ++i ) {
			if( ( column >= 0 ) && ( column <= 7 ) ) {
				display_row( 0, raster[(int)character][i], column );
			}
			++column;
		}
	}
}



/*
 * This function translates the morse code into an ASCII character
 * so we know what symbol we need to display.
 * Because this computer works in binary, not trinary, it requires two
 * bytes: one for the code sequence, and one for the length of that
 * sequence.  In order to make sure the character is found, we mask
 * the code to the length given.
 */
char translate_morse( char code, char length ) {
	char character;
	code &= ( 1 << length ) - 1; //mask with length 'length'

	switch( length ){
		case 1:
			character = lookup_1bit[(int)code];
			break;
		case 2:
			character = lookup_2bit[(int)code];
			break;
		case 3:
			character = lookup_3bit[(int)code];
			break;
		case 4:
			character = lookup_4bit[(int)code];
			break;
		default:
			character = '\0';	// non-printable character
			break;
	}
	return character;
}


#endif
