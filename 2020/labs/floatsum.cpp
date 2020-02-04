#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#define MYDBG

int main() {

	float a = 1;
	float s;
	float *x = NULL;
	int n = 0;
	int i;
	float t;

	while(1) {
		printf("\n输入种子数 a (将用 a×2^(i-n/2) 填充数组x[n])：");
		scanf("%f", &a);
		printf("\na=%f\n", a);

		printf("\n输入数组 float x[n] 的大小 n (非正数将退出程序)：");
		while(scanf("%d", &n) != 1) { getchar(); }

		if(n<1) break;

		x = (float*) malloc( sizeof(float) * n );
		if(x==NULL) { printf("\n申请数组 float x[%d] 空间失败！\n", n); continue; }

		for(i=0; i<n; i++) {
			x[i] = a * powf(2, i-n/2);
#ifdef MYDBG
			printf("\nx[%d] = %f", i, x[i]);
#endif
		}

		s = 0;
		for(i=0; i<n; i++) {
			s += x[i];
#ifdef MYDBG
			printf("\ns=%f", s);
#endif
		}
		printf("\n\n从 0 到 %d 累加 x[i] 得到：%f\n", n-1, s);

		s = 0;
		for(i=n-1; i>=0; i--) {
			s += x[i];
#ifdef MYDBG
			printf("\ns=%f", s);
#endif
		}
		printf("\n从 %d 到 0 累加 x[i] 得到：%f\n", n-1, s);

		s = 0;
		for(i=0; i<n/2; i++) {
			t = x[i] + x[n-1-i];
#ifdef MYDBG
			printf("\nt=x[%d]+x[%d]=%f", i, n-1-i, t);
#endif
			s += t;
#ifdef MYDBG
			printf("\ns=%f after adding t", s);
#endif
		}
		if(n%2) { 
			s += x[n/2]; 
#ifdef MYDBG
			printf("\ns=%f after adding x[%d]", s, n/2);
#endif
		}
		printf("\n从 0 到 %d 成对累加 x[i], x[n-1-i] 得到：%f\n", n/2, s);

		free(x); x = NULL;
	}

	return 0;
}

