/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;

	t1 = 0;
	t2 = t1;
	t3 = 10;
	t4 = t3;
L0:
	t5 = t2 < t4;
	if(!t5) goto L1;
	t6 = 1;
	t7 = t2 + t6;
	t2 = t7;
	goto L0;
L1:
	return 0;
}

