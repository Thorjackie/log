#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME "output_rom"

const int sRA	= pow(2, 0);
const int shl	= pow(2, 1);
const int sSP	= pow(2, 2);
const int sPC	= pow(2, 3);
const int sMB	= pow(2, 4);
const int sRST	= pow(2, 5);
const int sFLG	= pow(2, 6);
const int sTMP	= pow(2, 7);
const int sACC	= pow(2, 8);
const int sRAM	= pow(2, 9);
const int sIR	= pow(2, 10);
const int sBUS	= pow(2, 11);

const int eRA	= pow(2, 12);
const int ehl	= pow(2, 13);
const int HLsel	= pow(2, 14);
const int eSP	= pow(2, 15);
const int ePC	= pow(2, 16);
const int ePCct	= pow(2, 17);
const int ePCld	= pow(2, 18);
const int eMB	= pow(2, 19);
const int eMBct	= pow(2, 20);
const int eMBld	= pow(2, 21);
const int OP2	= pow(2, 22);
const int OP1	= pow(2, 23);
const int OP0	= pow(2, 24);
const int eFLG	= pow(2, 25);
const int eALU	= pow(2, 26);
const int eACC	= pow(2, 27);
const int eRAM	= pow(2, 28);
const int eHL	= pow(2, 29);

const int PCinc = ePCct|sPC;
const int PCdec = ePCct|ePCld|sPC;
const int PCld 	= ePCld|sPC;

const int MBinc = eMBct|sMB;
const int MBdec = eMBct|eMBld|sMB;
const int MBld	= eMBld|sMB;





const int load_acc[16] = {
	ePC|PCinc|eRAM|sIR,
	eRA|sACC,
	sRST
};
const int stor_reg[16] = {
	ePC|PCinc|eRAM|sIR,
	eACC|sRA,
	sRST
};
const int load_imm[16] = {
	ePC|PCinc|eRAM|sIR,
	ePC|PCinc|eRAM|sRA,
	sRST
};

void writeInst(FILE* file, const int* instruction) {
	for (int i = 0; i < 16; i++) {
		if (instruction[i] > 0) {
			fprintf(file, "%d ", instruction[i]);
		} else {
			fprintf(file, "%d*0", 16 - i);
			break;
		}
	}
	fprintf(file, "\n");
}

int main() {

	FILE* output = NULL;

	output = fopen(FILENAME, "w");
	if (!output) {
		printf("error opening file: %s\n", FILENAME);
	}
	fprintf(output, "v2.0 raw\n");
	writeInst(output, load_acc);
	writeInst(output, stor_reg);
	writeInst(output, load_imm);

	fclose(output);
	return 0;
}
