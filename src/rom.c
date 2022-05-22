#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE(X) (16*X)

// Enables
const int eACC	= 0x0001;
const int eOP0	= 0x0002;
const int eOP1	= 0x0004;
const int ePC	= 0x0008;
const int ePCCT	= 0x0010;
const int ePCLD	= 0x0020;
const int eRAM	= 0x0040;
const int eADB	= 0x0080;
const int eSP	= 0x0100;
const int eBP	= 0x0200;
const int eRA	= 0x0400;
const int eRB	= 0x0800;

// Sets
const int sACC	= 0x0001;
const int sTMP	= 0x0002;
const int sMAR	= 0x0004;
const int sPC	= 0x0008;
const int sPCSH	= 0x0010;
const int sSP	= 0x0020;
const int sBP	= 0x0040;
const int sRAM	= 0x0080;
const int sFLG	= 0x0100;
const int sIRSH = 0x0200;
const int sRST	= 0x0400;
const int sIR	= 0x0800;
const int sRA	= 0x1000;
const int sRB	= 0x2000;

void writeLine(int* buffer, int* data, int line, size_t len) {
	int fetch[] = {ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, sIR}; // fetch
	memcpy(buffer + 16 * line, fetch, sizeof fetch);
	memcpy(buffer + 16 * line + 5, data, len);
}


int main() {

	int insts[][16] = {
		{ePC|sMAR, ePCCT|sPC|eRAM|sRA, sRST}, // data
		//{ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eREG|sRAM}, // store
		//{ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eRAM|sREG} // load
	};
	//int cmp[]
	//int add[]
	//int not[]
	//int and[]
	//int jmp[]
	//int jmpc[]
	int* dump = calloc(16*9, sizeof(int)); // steps * instructions	
	writeLine(dump, insts[0], 1, sizeof insts[0]);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++) {
			printf("%x ", dump[j * i]);
		}
		printf("\n");
	}

	for (int i = 0; i < 16*9; i++ ) {
		printf("%x\n", dump[i]);
	}
	free(dump);
	return 0;
}
