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

	t1 = 2;
	t2 = 3;
	t3 = t1 > t2;
	if(!t3) goto L0;
	t4 = 12;
	t5 = t4;
L0:
	t6 = 1;
	t7 = t6;
	return 0;
}

