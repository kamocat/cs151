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

	/* run the interactive prompt */
	command_chooser( &head );

	return 0;
}

