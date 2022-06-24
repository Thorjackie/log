#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME "rom.dump"
#define INST_SIZE 16

const int sRA	= 0x1;
const int shl	= 0x2;
const int sSP	= 0x4;
const int sPC	= 0x8;
const int sMB	= 0x10;
const int sRST	= 0x20;
const int sFLG	= 0x40;
const int sTMP	= 0x80;
const int sACC	= 0x100;
const int sRAM	= 0x200;
const int sIR	= 0x400;
const int sBUS	= 0x800;

const int eRA	= 0x1000;
const int ehl	= 0x2000;
const int HLsel	= 0x4000;
const int eSP	= 0x8000;
const int ePC	= 0x10000;
const int ePCct	= 0x20000;
const int ePCld	= 0x40000;
const int eMB	= 0x80000;
const int eMBct	= 0x100000;
const int eMBld	= 0x200000;
const int OP2	= 0x400000;
const int OP1	= 0x800000;
const int OP0	= 0x1000000;
const int eFLG	= 0x2000000;
const int eALU	= 0x4000000;
const int eACC	= 0x8000000;
const int eRAM	= 0x10000000;
const int eHL16	= 0x20000000;
const int e16t	= 0x40000000;

const int PCinc = ePCct|sPC;
const int PCdec = ePCct|ePCld|sPC;
const int PCld 	= ePCld|sPC;

const int MBinc = eMBct|sMB;
const int MBdec = eMBct|eMBld|sMB;
const int MBld	= eMBld|sMB;

const int sL = shl;
const int eL = ehl;
const int sH = shl | HLsel;
const int eH = ehl | HLsel;
const int sHL = shl;
const int eHL = eHL16 | ehl;

const int ALU_ADD = 0;
const int ALU_SUB = OP0;

const int insts[][INST_SIZE] = {
    { // empty
        ePC|PCinc|eRAM|sIR,
        sRST
    },
    { // load acc <- reg
	    ePC|PCinc|eRAM|sIR,
	    eRA|sACC,
	    sRST
    },
    { // load reg <- acc
	    ePC|PCinc|eRAM|sIR,
	    eACC|sRA,
	    sRST
    },
    { // load reg <- imm
	    ePC|PCinc|eRAM|sIR,
	    ePC|PCinc|eRAM|sRA,
	    sRST
    },
    { // load reg <- *imm
	    ePC|PCinc|eRAM|sIR, 
	    ePC|PCinc|eRAM|sH,
	    ePC|PCinc|eRAM|sL,
	    eHL|eRAM|sRA,
	    sRST
    },
    { // load reg <- *(*sp - *imm)
	    ePC|PCinc|eRAM|sIR, 
	    eSP|e16t|sHL,
	    eH|sACC,
	    ePC|PCinc|eRAM|sTMP,
	    ALU_SUB|eALU|sFLG|sH,
	    eL|sACC,
	    ePC|PCinc|eRAM|sTMP,
	    ALU_SUB|eFLG|eALU|sL,
	    eHL|eRAM|sRA,
	    sRST
    },
    { // store reg -> *imm
	    ePC|PCinc|eRAM|sIR,
	    ePC|PCinc|eRAM|sH,
	    ePC|PCinc|eRAM|sL,
	    eHL|eRA|sRAM,
	    sRST
    },
    { // store reg -> *(sp - imm)
	    ePC|PCinc|eRAM|sIR, 
	    eSP|e16t|sHL,
	    eH|sACC,
	    ePC|PCinc|eRAM|sTMP,
	    ALU_SUB|eALU|sFLG|sH,
	    eL|sACC,
	    ePC|PCinc|eRAM|sTMP,
	    ALU_SUB|eFLG|eALU|sL,
	    eHL|eRA|sRAM,
	    sRST
    }

};

void writeInsts(FILE* file, const int instructions[][16], int size, int inst_size) {
    for (int inst_num = 0; inst_num < size; inst_num++) {
        for (int index = 0; index < inst_size; index++) {
            if (instructions[inst_num][index] > 0) {
                fprintf(file, "%x ", instructions[inst_num][index]);
            } else {
                fprintf(file, "%d*0", 16 - index);
                break;
            }
        }
        fprintf(file, "\n");
    }
}

int main() {

	FILE* output = NULL;
    int size = (int) sizeof insts / sizeof insts[0];

	output = fopen(FILENAME, "w");
	if (!output) {
		printf("error opening file: %s\n", FILENAME);
	}
    fprintf(output, "v2.0 raw\n");
    writeInsts(output, insts, size, INST_SIZE);

	fclose(output);
	return 0;
}
