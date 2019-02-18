#ifndef NESULATOR_PPU_H
#define NESULATOR_PPU_H

#include "utils/Utils.h"

typedef enum bg_byte{low, high} bg_byte;
typedef enum scanline_type { Visible, NMI, Pre, Post } scanline_type;

extern word c_vram; /** Current vram address */
extern word t_vram; /** Temporary vram address aka address of the top left onscreen tile */
extern byte x; /** Fine X scroll, 3 bits */
extern bool w; /** Latch, 1 bit */
extern int current_scanline;
extern int ppu_cycle_per_cpu_cycle;
//extern int warmup_cycles_count;
extern uint ppu_back_buffer[];

#define PPUCTRL 0x2000
#define PPUMASK 0x2001
#define PPUSTATUS 0x2002
#define OAMADDR 0x2003
#define OAMDATA 0x2004
#define PPUSCROLL 0x2005
#define PPUADDR 0x2006
#define PPUDATA 0x2007
#define OAMDMA 0x4014
#define PPU_SCANLINES 261
#define PPU_VISIBLE_SCANLINES 240
#define TILES_PER_SCANLINE 32
#define PPU_CYCLES_PER_SCANLINE 341
#define NES_PPU_TEXTURE_HEIGHT 240
#define NES_PPU_TEXTURE_WIDTH 256

static enum {
	PPUCTRL_N = 0, PPUCTRL_I = 2, PPUCTRL_S = 3, PPUCTRL_B = 4, PPUCTRL_H = 5, PPUCTRL_P = 6, PPUCTRL_V = 7
} PPUCTRL_FLAGS;

#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#define TILES_PER_TABLE 0xFF
#define PPU_PATTERN_LEFT vram_bank[0x0000]
#define PPU_PATTERN_RIGHT vram_bank[0x1000]

typedef enum {
	NT_TOP_LEFT, NT_TOP_RIGHT, NT_BOTTOM_LEFT, NT_BOTTOM_RIGHT
} NametableIndex;

typedef enum {
	AT_TOP_LEFT, AT_TOP_RIGHT, AT_BOTTOM_LEFT, AT_BOTTOM_RIGHT
} AttributeTableIndex;

/**
 * Memory addresses for the Background palettes. These are the entry points and each palette holds 3 colours
 */
extern word BACKGROUND_PALETTES[4];
extern word UNIVERSAL_BACKGROUND;

typedef struct{
	/**
	 * matrix of numbers from 0 to 3. Defines the shape of the tile
	 */
	byte pattern[TILE_WIDTH][TILE_HEIGHT];
} tile;

/**
 * Starting at "start_pos" encodes the next "number_tiles" as a pattern table.
 *
 * That is in blocks of 16 bytes and performing the left + right sum to obtain numbers from 0 to 3.
 */
void encode_as_tiles(byte *mem_addr, uint number_tiles, tile *tiles);

tile nametable_tile(byte tile_id);

/**
 * Uses the current mirroring to return the start address of the nametable index
 * i.e. NT_TOP_RIGHT would be 0x2000 with horizontal mirroring or 0x2400 with vertical mirroring.
 */
word get_nt_start_addr(NametableIndex nametableIndex);

word get_at_start_addr(AttributeTableIndex attributeTableIndex);

byte get_attribute(NametableIndex nametableIndex, int row_id, int column_id);

colour *get_background_palette(byte attribute);

/**
 * Executes an instruction on the PPU.
 * Still to be defined what it means and what it needs to be happen on each cycle
 */
int ppu_cycle();

void ppu_power_up(int clock_speed);

void write_PPUADDR(byte value);

void write_PPUDATA(byte value);

void write_PPUCTRL(byte value);

void write_PPUSCROLL(byte value);

byte read_PPUDATA();

byte read_PPUSTATUS();

/**
 * Checks for the correct conditions to trigger an nmi. If they are met, then it triggers it
 */
void trigger_nmi();

/**
 * Fetches the current Nametable Byte. Returns the addr to find the nt_byte
 */
word nt_byte();

/**
 * Fetches the current Attribute Table byte. Places it into the internal latch at_byte
 */
void fetch_at_byte();

/**
 * Fetches the low or high byte for the current tile. Places it into the internal latch
 */
void fetch_bg_tile(bg_byte high_low);

void store_tile_data(word addr, word at_addr);

/**
 * Executes the actual PPU logic for the current cycle.
 */
void step(scanline_type s_type);

/**
 * Runs a single PPU Scanline
 */
void ppu_scanline();

void ppu_run(int cpu_cycles_since_last_tick);

#endif //NESULATOR_PPU_H
