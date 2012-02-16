/* Marshal Horn		ECE 151 Lab	lection 10 */

#include <stdio.h> /** Include the stdio.h file to allow for printf() to be used*/
/** @brief Main Function @param void This function does not accept any input variables
 * @return This function would return an error code to the OS if needed.
 * */

double input = 29.87; /** 'input’ will hold the amount of money */ 

#define BILLS 8
double bills[BILLS] = {
	20.00, /* $20 */
	10.00, /* $10 */
	5.00,  /* $5  */
	1.00,  /* $1  */
	.25,   /* $0.25 */
	.10,   /* $0.10 */
	.05,   /* $0.05 */
	.01    /* $0.01 */
};
/* sub-routine to determine change and print to screen */
void get_change (double money) {
	char change = 0; /* This variable stores change for
				   * current bill or coin
				   */
	int i = 0;
	while (i<BILLS) {
		change = (char)(money / bills[i]);
		money -= change * bills[i];
		printf("%d - $%.2lf\n", change, (double)bills[i]);
		i++; /* increment the loop count */
	}
}

int main(void) {
	printf("Input: $");
	scanf("%lf", &input);
	printf("Output:\n");
	get_change(input);
	return (0);
}
		
