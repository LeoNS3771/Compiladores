/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char* t1;
	char* t2;
	char* t3;
	char* t4;
	char* t5;
	char* t6;
	char* t7;
	char* t8;
	char* t9;

	t1 = "alo";
	t2 = t1;
	t3 = " tudo bem?";
	t4 = t3;
	t5 = (char *) malloc(256);
	strcpy(t5,t2);
	strcat(t5,t4);
	t6 = t5;
	t7 = "!";
	t8 = (char *) malloc(256);
	strcpy(t8,t6);
	strcat(t8,t7);
	t9 = t8;
	printf("%s\n", t9);
	return 0;
}

