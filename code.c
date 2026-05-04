/*Compilador FOCA*/
#include <stdio.h>
int main(void) {
	int t1;
	float t10;
	float t11;
	int t12;
	int t13;
	int t14;
	int t15;
	int t2;
	float t3;
	float t4;
	float t5;
	int t6;
	float t7;
	float t8;
	float t9;

	t1 = 5;
	t2 = t1;
	t4 = (float) t2;
	t3 = 1.0;
	t5 = t4 + t3;
	t6 = 5;
	t8 = (float) t6;
	t7 = 2.0;
	t9 = t8 * t7;
	t10 = t5 < t9;
	t11 = t10;
	t12 = (int) t11;
	t13 = 15;
	t14 = t12 + t13;
	t15 = t14;
	return 0;
}

