/*Compilador*/
#include <stdio.h>
int main(void) {
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;
	int t11;
	int t12;
	int t13;

	t1 = 0;
	t2 = t1;
	t3 = 1;
	t4 = t3;
	goto L3;
L0:
	t12 = 10;
	t13 = t2 < t12;
	if(!t13) goto L1;
L3:
	t5 = 2;
	t6 = t4 % t5;
	t7 = 0;
	t8 = t6 == t7;
	if(!t8) goto L2;
	goto L0;
L2:
	t9 = t2 + t4;
	t2 = t9;
	t10 = 1;
	t11 = t4 + t10;
	t4 = t11;
	goto L0;
L1:
	return 0;
}

