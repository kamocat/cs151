
/*
 * Author: Marshal Horn
 *
 *
 * This is a description of how the gradebook will work.
 * Each function is described in the comments, with pseudocode,
 * and the function prototype is immidiately below.
 *
 * The exception is mean, median, and std_dev, whose functions are
 * written as regular c code.
 *
 * The datatypes are copied from an example file of Kevin McGrath
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>	// for tolower()


#ifndef HORNM_GRADEBOOK_FOR_CS151
#define HORNM_GRADEBOOK_FOR_CS151


#define MAX_STRING_LENGTH 100
#define MAX_NUM_ASSIGNMENTS 30
#define MAX_LINE_LENGTH (MAX_STRING_LENGTH * ( 1 + MAX_NUM_ASSIGNMENTS ) )

/* ERROR codes */
#define FILE_NOT_FOUND -404
#define STUDENT_NOT_FOUND -304
#define ASSIGNMENT_NOT_FOUND -204
#define OVERWRITE_STUDENT -310
#define OVERWRITE_ASSIGNMENT -210
#define BAD_INPUT -9000
#define END_OF_LIST -321

/* Define useage */
#define GRADEBOOK_USEAGE "This gradebook takes input in the form command \
argument.\nThese are the valid commands:\n\
add Last_name,First_name,{,[Assignment,score]*}\n\
\tAdds a student to the list\n\
getn n\n\
\tGets the nth student from the list\n\
get0\n\
\tGets the first student from the list\n\
getend\n\
\tGets the last student from the list\n\
rm\n\
\tDeletes the current student\n\
getf First_name\n\
\tFinds a student by first name\n\
getl Last_name,First_name\n\
\tFinds a student by last name (first name is optional)\n\
ls\n\
\tPrints all the students in the list\n\
import\n\
\tLoads a gradebook from file.  The first line should contain the number\n\
\tof students and the number of grades per student.  Each line after\n\
\tshould contain student data in the same format as when adding them\n\
\tindividually with add.\n\
gradepointer\n\
\tPrints the address of the assignment array of the current student\n\
stat\n\
\tPrints the mean, median, and standard deviation of the current \n\
\tstudents grades.\n\
allstat assignment_name\n\
\tPrints the mean, median, and standard deviation of all students grades\n\
\ton the specified assignment.  If the assignment is not found, that\n\
\tstudents grade is translated as zero.\n\
quit\n\
\tExit the program\n\n"


/*
 * Struct declarations
 */
struct assignment{
	char *name;
	double score;
};

struct node{
	struct node *next;
	struct node *previous;

	char *first_name;
	char *last_name;

	struct assignment *grades;
	long long num_assignments;
};

struct stats{
	double mean;
	double median;
	double stddev;
};

/*
 * Create a new space and copy a string over
 */
int copy_string( char **target, char *source ) {
	int length = strlen( source ) + 1;
	int error = 0;
	if( (source != NULL ) && ( length > 1) ) {
		*target = (char *)malloc( length );
		strcpy( *target, source);
	} else {
		error = BAD_INPUT;
	}
	return error;

}

/*
 * Copy the grades over, so the list is only as long as we need
 */
void copy_grades( struct assignment **copy, struct assignment *source,
		int number_of_grades ) {
	*copy = (struct assignment *)malloc( number_of_grades 
			* sizeof(struct assignment) );

	for( int i = 0; i < number_of_grades; ++i ) {
		*copy[i] = source[i];
	}
}


/*
 * This function frees the malloced space for the student.
 * Use it after the list is stitched back together; this function gets rid
 * of all the data about this student, including what the previous and
 * next students are.  Be careful.
 */
int release_student( struct node *student ) {
	printf("Deleting %s, %s....", 
			student->last_name, student->first_name );
	free( student->first_name );
	free( student->last_name );
	for( int i = 0; i < student->num_assignments; ++i ) {
		free( student->grades[i].name );
	}	
	free( student->grades );
	free( student );

	printf("Done.\n");

	/* 
	 * This is here so I can create error codes later if I want. 
	 */
	return 0;
}
			



/*
 * get assignment grade
 *
 * int error = ASIGNMENT_NOT_FOUND
 * grades = student->assignments
 * for( length of array )
 * 		if( strcmp( grades[i].assignment, assignment) == 0 )
 * 			error = NO_ERROR
 * 			*score = grades[i].score
 * 		else
 * 			++i
 *
 * return error
 *
 */
int get_assignment( struct node *student, char *assignment, double *score ){
	int error = ASSIGNMENT_NOT_FOUND;
	struct assignment *grades = student->grades;
	for( int i = 0; i < (student->num_assignments); ++i ){
		if( strcmp( grades[i].name, assignment) == 0 ){
			error = 0;
			*score = grades[i].score;
			break;
		}
	}

	return error;
}




/*
 * Return first element in list
 */
struct node *get_first( struct node *head ) {
	if( head != NULL ) {
		while( head->previous != NULL ) {
			head = head->previous;
		}
	}
	return head;
}


/*
 * Return length of list
 *
 * start at first element
 * int length = 0
 * while( element_pointer != NULL )
 * 		go to next element
 * 		++length
 * return length
 */
int get_length( struct node *head ) {
	int length = 0;
	while( head != NULL ) {
		head = head->next;
		++length;
	}
	return length;
}

/*
 * Close gradebook and clear list
 */
int close_gradebook( struct node **head ) {
	if( head != NULL ) {
		*head = get_first( *head );
		struct node *next;
		int n = get_length( *head );
		for( int i = 0; i < n; ++i ) {
			next = (*head)->next;
			release_student( *head );
			*head = next;
		}
	}
	return 0;
}
			





/*
 * Return nth element from list
 *
 * int error
 * for( n )
 * 		if( head->next != NULL )
 * 			head = head->next
 * 		else
 * 			error = ELEMENT_NOT_FOUND
 * 			break
 *
 * If there's no error, then we can update the value at element
 * if( !error )
 * 		*element = head
 *
 * return error
 */
int get_nth_element( struct node *head, int n, struct node **element ) {
	int error = 0;
	for( int i = 0; i < n; ++i ) {
		if( (head->next) != NULL ) {
			head = head->next;
		} else {
			error = STUDENT_NOT_FOUND;
			break;
		}
	}
	if( !error ) {
		*element = head;
	}
	return error;
}

/*
 * Return last element in list
 *
 * while( head->next != NULL )
 * 		head = head->next
 *
 * return head
 */
struct node* get_last( struct node *head ) {
	if( head != NULL ) {
		while( (head->next) != NULL ) {
			head = head->next;
		}
	}
	return head;
}



/*
 * Search the list by last name (first name optional)
 *
 * Start with the first element
 * While( next_pointer != NULL )
 * 		int eval = strcmp( last, element->last )
 * 		if( eval > 0 )
 * 			go to next element
 * 		else if ( eval < 0 )
 * 			error = STUDENT_NOT_FOUND
 * 		else if( eval == 0 )
 * 			if( first != NULL )
 * 				// only search for first name if one was passed in
 *	 			eval = strcmp( first, element->first )
 * `			if( eval != 0 )
 * 					go to next element
 *
 * pointer to preceding = element->previous
 *
 * return error
 *
 *
 */
int search_for_element( struct node *start, char *last, char *first,
		struct node **address, struct node **preceding ) {
	/* 
	 * We initialize to END_OF_LIST in case the search goes through the 
	 * whole array without finding the name we're looking for.
	 * If this is the case, we catch it and set preceding to the last
	 * element, and address to NULL.
	 */
	int error = END_OF_LIST;
	*preceding = start == NULL ? NULL : start->previous;

	while( start != NULL ) {
		int eval = strcmp( last, start->last_name );
		if( eval > 0 ) {
			printf("%s was found.  Checking next student.\n",
					start->last_name );
			*preceding = start;
			start = start->next;

		} else if ( eval < 0 ) {
			// Student not found.
			printf("Student was not found.\n");
			error = STUDENT_NOT_FOUND;
			break;

		} else if( eval == 0 ) {
			if( first != NULL ) {

				// only search for first name if one was passed in
	  			eval = strcmp( first, start->first_name );
				if( eval > 0 ){
					start = start->next;
					continue; //skip back to start of loop
				} else if ( eval < 0 ) {
					// Student not found
					error = STUDENT_NOT_FOUND;
					break;
				}
				// ELSE continue to below
			}

			// Match was found
			error = 0;
			break;
		}
	}

	*address = start;

	return error;
}

/*
 * Search by first name
 *
 * Start at top of list
 * error = ELEMENT_NOT_FOUND
 * while( ( first != element->first ) 
 * 			&& ( (*element)->next != NULL ) )
 * 		go to next pointer
 * if( first == (*element)->first )
 * 		error = NO_ERROR
 * return error
 *
 */
int search_for_first_name( struct node *head, char *first,
		struct node **address );





/*
 * Print a single element
 */
void print_student( struct node *element ) {
	printf("Student %s, %s has %lld assignments.\n", element->last_name, 
			element->first_name, element->num_assignments );
}

/*
 * Print the list
 *
 *
 * Start at the element pointed to.
 * for( n )
 * 		print element
 * 		if( first->next != NULL )
 * 			first = first->next
 * 		else
 * 			((no error for trying to print more elements than there are))
 * 			break
 *
 * return start
 */
struct node* print_list( struct node *element, int n ) {
	/*
	 * We use != here intead of < so that the user can pass in -1 if they 
	 * want to print the entire list.
	 */
	printf("\n****Printing gradebook****\n");
	for( int i = 0; i != n; ++i ) {
		print_student( element );
		if( element->next != NULL ) {
			element = element->next;
		} else {
			/* No error for trying to print more elements than exist */
			break;
		}
	}
	return element;
}



/*
 * Calculate mean
 */
double mean( double *array, int length ) {
	double sum;
	for( int i = 0; i < length; ++i ) {
		sum += array[i];
	}
	sum /= length;
	return sum;
}


/*
 * This function is made to work with a sorting function.
 * So, it should return 1 if a is greater, -1 if b is less,
 * or 0 if they are equal.
 */
int cmpdouble( const void *arg1, const void *arg2 ) {
	/* First we must get the values pointed to */
	double a = *(double*)arg1;
	double b = *(double*)arg2;

	/* Now we can calculate the return value */
	int return_value;
	if( a < b ) {
		return_value = -1;
	} else if( a == b ) {
		return_value = 0;
	} else {
		return_value = 1;
	}
	return return_value;
}


/*
 * Calculate median
 *
 * This function sorts the array.  Do not use it where the array must
 * stay unsorted
 */
double median( double *array, int length ) {
	qsort( array, length, sizeof(double), cmpdouble );

	double first = array[ (length - 1 ) / 2 ];
	double second = array[ length / 2 ];
	double median = (first + second) / 2;
	return median;
}


/*
 * Calculate standard deviation
 *
 * To reduce calcualtion time, this function uses a mean passed in.
 */
double std_dev( double *array, int length, double mean ) {
	double sum = 0;
	for( int i = 0; i < length; ++i ) {
		double difference = array[i] - mean;
		sum += difference*difference;
	}
	double variance = sum / length;
	return sqrt(variance);
}
		


/*
 * Stats on assignment
 *
 *
 * length = get_length( head )
 * double *array = malloc( length * sizof(double) )
 * double *score
 *
 * for( length )
 * 		error = get_assignment( head, assigment, score )
 * 		if( error )
 * 			printf("%s, %s does not have a grade for assignment %s.\n",
 * 				last, first, assignment )
 * 			array[i] = 0
 * 		else
 * 			array[i] = score
 *
 * struct stats statistics
 * statistics.mean = mean( array, length )
 * statistics.median = median( array, length )
 * statistics.stddev = std_dev( array, length, statistics.mean )
 *
 * free( array )
 * return statistics
 */
struct stats stats_on_assignment( struct node *head, char *assignment ) {

	int length = get_length( head );
	double *array = (double *)malloc( length * sizeof(double) );
	double *score = 0;
	int error;

	for( int i = 0; i < length; ++i ) {
		error = get_assignment( head, assignment, score );
		if( error ) {
			printf("%s, %s does not have a grade for assignment %s.\n",
				head->last_name, head->first_name, assignment );
			array[i] = 0;
		} else {
			array[i] = *score;
		}
	}

	struct stats statistics;
	statistics.mean = mean( array, length );
	statistics.median = median( array, length );
	statistics.stddev = std_dev( array, length, statistics.mean );

	free( array );
	return statistics;
}
	


/*
 * Stats on person
 *
 *
 * length = student->num_assignments
 * double *array = malloc( length * sizeof(double) )
 *
 * for( length )
 * 		array[i] = student->assignments[i].value
 *
 * struct stats statistics
 * statistics.mean = mean( array, length )
 * statistics.median = median( array, length )
 * statistics.stddev = std_dev( array, length, statistics.mean )
 *
 * free( array )
 * return statistics
 */
struct stats stats_on_individual( struct node *student ){
	int length = student->num_assignments;
	double *array = malloc( length * sizeof(double) );

	for( int i = 0; i < length; ++i ) {
		array[i] = student->grades[i].score;
	}

	struct stats statistics;
	statistics.mean = mean( array, length );
	statistics.median = median( array, length );
	statistics.stddev = std_dev( array, length, statistics.mean );

	free( array );
	return statistics;
}




/*
 * Add a value to the list:
 *
 * malloc the space for the new element
 * fill the element with the data passed in
 * (The grades are already malloced and passed in; the element just
 *  needs to point to them) 
 * Search for the placement of this element
 * 		(Return the element immidiately following and preceding where
 * 		 this should go. )
 * if an element with the same name already exists, free and return error
 * Fix the previous element to point to this one as next
 * Fix the next element to point to this one as previous
 * Update head pointer
 */
struct node *insert_student( struct node **head, char *last, char *first,
		struct assignment *grades, int number_of_assignments ) {

	// printf("allocating struct...\n");
	struct node *new = malloc(sizeof(struct node) );
	// printf("copying first name...\n");
	copy_string( &(new->first_name), first );
	// printf("copying last name...\n");
	copy_string( &(new->last_name), last );
	// printf("copying gradebook...\n");
	new->grades = grades;	// array is already created - use it.
	// printf("copying number of assignments...\n");
	new->num_assignments = number_of_assignments;


	// printf("Searching the list...\n");
	if( *head == NULL ) {
		/*
		 * Array is empty.
		 * This will be the first element.
		 */
		// printf("This is the first element in the list.\n");
		*head = new;
		new->next = NULL;
		new->previous = NULL;
	} else if( 0 != search_for_element( *head, last, first,
			&(new->next), &(new->previous) ) ) {
		/*
		 * This is good - it means the entry for the student doesn't
		 * already exist.  So, now we can link it in.
		 */
		// printf("place was found between %lld and %lld.\n",
				// (long long)(new->previous), (long long)(new->next) );
		// printf("Patching previous...\n");
		if( new->next != NULL ) {
			new->next->previous = new;
		}
		// printf("Patching next...\n");
		if( new->previous != NULL ) {
			new->previous->next = new;
		}
		// printf("Resetting head...\n");
		*head = get_first( *head );

	} else {
		/*
		 * The element already exists.
		 * Print warning to user, and don't create element.
		 */
		printf("Student already exists.  Deleting entry...\n");
		release_student( new );
	}
		
	return new;
}



/*
 * Separate a string at the first comma.
 * This replaces the comma with a null character, and returns a pointer
 * to the string after the comma.
 * If there is no comma, this will point to to the last character (null)
 * of the string.
 */
char * seperate_string( char *string ) {
	char *second = strchr( string, ',' );
	if( second != NULL ) {
		*second = '\0'; // seperate the string
		second = &second[1];	// point to the next character
	} else {
		/* comma was not found, so point to the last character */
		second = strchr( string, '\0' ); 
	}
	return second;
}


/*
 * Interpret student from line of text
 * and add student to array
 * This will stop at the first newline or null character.
 */

struct node *interpret_line( struct node **head, char *line ) {
	char *last;
	char *first;
	char *score;
	char *end;
	double value;
	int i = 0;
	struct assignment *grade_pairs;
	struct node *new = NULL;
	
	// Strip the newline off of the end
	char *tmp = strchr( line, '\n' );
	*tmp = '\0';

	last = line;
	first = seperate_string( last );
	line = seperate_string( first );

	/*
	 * If the name is valid, we can continue.
	 * Otherwise, skip this student.
	 */
	if(( strlen(first) > 0 ) && ( strlen(last) > 0 )){
		grade_pairs = malloc( sizeof(struct assignment)
				* MAX_NUM_ASSIGNMENTS );
		
		/* store each assignment */
		while( *line != '\0' ){
			score = seperate_string( line );
			value = strtod( score, &end );

			if( score != end ) {
				copy_string( &(grade_pairs[i].name), line );
				grade_pairs[i].score = value;
				++i;
			}
			if( i >= MAX_NUM_ASSIGNMENTS ) {
				/* We have all the assignments we can hold */
				printf("%s %s has reached the maximum number of",
						first, last );
				printf(" assignments, which is capped at %d.\n",
						MAX_NUM_ASSIGNMENTS );
				break;
			}

			/*
			 * Skip the next comma and go to the
			 * next assignment
			 */
			line = seperate_string( end );
		} 
		new = insert_student( head, last, first, grade_pairs, i );
	} else {
		/* Bad input */
	}
	return new;
}



/*
 * Allow user to manually add a new student (instead of from a new file)
 */
struct node *enter_new( struct node **head ) {
	char last[MAX_STRING_LENGTH];
	printf("\nPlease enter a new student:\n");
	fgets( last, MAX_STRING_LENGTH, stdin );

	// use this so that it uses the same code as read from file.
	struct node *new = interpret_line( head, last );

	if( new == NULL ) {
		fprintf( stderr, "That was not entered correctly.\n");
	}
	return new;
}
		


/*
 * Read gradebook from file
 *
 * The file should be formatted as:
 * Last_name,First_name[{,Assignment_name,score}*]
 * 
 * For example:
 * Horn,Marshal,Foo,3.45,Bar,834.2,Foobar,100
 * represents a student with the name Marshal Horn and three
 * assignments: Foo (with a score of 3.45), Bar (with a score
 * of 834.2), and Foobar (with a score of 100).
 *
 * It returns an error as an integer.
 */
int read_file( struct node **head, char *filename ) {
	char readonly = 'r';
	FILE *gradebook = fopen( filename, &readonly );
	int error = FILE_NOT_FOUND;
	if( gradebook != NULL ) {
		error = 0;	// the file was found

		/*
		 * Create the variables that will be used to interpret
		 * the file
		 */
		char storage[MAX_LINE_LENGTH];
		fgets( storage, MAX_LINE_LENGTH, gradebook );

		/* Make an entry for each student in the file */
		while( storage != NULL ){
			if( interpret_line( head, storage ) == NULL ) {
				error = BAD_INPUT;
			}
			fgets( storage, MAX_LINE_LENGTH, gradebook );
		} 

	}
	return error;
}


/*
 * Get command
 *
 * The storage input just provides a space for the input to be stored.
 */
void get_command( char **command, char **arguments, char *storage ) {
	/* Print the prompt, and clear erroneous data */
	printf("grade>");
	fflush( stdout );
	fflush( stdin );
	fgets( storage, MAX_LINE_LENGTH, stdin );
	
	/* Remove the trailing newline character */
	char *tmp = strchr( storage, '\n' );
	*tmp = '\0';


	/* convert input to lowercase */
	for( int i = 0; i < strlen(storage); ++i ) {
		storage[i] = tolower(storage[i]);
	}

	/* seperate the command from the arguments */
	*command = storage;
	*arguments = strchr( *command, ' ' );
	if( *arguments != NULL ) {
		**arguments = '\0'; // seperate the string
		*arguments = &((*arguments)[1]);	// point to the next character
	} else {
		/* ' ' was not found, so point to the last character */
		*arguments = strchr( *command, '\0' ); 
	}
}



/*
 * Command chooser
 * This executes a function based on user input
 */
void command_chooser( struct node **head ) {
	char run = 1;
	struct node *tmp;	// this stores the return of some functions
	char storage[MAX_STRING_LENGTH];
	char *command;
	char *argument;

	while( run ) {
		/* Get a line of input from the user */
		get_command( &command, &argument, storage );

		/* Now select the function to execute */
		if( !strcmp( command, "quit" ) ) {
			run = 0;
			printf("Quitting...\n");
		} else if( !strcmp( command, "add" ) ) {
			tmp = interpret_line( head, argument );
		} else if( !strcmp( command, "stats" ) ) {
		} else if( !strcmp( command, "getn" ) ) {
		} else if( !strcmp( command, "get0" ) ) {
		} else if( !strcmp( command, "getend" ) ) {
		} else if( !strcmp( command, "rm" ) ) {
		} else if( !strcmp( command, "len" ) ) {
		} else if( !strcmp( command, "ls" ) ) {
		} else if( !strcmp( command, "import" ) ) {
		} else if( !strcmp( command, "gradepointer" ) ) {
		} else if( !strcmp( command, "stat" ) ) {
		} else if( !strcmp( command, "allstat" ) ) {
		} else if( !strcmp( command, "echo" ) ) {
			printf("%s\n", argument);
		} else { // print useage
			fprintf( stderr, GRADEBOOK_USEAGE );
		}
		
	}

	close_gradebook( head ); 
	printf("DONE.\n");

	
}

#endif
