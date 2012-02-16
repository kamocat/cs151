/*
 * Created by: Marshal Horn
 * File: hornm_hw0_3.c
 * Created 2012 January 27 7:54 PM
 * Modified 2012 January 29 2:21 PM
 *
 * Purpose:
 * Excercise 3.15
 * THe formula for the volume of a sphere is 4/3*pi*r*r*r, where r is the radius of the
 * sphere.  Write a program to compute the volume of the sphere.  Check your program
 * with a radius of 5 meters.  (a) The program accepts the user input for the radius
 * of the circle from the terminal and displays the result on the standard output.
 * (b) Redirect your input from the file sphere.dat and output hte file to
 * shpere.out in a command shell.
 *
 */

#include <stdio.h>

/* This is the ratio between r cubed and the volume of the sphere */
#define RATIO 3.14159265358979323*4/3

/*
 * Calculate the volume of a sphere
 * This uses the equation r*r*r*pi*4/3
 */
double sphere_volume(double r) {
	return (r*r*r*RATIO);
}

double radius;	// the radius of the sphere.  Input is selected by user.
double volume;	// the volume of the sphere.  Calculated by sphere_volume()


int main(int argc, char *argv[]) {
	printf("This program calculates the volume of a spehere from the radius.\n");
	printf("Please enter a radius: ");
	scanf("%lf", &radius);
	
	volume = sphere_volume(radius); // calculate the volume

	printf("The volume is %f cubic units\n", volume); // display the volume

	return 0;
}
