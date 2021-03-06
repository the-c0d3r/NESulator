#include "CNROM.h"
#include "../memory.h"

static uint first_rom_page = 0x8000;
static uint second_rom_page = 0xC000;
static uint prg_ram = 0x6000;

void mapper3(ROM *rom) {
	for (int i = 0; i < PRG_PAGE_SIZE; ++i) {
		wmem_b(first_rom_page + i, rom->prgROM[i]);
	}

	uint mirror_starting_point = rom->numPRGPages == 1 ? 0 : PRG_PAGE_SIZE;

	//If there's more than one 16Kb pages, then copy everything, otherwise mirror what was copied on the first loop
	for (int i = 0; i < PRG_PAGE_SIZE; ++i) {
		wmem_b(second_rom_page + i, rom->prgROM[i + mirror_starting_point]);
	}
	// TODO CHR stuff goes here
}
