#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct INST {
        int data[16];
        size_t size;
} INST;

// Enables
const int eACC	= 0x0001; // enable accumulator register
const int eOP0	= 0x0002; // enable ALU OP 0 bit
const int eOP1	= 0x0004; // enable ALU OP 1 bit
const int ePC	= 0x0008; // enable Program Counter
const int ePCCT	= 0x0010; // enable program counter count bit
const int ePCLD	= 0x0020; // enable program counter load bit
const int eRAM	= 0x0040; // enable ram out
const int eADB	= 0x0080; // enable 16 bit alu mode
const int eSP	= 0x0100; // enable stack pointer register
const int eBP	= 0x0200; // enable base pointer register
const int eRA	= 0x0400; // enable register a
const int eRB	= 0x0800; // enable register b

// Sets
const int sACC	= 0x0001; // set accumulator register
const int sTMP	= 0x0002; // set alu tmp register
const int sMAR	= 0x0004; // set memory address register
const int sPC	= 0x0008; // set program counter
const int sPCSH	= 0x0010; // set program counter shift register
const int sSP	= 0x0020; // set stack pointer register
const int sBP	= 0x0040; // set base pointer register
const int sRAM	= 0x0080; // set ram
const int sFLG	= 0x0100; // set flag register
const int sIRSH = 0x0200; // set instruction shift register
const int sRST	= 0x0400; // set reset flag
const int sIR	= 0x0800; // set instruction register
const int sRA	= 0x1000; // set register a
const int sRB	= 0x2000; // set register b

const INST fetch = {{ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, sIR}, 5};

void writeLine(int* buffer, INST inst, int line) {
        memcpy(buffer + (16 * line), fetch.data, fetch.size); // add fetch data to buffer
        memcpy(buffer + (16 * line) + fetch.len, inst.data, inst.data); // add instruction data to buffer
}

int main() {

	int empty[] = {sRST};
    INST empty = {{sRST}, 1};

	int data[]  = {ePC|sMAR, ePCCT|sPC|eRAM|sRA, sRST};
	int store[] = {ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eRA|sRAM};
	int load[]  = {ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eRAM|sRA};

	int add[] = {eRB|sTMP, eRA|sACC, eACC|sRB};
	int and[] = {eRB|sTMP, eRA|eOP0|sACC, eACC|sRB};
	int not[] = {eRB|sTMP, eRA|eOP1|sACC, eACC|sRB};
	int cmp[] = {eRB|sTMP, eRA|eOP0|eOP1|sFLG};
	
	int jmp[] = {ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePCLD|sPC};
	int jmpc[] = {ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePC|sMAR, ePCCT|sPC|eRAM|sPCSH, ePCLD|sPC};

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

	free(dump);
	return 0;
}
