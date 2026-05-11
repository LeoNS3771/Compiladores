/*Compilador FOCA*/
#include <stdio.h>
int main(void) {
	float t1;
	int t2;
	int t3;
	float t4;
	float t5;
	float t6;
	int t7;
	int t8;
	int t9;
	int t10;

	t2 = 10;
	t3 = t2;
	t4 = (float) t3;
	t5 = 3.5;
	t6 = t4 + t5;
	t1 = t6;
	t7 = (int) t1;
	t8 = 20;
	t9 = t3 < t8;
	t10 = !t9;
	return 0;
}

