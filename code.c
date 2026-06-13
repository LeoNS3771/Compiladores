/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int t1;
	int t2;
	int t3;
	int t4;
	char* t5;
	char* t6;

	t1 = 0;
	t2 = t1;
L0:
	t3 = 10;
	t4 = t2 < t3;
	if(!t4) goto L1;
	t5 = "alo meu filho numero ";
	t6 = (char*) malloc(4096);
	strcpy(t6, t5);
	printf("%s", t6);
	printf("%d", t2);
	free(t6);
	t2 = t2 + 1;
	goto L0;
L1:
	return 0;
}

