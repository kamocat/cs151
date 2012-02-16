/* Study Questions for lab 2 */
#include <stdio.h>

int main(void){
	char school[] = "Oregon State";
	char grade;
	int x = 20, y = 3;
	int a = x/y;
	int b = x%y;
	int c = y%x;

	float z = 21.74;
	printf("%i\n", (int)z);
	printf("%5.1f\n", z);
	
	printf("School: %s\nGrade: %d\nx: %d\nz: %f\n", 
		school, 	grade,		x,	  z);
}
