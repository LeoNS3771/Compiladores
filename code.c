/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char* t1;
	char* t2;
	int t3;
	int t4;
	char t5;
	char t6;
	char t7;
	char t8;

	t1 = "alo";
	t2 = (char*) malloc(4096);
	strcpy(t2, t1);
	t3 = 0;
	t4 = t3;
L0:
	t5 = t2[t4];
	t6 = '\0';
	t7 = t5 != t6;
	if(!t7) goto L1;
	t8 = t2[t4];
	printf("%c", t8);
	printf("\n");
	t4 = t4 + 1;
	goto L0;
L1:
	free(t2);
	return 0;
}

