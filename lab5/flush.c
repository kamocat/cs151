/*
 * Created by Marshal Horn
 * File: flush.c
 * Created: 2012 Febrary 15 at 11:07 PM
 * Modified: 2012 February 15 at 11:30 PM
 *
 *
 * Purpose:
 * Use getchar()
 *
 * In main, create a loop that:
 * 		Prompts the user for input
 * 		Prints out the first character the user typed, as well as its ASCII code
 * 		Repeat until the user enters a "special" character.
 * 		(What counts as special is entirely up to you)
 *
 */

#include <stdio.h>

/*
 * This is the character the user must enter to end the program.
 * Effectively, it means they just press enter, and nothing else.
 */
#define EXIT '\n'



/*
 * This function flushes the buffer used by getchar()
 */
void flush() {
	char d;
	do {
		d = getchar();
	} while( d != '\n' );
	return;
}

/*
 * Get input from the user, using getchar()
 * Then flush the buffer
 */
char get_input() {
	printf("Please enter a character, and then hit enter: ");
	char c = getchar();
	/* If there are other values, flush them */
	if( c != '\n' ) {
		flush();
	}
	return c;
}
	
/*
 * This function prints a character, as well as its ASCII code (in decimal)
 */
void print_char( char c ) {
	printf("%c = ASCII %d\n", c, c );
}


int main( int argc, char **argv ) {
	char end = 0;
	while( !end ) {
		char c = get_input();
		if( c == EXIT ) {
			end = 1;	// exit the program
		} else {
			print_char( c );
		}
	}
	return 0;
}



