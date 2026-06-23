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
	float t4;
	int t5;

	t1 = "maria";
	t2 = 22;
	t3.nome = t1;
	t3.idade = t2;
	mostrarPessoa(t3);
	t4 = 1.0;
	mostrar(t4);
	t5 = 2;
	mostrar(t5);
	return 0;
}

