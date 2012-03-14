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
	enter_new( &head );
	print_student( head );
	release_student( head );


	return 0;
}

