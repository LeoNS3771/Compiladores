#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função auxiliar
int __tamString(char* t1)
{
	int t2;
	int t3;
	char t4;
	char t5;
	char t6;
	t2 = 0;
	t3 = t2;
L0:
	t4 = t1[t3];
	t5 = '\0';
	t6 = t4 != t5;
	if(!t6) goto L1;
	t3 = t3 + 1;
	goto L0;
L1:
	return t3;
}

int main(void) {
	char* t1;
	char* t2;
	char* t3;
	int t4;
	int t5;
	int t6;
	int t7;
	char* t8;
	char* t9;
	int t10;
	int t11;
	int t12;
	int t13;
	char* t14;
	char* t15;

	t1 = "2";
	t2 = "2";
	t4 = __tamString(t1);
	t5 = __tamString(t2);
	t6 = t4 + t5;
	t7 = t6 + 1;
	t3 = (char*) malloc(t7);
	strcpy(t3, t1);
	strcat(t3, t2);
	t8 = "2";
	t10 = __tamString(t3);
	t11 = __tamString(t8);
	t12 = t10 + t11;
	t13 = t12 + 1;
	t9 = (char*) malloc(t13);
	strcpy(t9, t3);
	strcat(t9, t8);
	t14 = (char*) malloc(__tamString(t9 + 1));
	strcpy(t14, t9);
	scanf("%s", t15);
	free(t14);
	return 0;
}

