#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Pessoa{
	char* nome;
	int idade;
}Pessoa;

void mostrarPessoa(Pessoa t1){
	char* t2;
	int t3;
	t2 = t1.nome;
	printf("%s", t2);
	t3 = t1.idade;
	printf("%d", t3);
}

void mostrar(int t1){
	printf("%d", t1);
	printf("\n");
}

int main(void) {
	char* t1;
	int t2;
	struct Pessoa t3;
	struct Pessoa* t4;
	float t5;
	int t6;

	t1 = "maria";
	t2 = 22;
	t3.nome = t1;
	t3.idade = t2;
	t4 = malloc(1* sizeof(struct Pessoa));
	t4[0].nome = t3.nome;
	t4[0].idade = t3.idade;
	mostrarPessoa(t3);
	t5 = 1.0;
	mostrar(t5);
	t6 = 2;
	mostrar(t6);
	return 0;
}

