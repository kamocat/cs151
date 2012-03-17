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

	// Troubleshoot the menu
	/* 
	char *command;
	char *arguments;
	char storage[MAX_LINE_LENGTH];
	get_command( &command, &arguments, storage );
	printf("Command: %s\n", command);
	printf("Arguments: %s\n", arguments);
	*/
	

	return 0;
}

