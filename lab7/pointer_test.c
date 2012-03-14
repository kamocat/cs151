/*
 * Marshal Horn
 * Pointer test
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
	long long int *x;
	printf("The address of x is %lld\n", (long long int)x );
	
	/* 
	 * Here we need to allocate the space before we can print it.
	 * Otherwise, we get a segmentation fault.
	 */
	x = malloc( sizeof( long long int ) );
	printf("The value at x is %lld\n", *x );
	printf("Now the address of x is %lld\n", (long long int)x );

	return 0;
}

