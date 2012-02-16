/*
 * Original Author: Marshal Horn
 * File: lab4_2.c
 * Created: February 15th 2012 at 2:23 PM
 * Last modified: February 15th 2012 at 2:23 PM
 * 
 * Purpose:
 * Propmt the user to enter a number between 1 and 20.  If their number is
 * not in this range, print an error message and exit the program with
 * either return -1; or exit (-1);
 *
 * If their number is in the correct ranger, use a for loop to print out
 * from 1 up to and including their number.  All the numbers should be
 * on one line with a space between.  Then print a new line.
 *
 * Then using another for loop print the numbers from their number down
 * to 1 all on one line with a space between.
 *
 */

#include <stdio.h>
#include <stdlib.h> // for exit()


#define MIN 1
#define MAX 20
#define ERROR -1

/*
 * Check if the input is valid
 */
char is_number_valid ( int number ) {
	return (( number <= MAX ) && ( number >= MIN ) );
}

/*
 * Ask for input from user
 */
int get_input ( ) {
	printf( "Please enter a number between 1 and 20: " );
	int input;
	scanf("%d", &input );
	if( is_number_valid( input ) ) {
		return input;
	} else {
		/* Print an error message */
		printf("ERROR: input is not between %d and %d.\n", MIN, MAX );
		/* Quit the program entirely */
		exit( ERROR );
	}
}

/*
 * This function counts up from the start to the end.
 * It assumes the start is less than the end.
 */
void count_up( int start, int end ) {
	for( int i = start; i <= end; ++i ) {
		printf("%d ", i );
	}
	printf("\n");
}


/*
 * This function counts down from the start to the end.
 * It assumes the start is greater than the end.
 */
void count_down( int start, int end ) {
	for( int i = start; i >= end; --i ) {
		printf("%d ", i );
	}
	printf("\n");
}


int main( int argc, char **argv ) {
	int input = get_input();
	count_up( MIN, input );
	count_down( input, MIN );
	return 0;
}
	
