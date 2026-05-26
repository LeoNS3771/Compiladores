/*Compilador*/
#include <stdio.h>
int main(void) {
	int t1;
	int t2;
	int t3;
	int t4;
	float t5;
	float t6;
	int t7;
	int t8;
	int t9;
	int t10;
	char t11;
	char t12;

	t1 = 2;
	t2 = t1;
	t9 = 1;
	t10 = t2 == t9;
	if(t10) goto L3;
	goto L4;
	goto L0;
L3:
	t3 = 1;
	t2 = t3;
	t4 = 2;
	t4 = 2;
	t7 = 1;
	t8 = t4 == t7;
	if(t8) goto L2;
	goto L1;
L2:
	t5 = 1.1;
	t6 = t5;
	goto L1;
L1:
	goto L0;
L4:
	t11 = 'd';
	t12 = t11;
L0:
	return 0;
}

