#include "ppu_utils.h"
#include "log.h"
#include "math.h"

void log_tile(struct tile *tile){
	for (int i = 0; i < TILE_ROW_SIZE; ++i) {
		for (int j = 0; j < TILE_ROW_SIZE; ++j) {
			tile->pattern[i][j] ? log_info("%i", tile->pattern[i][j]) : log_info(".");
		}
		log_info("\n");
	}
}

void encode_as_tiles(byte *mem_addr, byte number_tiles, struct tile *tiles) {
	for (int i, tile_count = i = 0; tile_count < number_tiles; i+=16, ++tile_count) { //Each tile is defined by 16 bytes
		log_debug("Tile: $%02x: \n", i/16);
		for (int j = 0; j < TILE_ROW_SIZE; ++j) { //And each byte defines a row of pixels with a value from 0 to 3
			for (byte k = 0; k < TILE_COLUMN_SIZE; ++k) {
				//Get the bit j from the current iteration and 8 positions ahead. Then add those two bits so that
				//you get one of the following: 00, 01, 10, 11.
				byte most_sig_bit = (byte)bit_test(mem_addr[j+ i], k) << 1;
				byte least_sig_bit = (byte)bit_test(mem_addr[j+ i + TILE_ROW_SIZE], k);

				//use the abs to flip the tile in the Y component. Otherwise it comes out wrong.
				tiles[tile_count].pattern[j][abs(k - TILE_COLUMN_SIZE)] = most_sig_bit + least_sig_bit;
				log_debug("%i",most_sig_bit + least_sig_bit);
			}
			log_debug("\n");
		}
	}
}

struct tile nametable_tile(uint tile_id) {
	uint base_tile_addr = bit_test(rmem_b(PPUCTRL), PPUCTRL_S) ? 0x0000 : 0x1000;
	base_tile_addr += tile_id * 16;

	struct tile tile;
	encode_as_tiles(&vram_bank[base_tile_addr], 1, &tile);
	return tile;
}
