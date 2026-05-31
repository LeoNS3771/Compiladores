/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int t1;
	int t2;
	bool t3;
	bool t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;

	t1 = 0;
	t2 = t1;
	t3 = 1;
	t4 = t3;
	t5 = 0;
	t6 = t5;
L0:
	t7 = 10;
	t8 = t2 < t7;
	if(!t8) goto L1;
	t9 = 1;
	t10 = t2 + t9;
	t2 = t10;
	goto L0;
L1:
	return 0;
}

