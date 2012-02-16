#include <stdio.h>  /* standard IO library */
#include <unistd.h> /* unix standard library */
#include <stdlib.h> /* standard library */


/* there is no const in C89 */
#define MAGIC 42
/* 
	The only numbers that should ever appear in code are 0 and 1.
	Everything else should be defined as a macro.
*/


/* 
	ALWAYS make main take these arguments.
	This allows it to be called in the terminal.
*/
int main(int argc, char **argc) {
	
	int foo_bar = 0; /* DO NOT use camelCase */
	int foo = 0; /* ALWAYS initialize your variables */
	int bar = 0;

	
	fprintf(stdout, "Hello world!\n");
	
	return 0;
}
