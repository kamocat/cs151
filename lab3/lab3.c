/* Marshal Horn		ECE 151 Lab	Section 10 */

#include <stdio.h> /**	Included to allow for printf() to be used */
#include <time.h> /**	Included to allow time() to be used*/
#include <stdlib.h> /**	Included to allow rand() and srand() to be used*/

#define MIN 0
#define MAX 50
#define TRIES 5

/**	@brief main function
 * 		@param void This function does not accept any input values
 * 		@return This function would return an error to the OS if enabled
 */

int main() {
	// variables declarations
	int x = 0; /** variables to hold our random integer*/
	int guess = MAX + 1; /** variable to hold our user's guess **/

	srand(time(NULL)); /** seeds our random number generator.  Do this jut once */
	printf("Guess a number between %d and %d. \nYou get %d guesses. \nI'll tell if you if it's too high or too low\n", MIN, MAX, TRIES);

	x = rand() % MAX;

	int i; /* This is the iterator for the FOR loop */
	for(i=0; i<TRIES; ++i) {
		printf("Guess my number. ");
		scanf("%d", &guess);

		if(guess == x){
			printf("Perfect guess!\n");
			break;
		}else if((guess > x) && (MAX >= x)){
			printf("%d is too high!\n", guess);
		}else if((guess < x) && (x >= MIN)){
			printf("%d is too low.\n", guess);
		}else {
			printf("%d is not between %d and %d\n", guess, MIN, MAX);
		}
	}
	return 0;

}
