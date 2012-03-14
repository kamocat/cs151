/*
 * Created by Marshal Horn
 * File: hornm_hw0_2.c
 * Created: 2012 January 27 at 6:00 PM
 * Modified: 2012 January 29 at 2:45 PM
 *
 * Purpose:
 * Excercise 3.10
 *
 * Write a program that prints the number 1 to 4 on the same line.
 * Write the program using the following methods:
 * 	a) Calling the function printf() once with four format specifiers
 * 	b) Calling the function printf() four times
 */

#include <stdio.h>


#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4

int main(int argc, char *argv[]) {
	
	/*
	 * Print ONE, TWO, THREE, and FOUR using a single printf
	 */
	printf("%d, %d, %d, %d\n", ONE, TWO, THREE, FOUR);

	/*
	 * Print ONE, TWO, THREE, and FOUR using a printf for each
	 */	
	printf("%d, ", ONE);
	printf("%d, ", TWO);
	printf("%d, ", THREE);
	printf("%d\n", FOUR);

	return 0;
}
