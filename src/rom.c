#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cmd {
	int pos;
	char* name;
};

struct cmd Sets[] = {
	{0x00000001, "sACC"},	// Set Accumulator
	{0x00000002, "sRGS"},	// Set Register Store
	{0x00000004, "sIR"},	// Set Instruction Register
	{0x00000008, "sSHF"},	// Set Program Counter Shift
	{0x00000010, "sPC"},	// Set Program Counter
	{0x00000020, "sMAR"},	// Set Memory Address Register
	{0x00000040, "sRAM"},	// Set RAM
	{0x00000080, "sTMP"},	// Set ALU TMP Register
	{0x00000100, "sREG"}	// Set Register
};

struct cmd Enables[] = {
	{0x00000001, "eACC"},	// Enable Accumulator
	{0x00000002, "eCT"},	// Enable CT PC Var
	{0x00000004, "eLD"},	// Enable LD PC Var
	{0x00000008, "ePC"},	// Enable PC
	{0x00000010, "eRAM"},	// Enable RAM
	{0x00000020, "eCRY"},	// Enable Carry In
	{0x00000040, "eOP0"},	// Enable OP0
	{0x00000080, "eOP1"},	// Enable OP1
	{0x00000100, "eREG"}	// Enable Register
};

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


int main() {
	int fetch[] = {
		ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, ePC|sMAR, ePCCT|sPC|eRAM|sIRSH, sIR
	};
	int data[] = {
		ePC|sMAR, ePCCT|sPC|eRAM|sREG, sRST
	};
	int store[] = {
		ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eREG|sRAM
	}
	int load[] = {
		ePC|sMAR, ePCCT|sPC|eRAM|eADB|sTMP, eSP|eADB|sACC, eACC|eADB|sMAR, eRAM|sREG
	};
	int cmp[] = {
		eREG
	int add[];
	int not[];
	int and[];
	int jmp[];
	int jmpc[];

	int* data_inst = calloc(16, sizeof(int));
	if (data_inst == NULL) {
		fprintf(stderr, "calloc returned (NULL)!\n");
		exit(EXIT_FAILURE);
	}
	memcpy(data_inst, fetch, 5 * sizeof(int));
	for (int i = 0; i < 5; i++) {
		printf("%x ", data_inst[i]);
	}
	printf("\n");
	memcpy(&data_inst[5], data, 3 * sizeof(int));
	for (int i = 0; i < 8; i++) {
		printf("%x ", data_inst[i]);
	}
	printf("\n");

	free(data_inst);
	return 0;
}
