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
#include <avr/interrupt.h>

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
 * Decode morse code
 */
void decode_morse_code( void ) {
	unsigned char ltime = 0;
	unsigned char subcounter = 0;
	char state = 0;
	char length = 0;
	char morse = 0;
	char beep = 0; // This holds if the beep was a dit, a dah, or neither 

	unsigned char dit = 4;
	unsigned char dah = 20;
	unsigned char pause = 48;

	char red = 0;
	char green = 0;


	while( 1 ) {

		/* Update state */
		state <<= 1;
		state &= 0x03;
		state |= (PINA & 0x01 );
		// display_row( state, 0, 0 );

		/* Update time */
		++subcounter;
		if( ( subcounter > 10 ) && ( ltime < 255 ) ) {
			++ltime;
			subcounter = 0;
		}
		// display_row( 0 , ltime, 1 );

		/* Update display */
		/* red = ( 1 << length ) - 1;
		 * green = morse;
		 */
		display_row( red, green, 7 );

		/* Choose an action */
		switch( state ) {
			case 1: // button was pressed
				/* Rising or falling edge; reset timer */
				ltime = 0;
				break;

			case 3: // button is held
				if( ltime > dah ) {
					beep |= 0x02;
					display_row( 0x3e, 0x3e, 6 );
				} else if ( ltime > dit ) {
					beep |= 0x01;
					display_row( 0x0e, 0, 6 );
				}
				break;


			case 2: // button is released
				ltime = 0;

				if( beep > 0 ) {
					++length;
					morse <<= 1;
					
					/* if it was a dah, we need to set the code bit true */
					morse += ( beep > 1) ? 1 : 0;
					beep = 0;
				}

				break;

			case 0: // Button remains off

				if( ( ltime > pause ) && ( length != 0 ) ) {
					/*
					 * Character is complete.  Write to output and reset code.
					 */
					
					red = ( 1 << length ) - 1;
					green = morse;

					length = 0;
					morse = 0;
					display_row( 0x00, 0xff, 6);
				}
				break;

			default:
				break;
		}
	}
}




/** Main Function */

int main (void) {
	/** Local Varibles */
	
	initialize();
	clearArray();
	
	decode_morse_code();

	return 0;

}//main
