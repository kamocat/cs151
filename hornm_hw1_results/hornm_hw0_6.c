/* ECE 151
 * Created by Marshal Horn
 * File: hornm_hw0_6.c
 * Created: 2012 January 26 at 5:03 PM
 * Modified: 2012 January 29 at 5:17 PM
 *
 * Purpose:
 * Excercise 5.11
 * The Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13, ... is defined by the difference
 * operation F(k+2) = F(k+1) + F(k)
 * Write a program to calculate and print out the Fibonacci sequence with the value
 * k read from the terminal input.  Write a pseudocode and draw out the flowchart
 * for the program first.
 *
 * Overview of logic:
 * Read input from command line argument
 * Iterate through fibonacci sequence
 * Stop when index is reached
 * print out values during iteration (with tabs in between),
 * Make a new line after every value. 
 *
 */

#include <stdio.h>
#include <stdlib.h> // for atoi()

/* The number of arguments this program takes */
#define ARGUMENTS 2

/* This is the maximum index of the fibonacci sequence that the program can execute
 * without causing a negative number (meaning a roll-over)
 */
#define MAX 93
int k = 0; // The total number of iterations (chosen by user)


/*
 * This function prints out the fibbonacci sequence up to the desired index,
 * refered to as the "end". Caveat: it prints the first two elements of the
 * fibbonacci sequence, even if the argument is less than 1.  If given indexes
 * 94 or greater, the output will roll over (indicated by it alternating between
 * positive and negative).
 * If your goal is to only receive the final result, not print every value in the
 * sequence up to that point, you can comment out the printf and simply use the
 * value that is returned.
 */
long long fibb( int end ) {
	/*
	 * These values are initialized here as a seed, AKA a starting point.
	 * If they were all initialized to zero, the sum would not increase.
	 */
	long long sum = 1;
	long long previous = 0;		// the previous sum
	long long penultimate = 0;	// the sum before that

	printf( "%lld,\n%lld,\n", previous, sum ); // print the first two values
	end = end - 2; // accomodate for the values that were already printed

	int i = 0;
	for( i = 0; i<end; ++i ) {
		penultimate = previous;
		previous = sum;
		sum = previous + penultimate;
		printf( "%lld,\n", sum );
	}
	return sum;
}

int main( int argc, char *argv[ ] ) {
	/*
	 * First, check if the correct number of arguments are entered.
	 * If it's incorrect, tell the user how to use this program.
	 * Otherwise, proceed on.
	 */
	if( argc != ARGUMENTS ) {
		printf("Useage: %s iterations\n\n", argv[0]);
		return 1;
	}
	k = atoi( argv[1] ); // Get number of iterations from commandl line
	if( k > MAX ) {
		printf( "More than %d iterations will provide poor results, due", MAX);
		printf( " the values generated being\ntoo large for the integer" );
		printf(" type.\nAre you sure you want to continue?\n (y/n) " );

		/*
		 * This value stores the user's option: 'y' or 'n'
		 * It is used to determine whether to continue, should the use happen
		 * to request more values of the fibonacci sequence than the program
		 * can meaningfully produce.  (calculate without rolling over)
		 */
		char choice;

		/*
		 * Since the first character of the scan is always "1", this forces
		 * the program to scan a second time.  (It's a work-around to a
		 * problem I don't have time to troubleshoot right now)
		 */
		scanf( "%c%c", &choice, &choice );	

		/* Only accept valid choices */
		if( ( choice != 'Y' ) && (choice != 'y') ) {
			printf( "Please choose a new integer between 1 and %d: ", MAX );
			scanf( "%d", &k );
		}
	}

	fibb( k ); // Print the fibbonacci sequence up to the index k

	printf( "Done! \n" );

	return 0;
}
