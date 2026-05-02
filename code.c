/*Compilador da nossa linguagem... Shakal?????*/
#include <stdio.h>
#include "runtime.h"
int main(void) {
	Value t1;
	Value t2;
	Value t3;

	t1 = make_int(10);
	t2 = t1;
	t3 = make_float(15.0);
	t2 = t3;
	return 0;
}

