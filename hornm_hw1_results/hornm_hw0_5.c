/* 
 * Created by Marshal Horn
 * File: hornm_hw0_5.c
 * Created: 2012 January 27 at 11:30 PM
 * Modified: 2012 January 29 at 5:03 PM
 *
 * Purpose:
 * Excercise 5.6
 * It is important to write an effecient program with a correct algorithm.
 * Write a program using a loop to add integers from 1 to n with n equal to 
 * 1000.  Cerify the result using the formula n(n+1)/2 for the sum from 1 
 * to n, which is more effecient than using a loop.
 *
 */

#include <stdio.h>

/* This is the number of consecutive integers to sum */
#define N 1000

int i;
long long sum = 0;
long long verify;	// stores answer of verified algorithm


int main(int argc, char *argv[]) {
	/*
	 * Start at 1, and count up through N, adding each integer
	 * to the previous value
	 */
	for(i = 1; i<=N; ++i) {
		sum += i;
	}
	
	/*
	 * Make sure that the summation worked properly
	 * This algorithm is a shortcut to the summation of consecitive integers.
	 * If the empirical answer matches this, then it is most likely correct.
	 */
	verify = N*(N+1)/2;
	
	/*
	 * Give indication of whether the summation is correct.
	 * If it correct, say so.
	 * If it is not, provide the the emperical summation (sum) along with
	 * the verification sum (verify)
	 */
	if(verify == sum) {
		printf("Program is correct. The ");
	}else{
		printf("Program is incorrect.\n");
		printf("Calculated sum is %lld, but the ", sum);
	}
	printf("sum of all integers from 1 to %d is %lld\n", N, verify);

	return 0;
}
