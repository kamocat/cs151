/*
 * Created by Marshal Horn
 * File: hornm_hw0_7.c
 * Created: 2012 January 28 at 8:33 PM
 * Modified: 2012 January 29 at 8:53 PM
 *
 * Purpose:
 * Excercise 5.19 for ECE 151
 * Write a program to read an integer number between 0 and 255.  Print out the
 * character corresponding to the input number of the ASCII value as shown in
 * Appendix D.  Give an error message if the input number is outside the
 * specified range.  The program terminates when the input number is -1.  Write
 * a pseudocode and draw the flowchart for the program first.
 */

#include <stdio.h>

int input = 0;		// The initial input by the user
char character = 0;	// The input once typecasted to a char
#define QUIT -1		// Quit if input == -1

/*
 * Use CHAR_MAX and CHAR_MIN to determine if the input is out of range
 * HOWEVER, if they are already defined, we don't want to re-define them
 * (Anybody in their right mind would define them to these values)
 */
#ifndef CHAR_MAX
#define CHAR_MAX 255
#define CHAR_MIN 0
#endif


int main( int argc, char *argv[ ] ) {

	/* The loop ends when the user enters "-1" */
	while( 1 ) {
		printf( "Please enter an integer between 0 and 255: " );
		scanf( "%d", &input );

		/*
		 * Evaluate input to figure out the next action.
		 * If input == QUIT value, then quit the program.
		 * If input is out of range, ask for a new value
		 * Otherwise (the input is in range), convert it to a character.
		 */
		if( input == QUIT ) {
			break;
		}else if( ( input > CHAR_MAX ) || 
			  ( input < CHAR_MIN ) ) {
			printf( "ERROR: %d is out of range.  ", input );
			continue; // Ask for a new value
		}
		character = input; // cast input to char
		printf( "%c\n", character );
	}
	return 0;
}
