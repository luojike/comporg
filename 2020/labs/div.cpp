#include <stdio.h>
#include <stdint.h>

#define divzero (-1)


int divint32(int32_t x, int32_t y, int32_t& q, int32_t& r) {
	// FIXME: Result is wrong

	if(y==0) { return divzero; }

	int64_t xx = x<0 ? (-x) : x;
	int64_t yy = y<0 ? (-y) : y;

	yy = yy << sizeof(int32_t);

	q = 0;

	for(int i=0; i < 8*sizeof(int32_t); i++) {
		q = q << 1;
		if(xx >= yy) { 
			q = q + 1; 
			xx = xx - yy;
		}
		yy = yy >> 1;
	}

	if(x<0 && y>0 || x>0 && y<0) { q = -q; }

	if(x<0) { r = -xx; } else { r = xx; }

	return 0;
}

int main() {

	int32_t x = 5;
	int32_t y = -3;

	int32_t q, r;

	while(1) {
		printf("\nInput x:");
		scanf("%d", &x);

		printf("\nInput y:");
		scanf("%d", &y);

		if(divint32(x, y, q, r) == divzero) { 
			printf("!!! Divided by 0 !!!\n"); 
			break;
		}
		else { 
			printf("divint32(%d, %d, q, r) = %d, left %d\n", x, y, q, r); 
		}
	}

	return 0;

}

