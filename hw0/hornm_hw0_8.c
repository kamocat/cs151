/*
 * Created by: Marshal Horn
 * Filename: hornm_hw0_8.c
 * Created: 2012 January 29th, 1:28 AM
 * Modified: 2012 January 29th, 1:28 AM
 *
 * Purpose:
 * This program demonstrates an iterative method of approximating pi (by alternating 
 * between adding and subtracting reciprocals of consecutive odd positive integers).
 * It outputs a table of inputs (iterations) and the calculated value of pi at that
 * iteration.  The inputs are listed in an array, for easy modification.
 */

#include <stdio.h>

/*
 * These are the points where the value of pi is displayed.
 */
long long test_points [] = {
	10,
	20,
	30,
	40,
	50,
	60,
	70,
	80,
	90,
	100,
	10000
};

double pi = 0;	// approximation of pi
long long i = 0;	// iteration counter
int k = 0;	// index of next test point
long long max;	// maximum index


int main(int argc, char *argv[]) {
	printf("This program approximates pi using an iterative method.\n");
	printf("Iteration\tApproximate value of pi\n");
	
	/*
	 * Get the last element in the array.
	 * This is important because this is how high the loop must iterate to.
	 * If we define this as a seperate number, we are asking for errors.
	 */
	max = 2 * ( test_points[ sizeof(test_points) 
		/ sizeof( long long ) - 1 ] ) + 1;

	/*
	 * This loop calculates pi by using the summation (4 - 4/3 + 4/5 - 4/7 ...)
	 * which can be represented as the sum of ((-1)^i)/(2i + 1).
	 * This is simplified by iterating i through the odd numbers, and subtracting
	 * the previous value from the new term each time, instead of alternating between
	 * adding and subtracting.  However, this requires an absolute value function
	 * before the final result.  
	 */
	k = 0;
	for(i = 0; i <= max; ++i) {
		pi = 4.0/(i*2+1) - pi;
		if(i == test_points[k]) {
			pi = +pi; // take absolue value
			printf("%lld,\t\t%.20f\n", test_points[k], pi);
			++k;
		}
	}


	return 0;
}
