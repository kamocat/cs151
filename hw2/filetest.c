/*
 * Test the fgets to see if it gets consecutive lines
 */
#include <stdio.h>
#include <stdlib.h> // for atoi()

#define MAX_STRING_LENGTH 100

int main( int argc, char **argv ) {
	if( argc >= 2 ) {
		char string[MAX_STRING_LENGTH];
		char readonly = 'r';
		FILE *file = fopen( argv[1], &readonly );
		int lines = atoi( argv[2] );
		if( file != NULL ) {
			printf("Printing first %d lines from %s\n",
					lines, argv[1] );
			for( int i = 0; i < lines; ++i ) {
				fgets( string, MAX_STRING_LENGTH, file );
				printf("%s", string );
			}
		} else {
			printf("The file %s was not found\n", argv[1] );
		}
	} else {
		printf("This command prints the first n lines from a file\n");
		printf("Useage: test_fgets file n\n" );
	}
	return 0;
}
