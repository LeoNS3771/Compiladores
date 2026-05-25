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

	t1 = 2;
	t2 = t1;
	t7 = 1;
	t8 = t2 == t7;
	if(t8) goto L2;
	t10 = 2;
	t11 = t2 == t10;
	if(t11) goto L3;
	goto L0;
L2:
	t3 = 1;
	t2 = t3;
	t4 = 1;
	t5 = t2 == t4;
	if(!t5) goto L1;
	t6 = 2;
	t2 = t6;
L1:
L3:
	t9 = 2;
	t2 = t9;
L0:
	return 0;
}

