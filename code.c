/*Compilador FOCA*/
#include <stdio.h>
#include "runtime.h"
int main(void) {
	Value t1;
	Value t2;
	Value t3;
	Value t4;
	Value t5;
	Value t6;

	t1 = make_float(10.0);
	t2 = t1;
	t3 = make_int(5);
	t4 = t3;
	t5 = add(t2,t4);
	t6 = t5;
	return 0;
}

