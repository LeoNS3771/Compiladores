/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int t1;
	int t2;
	char* t3;
	undefined t4;
	char* t5;
	char* t6;
	int t7;
	int t8;
	undefined t9;
	int t10;
	int t11;

	t1 = 0;
	t2 = t1;
	t3 = "vi";
	t4 = t3;
	t5 = "ado";
	t6 = t5;
L0:
	t7 = 10;
	t8 = t2 < t7;
	if(!t8) goto L1;
	t9 = t4 + t6;
	t4 = t9;
	t10 = 1;
	t11 = t2 + t10;
	t2 = t11;
	goto L0;
L1:
	printf(, t4);
	return 0;
}

