/*
 *
 * Original Author: Marshal Horn
 * File: lab4_3.c
 * Created: Feb 15 2012 at 3:42 PM
 * Modified: Feb 15 2012 at 3:43 PM
 *
 * Purpose:
 * Prompt the user to enter two integers.  These numbers should be saved in
 * int variables.  Let's call these numbers a and b.
 * If be is larger than a, then swap them.
 * Print out the result of the division of a by b.
 * Print out the result of a mod b.
 * Create 2 bould variables a_double and b_double and assing a_double = a;
 * and b_double = b;
 * Print out the result of dividing a_double by b_double.  Match the output
 * below:
 *
 * ./division
 *
 * Enter an integer: 7
 * Enter a second integer: 37
 * 37 / 7 = 5
 * 37 % 7 = 2
 * 37.000000 / 7.000000 = 5.285174
 *
 */

#include <stdio.h>



/*
 * This function swaps two integers.
 * It takes pointers to integers (so it can access the values from whatever
 * scope is calling the swap function)
 */
void swap( int *first, int *second ) {
	#ifdef DEBUG
		printf("Before: %d and %d\n", *first, *second );
	#endif
	int tmp = *first;
	*first = *second;
	*second = tmp;
	
	#ifdef DEBUG
		printf("After: %d and %d\n", *first, *second );
	#endif
	return;
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
 * This function orders two integers so that the greater one is first.
 * It will manipulate the values referenced by the pointers passed in.
 */
void greatest_first ( int *first, int *second ) {
	if( *second > *first ) {
		swap( first, second );
	}
}

/*
 * This function prints the math required for this assignment.
 * It consists of integer division, modulus, and double division.
 */
void print_math ( int a, int b ) {
	printf("%d / %d = %d\n", a, b, (a/b) );		// integer division
	printf("%d %% %d = %d\n", a, b, (a%b) );		// modulus
	
	/* floating-point division */
	double a_double = a;
	double b_double = b;
	printf("%.6f / %.6f = %.6f\n", a_double, b_double,
			( a_double / b_double ) );

}


int main( int argc, char **argv ) {
	int a;
	int b;
	get_inputs( &a, &b );
	greatest_first( &a, &b );
	print_math( a, b );

	/* print a blank line to make output look nicer */
	printf("\n");

	return 0;
}

