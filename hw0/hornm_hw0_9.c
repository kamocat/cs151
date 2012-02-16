/*
 * Original Author: Marshal Horn (hornm@engr.orst.edu)
 * File: hornm_hw0_9.c
 * Created: 2012 January 29th, 2012, 12:05 AM by hornm
 * Last Modified: 2012 January 29th 2012, 12:06 AM by hornm
 * 
 * Purpose:
 * Print values from 1 to 25, with their square roots and cube roots.
 * The output should consist of 25 lines, with values on a line seperated by tabs.
 * You will want to make use of the pow() function for this.  The number in the first
 * column should be an integer, while the other columns should be doubles.
 *
 */

#include <stdio.h>
#include <math.h> 	// for pow()

int i;			// value that iterates through loop
double square_root;	// square root of value
double cube_root;	// cube root of value

// used for calculating square root
#define HALF 0.5

// used for calculating cube root
#define THIRD (1.0/3.0) 

// the maximum value of i
#define END 25


int main(int argc, char *argv[] ){
	for(i = 1; i <= END; ++i) {
		square_root = pow(i, HALF);	// compute square root
		cube_root = pow(i, THIRD);	// compute cube root

		/*
		 * Print i, the square root, and the cube root to the screen.
		 * Seperate with tabs.
		 */
		printf("%d\t%f\t%f\n", i, square_root, cube_root);
	}

	return 0;
}
