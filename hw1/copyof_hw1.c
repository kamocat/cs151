/*
 * Original Author: Marshal Horn
 * File: hornm_hw1.c
 * Created: 2012 Feb 16 at 6:56 PM
 * Modified: 2012 Feb 16 at 6:56 PM
 *
 * Excercises:
 * (1)	10.7
 * (2)	10.10
 * (3)	10.30
 * (4)	10.33 (EC)
 * (5)	11.6
 * (6)	11.7
 *
 * (7)	Write a program which uses pointers and arrays to perform matrix
 * multiplication.
 *
 * (8)	Sieve or Eratosthenes
 * (EC is using command-line argument for this)
 *
 * (9)	Write a function that concatenates the string s2 to the end of 
 * string s1 using pointers.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define LAST_EXCERCISE 9

int chooser_core( int argc, char **argv, int argi, int function ) {
	/*
	 * Dummy for chooser core.
	 * If we just return argi without incrementing, it means
	 * the selected function did not take any values.
	 */
	return argi;
}

void tell_useage( char *argument ) {
	printf("The argument %s is invalid.\n", argument );
	printf("The options are: ... \n" );
}


int decode_argument( char *string ) {
	int return_value;
	int arg = atoi( string );
	if( ( string[0] == '-' ) && ( arg <= LAST_EXCERCISE ) ) {
			return_value = arg;
	} else {
			return_value = 0;
	}
	return return_value;
}

void program_chooser( int argc, char **argv ) {
	int argi = 1;	// This is the current argument index

	/* 
	 * This is the task to be performed.  If it is zero, then
	 * the task is invalid.
	 */
	int task;

	/* While there are still arguments left */
	while( argi < argc ) {
		task = decode_argument( argv[argi] );

		if( task ) {
			++argi;
			/* pass arguments on to chooser_core */
			argi = chooser_core( argc, argv, argi, task );

		} else {	// If the task is invalid
			/* instruct user on useage */
			char *tmp = argv[argi];
			tell_useage( tmp );
			/* Increment argument index afterwards */
			++argi;
		}
	}
}



int main( int argc, char **argv ) {
	program_chooser( argc, argv );

	return 0;
}



