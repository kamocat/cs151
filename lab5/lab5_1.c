/*
 * Original Author: Marshal Horn
 * File: lab5_1.c
 * Created: 2012 Feb 15 at 8:19 PM
 * Last modified: 2012 Feb 15 at 8:25 PM
 *
 * Purpose:
 * For this task, you will be writing and using three functions. The first 
 * counts from 0 to the parameter and prints the numbers out in a single line. 
 * The second function counts down to 0 from the parameter. The last function 
 * should count between the two parameters. If the first number is smaller than 
 * the second number, the function should count up. If the first number is 
 * larger, the function should count down.
 *
 * Once all three functions are written, write a main function that prompts the 
 * user for two positive numbers, then uses the first for the count up and count
 * down functions and both numbers for the count between function. After doing 
 * this once, the program should ask the user if they would like to quit or 
 * re-run the program.
 *
 *
 */


#include <stdio.h>



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
	
/*
 * Get two integers from ther user.
 * They will be saved to the addresses referenced by the pointers passed
 * into the function.
 */
void get_inputs( int *input_1, int *input_2 ) {
	printf("Enter an integer: ");
	scanf("%d", input_1 );
	printf("Enter a second integer: ");
	scanf("%d", input_2 );

}

/*
 * This function counts between the first and second input.
 * If the first input is greater, it counts down.
 * If the first input is less, it counts up.
 */
void count_between( int input1, int input2 ) {
	if( input1 > input2 ) {
		count_down( input1, input2 );
	} else {
		count_up( input1, input2 );
	}
}


/*
 * This function asks the user if the program should quit, ore rerun.
 * If q or n is entered, the program will quit.
 * Otherwise, it will run again.
 */
char quit_or_rerun( ) {
	printf("Rerun the program? \n");
	char c;
	scanf("%c", &c );
	flushall();	// flush the scan buffer
	return !( ( c == 'q' ) || ( c == 'n' ) ||
			( c == 'Q' ) || ( c == 'N' ) );
}



int main( int argc, char **argv ) {
	int input1;
	int input2;
	do{
		get_inputs( &input1, &input2 );
		count_up( 0, input1 );
		count_down( input1, 0 );
		count_between( input1, input2 );
	} while( quit_or_rerun() );

	return 0;
}
