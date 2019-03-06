#include <stdio.h>

// TODO: Only read operations are implemented, 
//        please add write operations.

#define memsize (4096)

typedef int word; // assume int as word

union dataunion {
	char c[sizeof(double)];
	double d;
	float f;
	long l;
	int i;
	short s;
} datarray;

char mem[memsize];

char readbyte(unsigned addr) {
	return mem[addr];
}

word readword(unsigned addr) {
	return *( (word*) &(mem[addr]) );

}

short readshort(unsigned addr) {
	unsigned k = addr;
	for(int i=0; i<sizeof(short); i++, k++) {
		datarray.c[i] = mem[k];
	}

	return datarray.s;
}

int readint(unsigned addr) {
	unsigned k = addr;
	for(int i=0; i<sizeof(int); i++, k++) {
		datarray.c[i] = mem[k];
	}

	return datarray.i;
}

long readlong(unsigned addr) {
	unsigned k = addr;
	for(int i=0; i<sizeof(long); i++, k++) {
		datarray.c[i] = mem[k];
	}

	return datarray.l;
}

float readfloat(unsigned addr) {
	unsigned k = addr;
	for(int i=0; i<sizeof(float); i++, k++) {
		datarray.c[i] = mem[k];
	}

	return datarray.f;
}

double readdouble(unsigned addr) {
	unsigned k = addr;
	for(int i=0; i<sizeof(double); i++, k++) {
		datarray.c[i] = mem[k];
	}

	return datarray.d;
}

int main() {
	//
	for(int i=0; i<memsize; i+=sizeof(word)) {
		*((word*)&mem[i]) = i;
		// writeword(address, i);
	}

	for(int i=0; i<memsize; i+=sizeof(int)) {
		printf("mem[%d] = %d\n", i, readint(i));
	}

	for(int i=0; i<memsize; i++) {
		printf("mem[%d] = %d\n", i, readbyte(i));
	}

	return 0;
}

