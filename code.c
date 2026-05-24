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

	t1 = 1;
	t2 = t1;
L0:
	t3 = 3;
	t4 = t2 < t3;
	if(!t4) goto L1;
	t5 = 1;
	t6 = t2 + t5;
	t2 = t6;
	t7 = 2;
	t8 = t2 % t7;
	t9 = 0;
	t10 = t8 == t9;
	if(!t10) goto L2;
	goto L1;
L2:
	goto L0;
L1:
	return 0;
}

