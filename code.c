/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char* t1;
	char* t2;
	char* t3;
	char* t4;
	int t5;
	int t6;
	char* t7;
	int t8;
	int t9;
	char* t10;
	int t11;
	int t12;

	t1 = "a";
	t2 = (char*) malloc(256);
	strcpy(t2, t1);
	t3 = "b";
	t4 = (char*) malloc(256);
	strcpy(t4, t3);
	t5 = 0;
	t6 = t5;
	t7 = (char*) malloc(256);
	strcpy(t7, t2);
L0:
	t8 = 10;
	t9 = t6 < t8;
	if(!t9) goto L1;
	t10 = (char*) malloc(256);
	strcpy(t10, t7);
	strcat(t10, t4);
	t7 = (char*) malloc(256);
	strcpy(t7, t10);
	t11 = 1;
	t12 = t6 + t11;
	t6 = t12;
	goto L0;
L1:
	printf("%s\n", t7);
	return 0;
}

