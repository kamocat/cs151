/*
 * Created by Marshal Horn
 * File: lab4_1.c
 * Created 2012 Feb 2nd at 8:28 AM
 * Modifed 2012 Feb 2nd at 8:28 AM
 *
 * Purpose: Lab 4 for ECE 151
 */

#include <stdio.h>
#define TRUE 255
#define FALSE 0
#define ERROR 1

double get_input( void ) {
	double input;
	printf("\nPlease enter a value: ");
	scanf("%lf", &input);
	return input;
}
/*
 * Check if this value matches any of the previous values.
 * Since the values should all be initialized to -1, it should not be an
 * issue that this checks EVERY value (including the one it will eventually
 * be written to).  If it matches a value in the array, it returns TRUE
 * and ends the loop.  If none match, it will return FALSE.
 */
char match_prior ( double value, double array[], int array_length) {
	int i;
	for(i = 0; i < array_length; ++i) {
		/*
		 * Return TRUE if values are equal, and end the loop.
		 */
		if( value == array[i] ) {
			return TRUE;
		}
	}
	/* It will only return false after all the array values are checked */
	return FALSE;
}

/*
 * If the value is invalid, return TRUE
 * It is valid if it is not less than 0
 * and it does not match a previous value.
 */
char input_valid ( double value, double array[], int array_length ) {
	if( ( value < 0 ) ||
		match_prior( value, array, array_length ) ) {
		return FALSE;
	} else {
		return TRUE;
	}
}

void congradulate( double array[], int array_length ) {
	int i;
	/*
	 * Here we decrease the value of array_length by 1
	 * in order to stop the for loop one iteration early,
	 * so the last line can be printed differently.
	 */
	--array_length;
	printf("Congradulations!  You have completed this task.\n");
	for( i = 0; i < array_length; ++i) {
		printf("%f, ", array[i]);
	}
	/*
	 * This last number should be printed with a new line at the
	 * end, not a comma.  Thus, it has to be done seperately from
	 * the loop.
	 */
	printf( "%f\n", array[array_length] );
}

void print_instructions( void ) {

	printf("I am going to ask you to enter 5 different positive floating point numbers.\n");
	printf("I will end the program as soon as you enter a negative value or repeat a number.\n");
	printf("I will congradulate you and print out the 5 numbers if you successfully complete the task.\n");
}

#define F_LENGTH 5
int main(int argc, char *argv[]) {
	/* Store the 5 values here */
	double f[] = {
		-1.0,
		-1.0,
		-1.0,
		-1.0,
		-1.0
	};

	print_instructions(); // print the instructions for using this program.

	int i;
	for(i = 0; i < F_LENGTH; ++i) {
		double new_value = get_input();
		if( input_valid( new_value, f, F_LENGTH ) ) {
			f[i] = new_value; 	// write a new value to the array
		} else {
			return ERROR; 		// This ends the program with an error
		}
	}
	/*
	 * If the program got this far, this means all of the values are valid.
	 * Congradulate the user, and print all 5 values.
	 */
	congradulate( f, F_LENGTH );


	return 0;
}
