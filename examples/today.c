#include <stdio.h>

int main(int argc, char **argv) {
	int x = 4;
	int y;
	int z;
	
	
	if (4 == x) {
		
	}else{
		z = 9;
	}
	
	/*
	 * Ternary operator is often less lines of code than
	 * the if...else statement above.  These two statements
	 * do the same function.
	 */
	z = (4 ==x) ? 7 : 9;
	
	/*
	 * Once the program has found a true statement, it will
	 * stop evaluating the cases, but continue executing.
	 * Therefore, the break is used to stop fall-through.
	 */
	switch(z){
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}
}
}
