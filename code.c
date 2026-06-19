/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Cliente{
	char* nome;
	int idade;
	float peso;
};

int main(void) {
	int t1;
	int t2;
	int t3;
	int* t4;
	struct Cliente t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;

	t3 = 1;
	t2 = 2;
	t1 = 3;
	t4 = (int*) malloc(3 * sizeof(int));
	t4[0] = t3;
	t4[1] = t2;
	t4[2] = t1;
	t6 = 0;
	t7 = t6;
L0:
	t8 = 3;
	t9 = t7 < t8;
	if(!t9) goto L1;
	t10 = t4[t7];
	printf("%d", t10);
	printf("\n");
	t7 = t7 + 1;
	goto L0;
L1:
	free(t4);
	return 0;
}

