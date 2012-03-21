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

#include "morse_code.h"



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
