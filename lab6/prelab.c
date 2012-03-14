/*
 * Original author: Marshal Horn
 * file: prelab.c
 * Created: 2012 Feb 16 at 12:42 AM
 * Modified: 2012 Feb 16 at 12:42 AM
 *
 * Purpose:
 * Print out a table of the binary, hex, and decimal equivelents of the
 * following characters:
 * 'A', 'a', '0', '9', 'z', 'Z'
 *
 */

#include <stdio.h>


#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
	  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 


#define LENGTH 6

char array[] = { 'A', 'a', '0', '9', 'z', 'Z' };

void print_header() {
	printf("char\t\thex\t\tdecimal\t\tbinary\n");
}
void print_char( char c ) {
	printf("%c\t\t", c);
	printf("%x\t\t%d\t\t\n", c, c );
}


int main( int argc, char **argv ) {
	print_header();
	int i;
	for( i = 0; i < LENGTH; ++i ) {
		print_char( array[i] );
	}
	return 0;
}
