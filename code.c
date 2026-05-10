/*Compilador FOCA*/
#include <stdio.h>
int main(void) {
	float t1;
	float t2;
	int t3;
	int t4;
	int t5;
	float t6;
	float t7;

	t1 = 10.0;
	t2 = t1;
	t3 = 1;
	t4 = t3;
	t5 = (int) t4;
	t6 = (float) t5;
	t7 = t2 + t6;
	t2 = t7;
	return 0;
}

