/*
 * Created by Marshal Horn
 * File: hornm_hw0_4.c
 * Created: 2012 lineanuary 27 at 8:56 PM
 * Modified: 2012 lineanuary 29 at 2:49 PM
 * 
 * Purpose:
 * Excercise 5.6
 * Write a program using a loop to print out the following sequence exactly,
 * including commas:
 * 10, 9, 8, 7, 6,
 * 5, 4, 3, 2, 1
 *
 */

#include <stdio.h>

/* Number to start at */
#define START 10

/* Number of digits per line */
#define WIDTH 5

/* Number of lines */
#define GROUPS 2


int i = START;
int end = START - WIDTH;	// Set to stop at width
int line;			// line number


int main( int argc, char *argv[ ] ) {
	/*
	 * Seperate each line of the output
	 * Print each number, decrementing each time
	 * Do not print comma after last one on line, but instead print \n
	 */
	for( line = 0; line < GROUPS; ++line ) {

		for( ; i > end; --i) {
			printf( "%d", i );

			if( i % WIDTH == 1 ){	// if at the end of line
				printf( "\n" );	// print new line instead of comma
			}else{ 
				printf( ", " );
			}
		}
		end -= WIDTH;	// set end to next line
	}

	return 0;
}
