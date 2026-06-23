#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Pessoa{
	char* nome;
	int idade;
};

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

void proc(){
	char* t1;
	t1 = "procedimento chamado";
	printf("%s", t1);
	printf("\n");
}

int main(void) {
	int t1;
	int t2;
	char* t3;
	float t4;
	float t5;
	char* t6;
	char* t7;
	char* t8;
	char* t9;
	char* t10;
	char* t11;
	char* t12;
	int t13;
	int t14;
	int t15;
	int t16;
	int t17;
	int t18;
	int t19;
	int t20;
	char* t21;
	int t22;
	struct Pessoa t23;
	char* t24;

	t1 = 10;
	t2 = t1;
	t3 = " ";
	printf("%s", t3);
	printf("%d", t2);
	t4 = 1.0;
	t5 = t4;
	t6 = " ";
	printf("%s", t6);
	printf("%f", t5);
	t7 = "c";
	t8 = (char*) malloc(__tamString(t7 + 1));
	strcpy(t8, t7);
	t9 = " ";
	printf("%s", t9);
	printf("%s", t8);
	printf("\n");
	t10 = "string_a";
	t11 = (char*) malloc(__tamString(t10 + 1));
	strcpy(t11, t10);
	t12 = "agora a é do tipo string: ";
	printf("%s", t12);
	printf("%s", t11);
	proc();
	t13 = 0;
	t14 = t13;
	t15 = 0;
	t16 = t15;
L0:
	t17 = 10;
	t18 = t16 < t17;
	if(!t18) goto L1;
L2:
	t19 = 5;
	t20 = t16 == t19;
	if(!t20) goto L3;
	goto L3;
	goto L2;
L3:
	printf("%d", t16);
	t16 = t16 + 1;
	goto L0;
L1:
	printf(" ");
	printf("\n");
	t21 = "Maria";
	t22 = 22;
	t23.nome = t21;
	t23.idade = t22;
	t24 = t23.nome;
	printf("%s", t24);
	printf("\n");
	free(t11);
	free(t8);
	return 0;
}

