#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int maxi(int t1, int t2){
	int t3;
	t3 = t1 > t2;
	if(!t3) goto L0;
	return t1;
L0:
	return t2;
}

float maxf(float t1, float t2){
	float t3;
	t3 = t1 > t2;
	if(!t3) goto L1;
	return t1;
L1:
	return t2;
}

int mini(int t1, int t2){
	int t3;
	t3 = t1 < t2;
	if(!t3) goto L2;
	return t1;
L2:
	return t2;
}

float minf(float t1, float t2){
	float t3;
	t3 = t1 < t2;
	if(!t3) goto L3;
	return t1;
L3:
	return t2;
}

int powi(int t1, int t2){
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	t3 = 1;
	t4 = t3;
	t7 = 0;
	t5 = t7;
L4:
	t8 = t5 < t2;
	if(!t8) goto L5;
	t6 = t4 * t1;
	t4 = t6;
	t5 = t5 + 1;
	goto L4;
L5:
	return t4;
}

int fact(int t1){
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	t2 = 1;
	t3 = t2;
	t8 = 1;
	t4 = t8;
L6:
	t5 = 1;
	t6 = t1 + t5;
	t9 = t4 < t6;
	if(!t9) goto L7;
	t7 = t3 * t4;
	t3 = t7;
	t4 = t4 + 1;
	goto L6;
L7:
	return t3;
}

int sqrti(int t1){
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;
	t2 = 0;
	t3 = t1 <= t2;
	if(!t3) goto L8;
	t4 = 0;
	return t4;
L8:
	t5 = 0;
	t6 = t5;
L9:
	t7 = t6 * t6;
	t8 = t7 <= t1;
	if(!t8) goto L10;
	t6 = t6 + 1;
	goto L9;
L10:
	t9 = 1;
	t10 = t6 - t9;
	return t10;
}

float sqrtf(float t1){
	float t2;
	float t3;
	float t4;
	float t5;
	int t6;
	float t7;
	float t8;
	float t9;
	float t10;
	int t11;
	int t12;
	int t13;
	t2 = 0.0;
	t3 = t1 <= t2;
	if(!t3) goto L11;
	t4 = 0.0;
	return t4;
L11:
	t5 = t1;
	t11 = 0;
	t6 = t11;
L12:
	t12 = 25;
	t13 = t6 < t12;
	if(!t13) goto L13;
	t7 = t1 / t5;
	t8 = t5 + t7;
	t9 = 2.0;
	t10 = t8 / t9;
	t5 = t10;
	t6 = t6 + 1;
	goto L12;
L13:
	return t5;
}

int sumi(int* t1, int t2){
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	t3 = 0;
	t4 = t3;
	t8 = 0;
	t5 = t8;
L14:
	t9 = t5 < t2;
	if(!t9) goto L15;
	t6 = t1[t5];
	t7 = t4 + t6;
	t4 = t7;
	t5 = t5 + 1;
	goto L14;
L15:
	return t4;
}

float sumf(float* t1, int t2){
	float t3;
	float t4;
	int t5;
	float t6;
	float t7;
	int t8;
	int t9;
	t3 = 0.0;
	t4 = t3;
	t8 = 0;
	t5 = t8;
L16:
	t9 = t5 < t2;
	if(!t9) goto L17;
	t6 = t1[t5];
	t7 = t4 + t6;
	t4 = t7;
	t5 = t5 + 1;
	goto L16;
L17:
	return t4;
}

int maxElementi(int* t1, int t2){
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;
	int t11;
	t3 = 0;
	t4 = t1[t3];
	t5 = t4;
	t10 = 1;
	t6 = t10;
L18:
	t11 = t6 < t2;
	if(!t11) goto L19;
	t7 = t1[t6];
	t8 = t7 > t5;
	if(!t8) goto L20;
	t9 = t1[t6];
	t5 = t9;
L20:
	t6 = t6 + 1;
	goto L18;
L19:
	return t5;
}

int minElementi(int* t1, int t2){
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;
	int t11;
	t3 = 0;
	t4 = t1[t3];
	t5 = t4;
	t10 = 1;
	t6 = t10;
L21:
	t11 = t6 < t2;
	if(!t11) goto L22;
	t7 = t1[t6];
	t8 = t7 < t5;
	if(!t8) goto L23;
	t9 = t1[t6];
	t5 = t9;
L23:
	t6 = t6 + 1;
	goto L21;
L22:
	return t5;
}

void sort(int* t1, int t2){
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
	t21 = 0;
	t3 = t21;
L24:
	t22 = t3 < t2;
	if(!t22) goto L25;
	t19 = 0;
	t4 = t19;
L26:
	t5 = 1;
	t6 = t2 - t5;
	t20 = t4 < t6;
	if(!t20) goto L27;
	t7 = t1[t4];
	t8 = 1;
	t9 = t4 + t8;
	t10 = t1[t9];
	t11 = t7 > t10;
	if(!t11) goto L28;
	t12 = t1[t4];
	t13 = t12;
	t14 = 1;
	t15 = t4 + t14;
	t16 = t1[t15];
	t1[t4] = t16;
	t17 = 1;
	t18 = t4 + t17;
	t1[t18] = t13;
L28:
	t4 = t4 + 1;
	goto L26;
L27:
	t3 = t3 + 1;
	goto L24;
L25:
}

int find(int* t1, int t2, int t3){
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	t7 = 0;
	t4 = t7;
L29:
	t8 = t4 < t2;
	if(!t8) goto L30;
	t5 = t1[t4];
	t6 = t5 == t3;
	if(!t6) goto L31;
	return t4;
L31:
	t4 = t4 + 1;
	goto L29;
L30:
	t9 = 1;
	return t9;
}

int main(void) {
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int* t6;
	int t7;
	int t8;
	int t9;

	t1 = 0;
	t2 = 1;
	t3 = 20;
	t4 = 3;
	t5 = 4;
	t6 = (int*) malloc(5 * sizeof(int ));
	t6[0] = t1;
	t6[1] = t2;
	t6[2] = t3;
	t6[3] = t4;
	t6[4] = t5;
	t7 = 4;
	t8 = minElementi(t6, t7);
	t9 = t8;
	printf("%d", t9);
	free(t6);
	return 0;
}

