/*
 * Created by Marshal Horn
 * file: hornm_hw2.c
 *
 * This file just contains main.c - all the subfunctions are included
 * in the headers.
 */
#include "gradebook.h"

int main( int argc, char **argv ) {
	struct node *head = NULL;
	int n = 3;
	if( argc > 1 ) {
		n = atoi(argv[1]);
	}

	for( int i = 0; i < n; ++i ) {
		enter_new( &head );
	}

	print_list( head, -1 );
	close_gradebook( &head );

	return 0;
}

