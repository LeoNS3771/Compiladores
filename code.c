/*Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;
	int t11;
	int t12;
	int t13;
	int t14;
	int t15;
	int t16;
	int t17;
	int t18;
	int t19;
	int t20;
	int t21;
	int t22;
	int t23;
	int t24;
	int t25;
	int t26;
	int t27;
	int t28;
	int t29;
	int t30;
	int t31;
	int t32;
	int t33;
	int t34;
	int t35;
	int t36;
	int t37;
	int t38;
	int t39;
	int t40;
	int t41;
	int t42;
	int t43;
	int t44;
	int t45;
	int t46;
	int t47;

	t1 = 20;
	t2 = t1;
	t3 = 0;
	t4 = t3;
	t5 = 0;
	t6 = t5;
	t21 = 0;
	t7 = t21;
L0:
	t22 = t7 < t2;
	if(!t22) goto L1;
	t8 = 3;
	t9 = t7 % t8;
	t8 = 3;
	t9 = t7 % t8;
	t14 = 0;
	t15 = t9 == t14;
	if(t15) goto L4;
	t8 = 3;
	t9 = t7 % t8;
	t18 = 1;
	t19 = t9 == t18;
	if(t19) goto L6;
	goto L7;
	goto L3;
L4:
	t10 = 2;
	t11 = t7 * t10;
	t12 = t11;
	t13 = t4 + t12;
	t4 = t13;
	goto L3;
L6:
	t16 = 50;
	t17 = t4 > t16;
	if(!t17) goto L5;
	goto L3;
L5:
	goto L3;
L7:
	t20 = t4 + t7;
	t4 = t20;
L3:
	t7 = t7 + 1;
	goto L0;
L1:
	printf("%d\n", t4);
	t23 = 0;
	t24 = t23;
	t25 = 1;
	t26 = t25;
	goto L14;
L8:
	t34 = 3;
	t35 = t24 < t34;
	if(!t35) goto L9;
L14:
	t31 = 1;
	t27 = t31;
L10:
	t32 = 5;
	t33 = t27 < t32;
	if(!t33) goto L11;
	t28 = 3;
	t29 = t27 == t28;
	if(!t29) goto L13;
	goto L12;
L13:
	t30 = t26 * t27;
	t26 = t30;
L12:
	t27 = t27 + 1;
	goto L10;
L11:
	t24 = t24 + 1;
	goto L8;
L9:
	printf("%d\n", t26);
	t45 = 0;
	t36 = t45;
L15:
	t46 = 10;
	t47 = t36 < t46;
	if(!t47) goto L16;
	t42 = 0;
	t37 = t42;
L17:
	t43 = 10;
	t44 = t37 < t43;
	if(!t44) goto L18;
	t38 = t36 == t37;
	if(!t38) goto L20;
	goto L19;
L20:
	t39 = t36 + t37;
	t40 = 9;
	t41 = t39 == t40;
	if(!t41) goto L21;
	goto L16;
L21:
L19:
	t37 = t37 + 1;
	goto L17;
L18:
	t36 = t36 + 1;
	goto L15;
L16:
	printf("%d\n", t36);
	return 0;
}

