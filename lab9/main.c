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

unsigned char time = 0x00;
ISR( TIMER_OVF_vect ) {
	// if( time < 255 ) {
		++time;
	// }
}

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


	/* Configure timer0 */
	TCCR0A = 0;		// set timer0 to normal mode
	TCCR0B = 0x05;	// Set timer0 prescaler to 64
	TIMSK0 = 0x01;	// enable the overflow interrupt on timer0
	sei(); // enable interrupts
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


void display_number( void ) {
	for( int count = 0; ;  ++count ) {
		for( int repeat = 0; repeat < 200; ++repeat ) {
			for( int i = 0; i < 3; ++i ) {
				display_row( numraster[count%10][2-i] << 3,
						numraster[ (count + 1)%10][2-i], i );
			}
		}
	}
}

/*
 * Decode morse code
 */
void decode_morse_code( void ) {
	unsigned char time = 0;
	unsigned char subcounter = 0;
	char state = 0;
	char length = 0;
	char morse = 0;

	unsigned char dit = 20;
	unsigned char dah = 80;
	unsigned char pause = 100;

	char red = 0;
	char green = 0;


	while( 1 ) {

		/* Update state */
		state <<= 1;
		state &= 0x03;
		state |= (PINA & 0x01 );
		display_row( state, 0, 0 );

		/* Update time */
		++subcounter;
		if( ( subcounter > 50 ) && ( time < 255 ) ) {
			++time;
			subcounter = 0;
		}
		display_row( 0 , time, 1 );

		/* Update display */
		red = ( 1 << time ) - 1;
		green = morse;
		display_row( red, green, 5 );

		/* Choose an action */
		switch( state ) {
			case 3: // button is held
				if( time > dit ) {
					/* Set bit as dit, not dah */
					morse |= 0x01;
				} else if ( time > dah ) {
					/* 
					 * Add a new bit to the code.  For each bit, OFF is dit and 
					 * ON is dah.  So, the default is dit.
					 */
					++length;
					morse <<= 1;
				}
				break;

			case 1: // button was pressed
				/* Rising or falling edge; reset timer */
				// time = 0;
				display_row( 0xff, 0, 6 );
				_delay_ms( 50 );
				break;


			case 2: // button is released
				/* Rising or falling edge; reset timer */
				// time = 0;
				display_row( 0, 0xff, 7 );
				_delay_ms( 50 );
				break;

			case 0: // Button remains off
				if( ( time > pause ) && ( length != 0 ) ) {
					/*
					 * Character is complete.  Write to output and reset code.
					 */
					
					red = ( 1 << length ) - 1;
					green = morse;

					length = 0;
					morse = 0;
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
