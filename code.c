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
	int t7;
	int t8;

	t1 = "alo";
	t2 = t1;
	t3 = "tudo";
	t4 = t3;
	t5 = 1;
	t6 = 1;
	t7 = t5 && t6;
	t8 = t7;
	printf("%i\n", t8);
	return 0;
}

