#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct INST {
        int data[16];
        size_t size;
	int len;
} INST;

// Enables
const int eACC	= 0x00010000; // enable accumulator register
const int eOP0	= 0x00020000; // enable ALU OP 0 bit
const int eOP1	= 0x00040000; // enable ALU OP 1 bit
const int ePC	= 0x00080000; // enable Program Counter
const int ePCCT	= 0x00100000; // enable program counter count bit
const int ePCLD	= 0x00200000; // enable program counter load bit
const int eRAM	= 0x00400000; // enable ram out
const int eADB	= 0x00800000; // enable 16 bit alu mode
const int eSP	= 0x01000000; // enable stack pointer register
const int eBP	= 0x02000000; // enable base pointer register
const int eRA	= 0x04000000; // enable register a
const int eRB	= 0x08000000; // enable register b

// Sets
const int sACC	= 0x00000001; // set accumulator register
const int sTMP	= 0x00000002; // set alu tmp register
const int sMAR	= 0x00000004; // set memory address register
const int sPC	= 0x00000008; // set program counter
const int sPCSH	= 0x00000010; // set program counter shift register
const int sSP	= 0x00000020; // set stack pointer register
const int sBP	= 0x00000040; // set base pointer register
const int sRAM	= 0x00000080; // set ram
const int sFLG	= 0x00000100; // set flag register
const int sIRSH = 0x00000200; // set instruction shift register
const int sRST	= 0x00000400; // set reset flag
const int sIR	= 0x00000800; // set instruction register
const int sRA	= 0x00001000; // set register a
const int sRB	= 0x00002000; // set register b

const int fetch[] = {ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, sIR};
const int fetch_size = sizeof fetch;

void writeLine(int* buffer, int* inst, int line, size_t inst_size) {
	memcpy(buffer + (16 * line), fetch, fetch_size);
	memcpy(buffer + (16 * line) + (fetch_size / sizeof(int)), inst, inst_size);
}

int main() {

	int empty[] = {sRST};

	int data[]  = {ePC|sMAR, ePCCT|sPC|eRAM|sRA, sRST};
	int store[] = {ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eRA|sRAM, sRST};
	int load[]  = {ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eRAM|sRA, sRST};

	int add[] = {eRB|sTMP, eRA|sACC, eACC|sRB, sRST};
	int and[] = {eRB|sTMP, eRA|eOP0|sACC, eACC|sRB, sRST};
	int not[] = {eRB|sTMP, eRA|eOP1|sACC, eACC|sRB, sRST};
	int cmp[] = {eRB|sTMP, eRA|eOP0|eOP1|sFLG, sRST};
	
	int jmp[] = {ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePCLD|sPC, sRST};
	int jmpc[] = {ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePCLD|sPC, sRST};

	int* dump = malloc(16*128*sizeof(int));

    for (int i = 0; i < 128; i++) {
            writeLine(dump, empty, i, sizeof empty);
    }

	writeLine(dump, empty, 0, sizeof empty);
	writeLine(dump, data, 1, sizeof data);
	writeLine(dump, store, 2, sizeof store);
	writeLine(dump, load, 3, sizeof load);
	writeLine(dump, add, 4, sizeof add);
	writeLine(dump, and, 5, sizeof and);
	writeLine(dump, not, 6, sizeof not);
	writeLine(dump, cmp, 7, sizeof cmp);
	writeLine(dump, jmp, 8, sizeof jmp);

	writeLine(dump, empty, 64, sizeof empty);
	writeLine(dump, data, 65, sizeof data);
	writeLine(dump, store, 66, sizeof store);
	writeLine(dump, load, 67, sizeof load);
	writeLine(dump, add, 68, sizeof add);
	writeLine(dump, and, 69, sizeof and);
	writeLine(dump, not, 70, sizeof not);
	writeLine(dump, cmp, 71, sizeof cmp);
	writeLine(dump, jmp, 72, sizeof jmp);
    	writeLine(dump, jmpc, 73, sizeof jmpc);


	FILE* output = fopen("rom.dump", "w");
	if (!output) {
		printf("error opening file\n");
	}
	fprintf(output, "v2.0 raw\n");
	for (int i = 0; i < 16 * 128; i++) {
		if (i % 16 == 0) {
			fprintf(output, "\n%x ", dump[i]);
		} else {
			fprintf(output, "%x ", dump[i]);
		}
	}
	fprintf(output, "\n");

	fclose(output);
	free(dump);
	return 0;
}
