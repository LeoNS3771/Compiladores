#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	char* __t1;
	char* __t2;
	char* __t3;
	char* __t4;
	char* __t5;
	char* __t6;

	__t1 = "alo, ";
	__t2 = (char*) malloc(__tamString(__t1 + 1));
	strcpy(__t2, __t1);
	__t3 = "tudo bem?";
	__t4 = (char*) malloc(__tamString(__t3 + 1));
	strcpy(__t4, __t3);
	__t5 = (char*) malloc(4096);
	strcpy(__t5, __t2);
	strcat(__t5, __t4);
	__t6 = (char*) malloc(__tamString(__t5 + 1));
	strcpy(__t6, __t5);
	printf("%s", __t6);
	free(__t6);
	free(__t4);
	free(__t2);
	return 0;
}

