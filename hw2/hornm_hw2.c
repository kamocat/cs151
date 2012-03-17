/*
 * Created by Marshal Horn
 * file: hornm_hw2.c
 *
 * A gradebook application.
 * Details can be found at http://web.engr.oregonstate.edu/
 * cgi-bin/cgiwrap/dmcgrath/classes/12W/cs151/index.cgi?hw=2 
 *
 * This file just contains main.c - all the subfunctions are included
 * in gradebook.h
 *
 *
 */
#include "gradebook.h"

int main( int argc, char **argv ) {
	struct node *head = NULL;

	/* run the interactive prompt */
	command_chooser( &head );

	return 0;
}

