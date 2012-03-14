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
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
 * Struct declarations
 */
#define MAX_STRING_LENGTH 100

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
int add_value( struct node *head, char *first, char *last,
		struct assignment *grades, int number_of_assignments ) {
	struct node *new = malloc(sizeof(struct node) );

	/* Copy the first name over */
	new->first_name = malloc(MAX_STRING_LENGTH);
	strncpy(new->first_name, first, (MAX_STRING_LENGTH - 1) );
	new->first_name[MAX_STRING_LENGTH - 1] = '\0';

	/* Copy the last name over */
	new->last_name = malloc(MAX_STRING_LENGTH);
	strncpy(new->last_name, last, (MAX_STRING_LENGTH - 1) );
	new->last_name[MAX_STRING_LENGTH - 1] = '\0';

/*
 * Search the list by last name (first name optional)
 *
 * Start with the first element
 * While( next_pointer != NULL_POINTER )
 * 		int eval = strcmp( last, element->last )
 * 		if( eval > 0 )
 * 			go to next element
 * 		else if ( eval < 0 )
 * 			error = STUDENT_NOT_FOUND
 * 		else if( eval == 0 )
 * 			if( strlen( first ) ) 
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
int search_for_element( struct node *head, char *last, char *first,
		struct node **address, struct node **preceding );


/*
 * Search by first name
 *
 * Start at top of list
 * error = ELEMENT_NOT_FOUND
 * while( ( first != element->first ) 
 * 			&& ( (*element)->next != NULL_POINTER ) )
 * 		go to next pointer
 * if( first == (*element)->first )
 * 		error = NO_ERROR
 * return error
 *
 */
int search_for_first_name( struct node *head, char *first,
		struct node **address );


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
int get_assignment( struct node *student, char *assignment, double *score );


/*
 * Return length of list
 *
 * start at first element
 * int length = 0
 * while( element_pointer != NULL_POINTER )
 * 		go to next element
 * 		++length
 * return length
 */
int get_length( struct node *head );


/*
 * Return nth element from list
 *
 * int error
 * for( n )
 * 		if( head->next != NULL_POINTER )
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
int get_nth_element( struct node *head, int n, struct node **element );


/*
 * Return last element in list
 *
 * while( head->next != NULL_POINTER )
 * 		head = head->next
 *
 * return head
 */
struct node* get_last( struct node *head );



/*
 * Print the list
 *
 *
 * Start at the element pointed to.
 * for( n )
 * 		print element
 * 		if( first->next != NULL_POINTER )
 * 			first = first->next
 * 		else
 * 			((no error for trying to print more elements than there are))
 * 			break
 *
 * return start
 */
struct node* print_list( struct node *first, int n );



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
 * Calculate median
 *
 * This function sorts the array.  Do not use it where the array must
 * stay unsorted
 */

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
struct stats stats_on_assignment( struct node *head, char *assignment );



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
struct stats stats_on_individual( struct node *student );




int main( int argc, char **argv ) {
	printf("Main does nothing yet.\n");
	return 0;
}

