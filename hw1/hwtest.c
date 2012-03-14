// 11.8 What does this program do?
#include <stdio.h>
void mystery1( char *, const char * );

int main( int argc, char **argv ) {
	char string1[80], string2[80];

	printf("Enter two strings: ");
	scanf("%s%s", string1, string2 );
	mystery1( string1, string2 );
	printf("%s", string1 );
	return 0;
}

void mystery1( char *s1, const char *s2 ) {
	/* makes s1 pointing to the end of string s1 */
	while( *s1 != '\0' ) {
		++s1;
	}
	while( *s1 = *s2 ) {
		s1++;
		s2++;
	}
}







