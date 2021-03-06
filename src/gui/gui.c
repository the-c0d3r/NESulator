#include "gui.h"
#include "../cpu.h"
#include "../rom.h"
#include "../nes.h"
#include "gui_patterntable.h"
#include "gui_nametable.h"
#include "../memory.h"
#include "../ppu.h"

 int last_cpu_speed() {
	return cpu_cyclesLastSec;
}

 void gui_start_emulation(char *rom_path) {
	insertCartridge(rom_path);
	load_ROM(get_ROM());
	start_emulation();
}

 void gui_stop_emulation() {
	stop_emulation();
}

 FrameInfo gui_frame(){
	FrameInfo frameInfo = {};
	frameInfo.width = NES_SCREEN_WIDTH;
	frameInfo.height = NES_SCREEN_HEIGHT;
	frameInfo.size = frameInfo.height * frameInfo.width;
	frameInfo.buffer = ppu_back_buffer;

	return frameInfo;
}

 FrameInfo gui_left_patterntable(){
	return left_patterntable();
}

 FrameInfo gui_right_patterntable(){
	return right_patterntable();
}

 FrameInfo gui_nametable(NametableIndex index){
	return nametable(index);
}

 MemoryDumpInfo gui_ram_dump(){
	MemoryDumpInfo info = {};
	info.size = RAM_MEM_SIZE;
	info.buffer = ram_bank;

	return info;
}

 MemoryDumpInfo gui_vram_dump(){
	MemoryDumpInfo info = {};
	info.size = VRAM_MEM_SIZE;
	info.buffer = vram_bank;

	return info;
}

 void gui_cpu_speed(int speed_hertz){
	cpu_set_speed(speed_hertz);
}

/**
 * Iterates through the VRAM, where the colour palette information is stored and fills in a FrameInfo struct
 * with the RGBA colour of each position. The UI will take care of creating the images and fill them in with the colour.
 */
 FrameInfo gui_palette_dump(){
	FrameInfo info = {};
	static uint palette_buffer[32];
	info.size = 32;// Two rows of 16. Basically from 0x3F01 to 0x3F1F
	info.buffer = palette_buffer;
	info.width = 16;
	info.height = 16;

	for(uint i = 0; i < info.size; ++i){
		int colour_index = rmem_b_vram(i + UNIVERSAL_BACKGROUND_ADDR);
		palette_buffer[i] = encode_as_RGBA(COLOUR_PALETTE[colour_index]);
	}

	return info;
}
