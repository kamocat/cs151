/*
 * Created by Marshal Horn
 * File: hornm_hw0_1.c
 * Created 2012 January 25 at 3:24pm
 * Modified 2012 January 29 at 12:05pm
 *
 * Purpose:
 * Excerciese 3.7
 * Write a program to print out the results of integral and floating-point expressions.
 */

#include <stdio.h>

// This is where the integer numbering begins
#define INT_START 'a'

/*
 * This is the length of an integer (in bytes)
 * It is used for determining the length of the array
 */
#define INT_SIZE 4

/* This array is the list of integer operations */
int integral[ ] = {
	2 * 3,
	1 / 5,
	1 / 2,
	3 / 2,
	1 / 3,
	2 / 3
};

// Where the floating-point numbering begins
#define DBL_START 'g'

/* 
 * Size of a double in bytes.
 * Used for calculating the length of the array
 */
#define DBL_SIZE 8

// This array is the list of floating-point division
double division[] = {
	1.0 / 5,
	1.0 / 2,
	3.0 / 2,
	1.0 / 3,
	2.0 / 3,
	1 / 5.0,
	1 / 2.0,
	3 / 2.0,
	1 / 3.0,
	2 / 3.0
};

int i; // iteration counter


int main( int argc, char *argv[ ] ) {
	
	/* 
	 * Iterate through the list of itegers, labelling the results with sequential
	 * letters. Use the sizeof() function to determine the length of the array.
	 */
	for( i = 0; 
	     i < ( sizeof(integral) / INT_SIZE ); 
	     ++i ) {
		 char letter = (char)( i + INT_START );
		 printf( "(%c) %d\n", letter, integral[i] );
	}
	
	/*
	 * Iterate through the list of floating-points, labelling the results with
	 * sequential letters (starting after the previous array).  Use the sizeof()
	 * function to determine the length of the array.
	 */
	for( i = 0; 
	     i < ( sizeof(division) / DBL_SIZE );
	     ++i ) {
		char letter = (char)( i + DBL_START );
		printf( "(%c) %.6f,\t%.20f\n", letter, division[i], division[i] );
	}

	return 0;
}
