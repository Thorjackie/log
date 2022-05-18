#include <stdio.h>
#include <stdlib.h>

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

int main() {
	return 0;
}
