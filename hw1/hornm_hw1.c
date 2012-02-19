/*
 * Original Author: Marshal Horn
 * File: hornm_hw1.c
 * Created: 2012 Feb 16 at 6:56 PM
 * Modified: 2012 Feb 16 at 6:56 PM
 *
 * Excercises:
 * (1)	10.7
 * (2)	10.10
 * (3)	10.30
 * (4)	10.33 (EC)
 * (5)	11.6
 * (6)	11.7
 *
 * (7)	Write a program which uses pointers and arrays to perform matrix
 * multiplication.
 *
 * (8)	Sieve or Eratosthenes
 * (EC is using command-line argument for this)
 *
 * (9)	Write a function that concatenates the string s2 to the end of 
 * string s1 using pointers.
 *
 */

#include <stdio.h>
#include <stdlib.h>



/******************************************************************
 ***************	Task 2		Excercise 10.10		***************
 * Find the centroid of an array
 *
 *****************************************************************/

#define POINT_QUANTITY 4
#define X_AXIS 0
#define Y_AXIS 1
#define AXIS_STRIDE 2
double p[][AXIS_STRIDE] = {
	{ 5.0, -4.0 },
	{ 4.0,  3.0 },
	{-1.0,  6.0 },
	{-9.0,  5.0 }
};

double g[] = { 0.25, 0.57, 0.63, 0.1 };

void comp_c( int nrows, double p[][AXIS_STRIDE], const double g[], 
		double centr[AXIS_STRIDE] ) {
	double intensity_sum = 0;	// sum of all intensities
	double x_sum = 0;			// sum of intensities multiplied by x values
	double y_sum = 0;			// sum of intensities multiplied by y values
	for( int i = 0; i < nrows; ++i ) {
		intensity_sum += g[i];
		x_sum += g[i] * p[i][X_AXIS];
		y_sum += g[i] * p[i][Y_AXIS];
#ifdef DEBUG
		printf("%f, %f, %f\n", intensity_sum, x_sum, y_sum );
#endif
	}
	/*
	 * Now that we have the summs of the x and y axis, we need to divide this
	 * by the sum of the intensities.  This way, we get a weighted average, 
	 * resulting in the "center of mass" of the intensities, which is
	 * called the centroid.
	 */
	centr[X_AXIS] = x_sum / intensity_sum;
	centr[Y_AXIS] = y_sum / intensity_sum;
}


/*
 * This is the wrapper for task 2.
 * All its inputs are defined by arrays initialized in this file.
 */
void task_2 ( ) {
	double centr[2];
	/* Calculate the centroid of the given arrays */
	comp_c( POINT_QUANTITY, p, g, centr );

	printf("Task 2:\n");
	printf("centroid = %.3f %.3f\n", centr[X_AXIS], centr[Y_AXIS] );

	return;
}



/***********************************************
 ***********	Program chooser		************
 **********************************************/
#define LAST_EXCERCISE 9
int chooser_core( int argc, char **argv, int argi, int function ) {
	switch( function ) {
		case 2:
			task_2();
			break;

		default:
			printf("task %d is not yet implemented.\n", function );
			break;
	}
	printf("\n");	// print a new line to separeate tasks
	/*
	 * If we just return argi without incrementing, it means
	 * the selected function did not take any values.
	 */
	return argi;
}

void tell_useage( char *argument ) {
	printf("The argument %s is invalid.\n", argument );
	printf("The options are: -[123456789] \n" );
}


int decode_argument( char *string ) {
	int return_value;
	int arg = atoi( string );
	/*
	 * Because of the preceding dash, atoi reads as negative numbers.
	 * We negate the value here to fix that.
	 */
	arg = -arg;
	if( ( string[0] == '-' ) && ( arg <= LAST_EXCERCISE ) ) {
			return_value = arg;
	} else {
			return_value = 0;
	}
	return return_value;
}

void program_chooser( int argc, char **argv ) {
	int argi = 1;	// This is the current argument index

	/* 
	 * This is the task to be performed.  If it is zero, then
	 * the task is invalid.
	 */
	int task;

	/* While there are still arguments left */
	while( argi < argc ) {
		task = decode_argument( argv[argi] );

		if( task ) {
			++argi;
			/* pass arguments on to chooser_core */
			argi = chooser_core( argc, argv, argi, task );

		} else {	// If the task is invalid
			/* instruct user on useage */
			char *tmp = argv[argi];
			tell_useage( tmp );
			/* Increment argument index afterwards */
			++argi;
		}
	}
}



int main( int argc, char **argv ) {
	program_chooser( argc, argv );

	return 0;
}


