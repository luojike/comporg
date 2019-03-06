#include <stdio.h>
#include <stdint.h>

#define OPALU 0
#define OPLW  35
#define OPSW  43
#define OPBEQ 4
#define OPJ   2

#define FNADD 32
#define FNSUB 34
#define FNAND 36
#define FNOR  37
#define FNSLT 42

#define MSIZE 256

char M[MSIZE]; // 存储器

int32_t readword(uint32_t addr) {
	return *((int32_t *)&M[addr]);
}

void writeword(uint32_t addr, int32_t data) {
	*((int32_t *)&M[addr]) = data;
}

int32_t R[32]; // 通用寄存器

uint32_t PC; // 保存下一条要执行指令的地址

uint32_t IR; // 指令寄存器，保存当前被执行的指令

// TODO: 有些字段请自行补全
#define GETOP(ir) ((ir>>26) & 63)
#define GETRS(ir) ((ir>>21) & 31)
#define GETRD(ir) ((ir>>11) & 31)
#define GETAD(ir) (ir & 0x3ffffff)

void fetch() {
	// TODO: 读取PC指向的指令到指令寄存器中
	PC = PC + 4; // beq and j will change this in execution
}

void init() {
	int32_t d[2] = {-1, 1};
	for(int i=0; i<32; i++) { R[i] = 0; }
	for(int i=0; i<MSIZE/4; i++) { writeword(4*i, d[i%2]); }

	writeword(0, (OPLW<<26) | (1<<16) | (MSIZE-4)); // lw $1, $0(252)
	writeword(4, (OPLW<<26) | (2<<16) | (MSIZE-8)); // lw $2, $0(0)
	writeword(8, (OPBEQ<<26) | (1<<21) | (2<<16) | 7); // beq $1, $2, 7
	writeword(12, (2<<21) | (1<<16) | (2<<11) | FNSUB); // sub $2, $2, $1
	writeword(16, (2<<21) | (2<<16) | (3<<11) | FNADD); // add $3, $2, $2
	writeword(20, (3<<21) | (2<<16) | (4<<11) | FNAND); // and $4, $3, $2
	writeword(24, (4<<21) | (2<<16) | (5<<11) | FNOR); // or $5, $4, $2
	writeword(28, (5<<21) | (2<<16) | (6<<11) | FNSLT); // slt $6, $5, $2
	writeword(32, (OPSW<<26) | (6<<16) | 60); // sw $6, $0(60)
	writeword(36, (OPJ<<26) | 2); // j 2
	writeword(40, (OPJ<<26)); // j 0

	PC = 0;
}

void showall() {
	printf("\n");
	for(int i=0; i<MSIZE/4; i++) {
		printf("M[%d]=%d ", 4*i, readword(4*i));
	}

	printf("\n\n");

	for(int i=0; i<32; i++) {
		printf("$%d=%d ", i, R[i]);
	}
	printf("\n\nPC=%d IR=%08x\n", PC, IR);
}

int main() {

	unsigned int op, rs, rt, rd, sm, fn;
	int im, ad;

	init();

	showall();

	while(1) {
		if(PC >= MSIZE) { printf("\n!!! PC out of range !!!\n"); break; }

		printf("\nPress a key to continue ...");
		getchar();

		fetch();
		//printf("\nPC=%d IR=%08x\n", PC, IR);

		// TODO: Other fileds in the instruction
		op = GETOP(IR);
		rt = GETRT(IR);
		sm = GETSM(IR);
		im = GETIM(IR);

		switch(op) {
			case OPALU:
				switch(fn) {
					case FNADD:
						printf("\nExecuting: add $%d, $%d, $%d\n", rd, rs, rt);
						R[rd] = R[rs] + R[rt];
						break;
					case FNSUB:
						printf("\nExecuting: sub $%d, $%d, $%d\n", rd, rs, rt);
						// TODO: 减法操作
						break;
					case FNAND:
						printf("\nExecuting: and $%d, $%d, $%d\n", rd, rs, rt);
						// TODO: 与操作
						break;
					case FNOR:
						printf("\nExecuting: or $%d, $%d, $%d\n", rd, rs, rt);
						R[rd] = R[rs] | R[rt];
						break;
					case FNSLT:
						printf("\nExecuting: slt $%d, $%d, $%d\n", rd, rs, rt);
						// TODO: 比较并设置
						break;
					default:
						printf("\n!!! Unknown funct: %d !!!\n", fn);
				}
				break;
			case OPLW:
				printf("\nExecuting: lw $%d, $%d(%d)\n", rt, rs, im);
				// TODO: 从存储器读取一个字
				break;
			case OPSW:
				printf("\nExecuting: sw $%d, $%d(%d)\n", rt, rs, im);
				// TODO: 向存储器写入一个字
				break;
			case OPBEQ:
				printf("\nExecuting: beq $%d, $%d, %d\n", rs, rt, im);
				// TODO: 如果两个寄存器相等，则跳转
				break;
			case OPJ:
				printf("\nExecuting: j %d\n", ad);
				// TODO: 无条件跳转
				break;
			default:
				printf("\n!!! Unknown Opcode: %d !!!\n", op);
		}

		showall();
	}

	return 0;
}

