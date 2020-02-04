#include <stdio.h>

void test() {

	printf("\n!!!执行了 test 函数!!!\n\n");

	return;
}

int sumset(int x, int y, int i) {

	int a = x;
	int b = y;
	void* c[1];

	printf("\nsumset(x, y, i) 参数 x 的地址是: %lx \n", (unsigned long)&x);
	printf("\nsumset(x, y, i) 参数 y 的地址是: %lx \n", (unsigned long)&y);
	printf("\nsumset(x, y, i) 参数 i 的地址是: %lx \n", (unsigned long)&i);
	printf("\nsumset 函数局部变量 a 的地址是:  %lx \n", (unsigned long)&a);
	printf("\nsumset 函数局部变量 b 的地址是:  %lx \n", (unsigned long)&b);
	printf("\nsumset 函数局部变量 c 的地址是:  %lx \n\n", (unsigned long)&c);

	for(int k=0; k<=i+1; k++) {
		printf("c[%d] = %16lx \n", k, (unsigned long)c[k]);
	}

	printf("\nc[%d] 中的原值 %lx 将被赋予新值 %lx \n", i, (unsigned long)c[i], (unsigned long)test);

	c[i] = (void*)test;

	return a+b;
}


int main() {

	int a;

	printf("\nmain   函数的地址是: %lx \n", (unsigned long)main);
	printf("\nsumset 函数的地址是: %lx \n", (unsigned long)sumset);
	printf("\ntest   函数的地址是: %lx \n", (unsigned long)test);

	while(1) {

		printf("\n输入一个整数(负数将退出程序):");
		scanf("%d", &a);

		if(a < 0) break;

		printf("\n调用函数 sumset(%d, %d, %d) \n", a, a, a);
		sumset(a, a, a);

	}

	return 0;
}

