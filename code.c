/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int t1;
	int t2;
	int t3;
	int* t4;
	float t5;
	float t6;
	float t7;
	float* t8;
	char t9;
	char t10;
	char t11;
	char* t12;
	int t13;
	int t14;
	float t15;
	char t16;
	char* t17;
	char* t18;
	int t19;
	int t20;
	int t21;

	t3 = 10;
	t2 = 20;
	t1 = 30;
	t4 = (int*) malloc(3 * sizeof(int));
	t7 = 40.0;
	t6 = 50.0;
	t5 = 60.0;
	t8 = (float*) malloc(3 * sizeof(float));
	t8[0] = t7;
	t8[1] = t6;
	t8[2] = t5;
	t11 = 'a';
	t10 = 'b';
	t9 = 'c';
	t12 = (char*) malloc(3 * sizeof(char));
	t12[0] = t11;
	t12[1] = t10;
	t12[2] = t9;
	t19 = 0;
	t13 = t19;
L0:
	t20 = 3;
	t21 = t13 < t20;
	if(!t21) goto L1;
	t14 = t4[t13];
	printf("%d", t14);
	t18 = " ";
	printf("%s", t18);
	t15 = t8[t13];
	printf("%f", t15);
	t17 = " ";
	printf("%s", t17);
	t16 = t12[t13];
	printf("%c", t16);
	printf("\n");
	t13 = t13 + 1;
	goto L0;
L1:
	free(t12);
	free(t8);
	free(t4);
	return 0;
}

