#ifndef NESULATOR_GUI_NAMETABLE_H
#define NESULATOR_GUI_NAMETABLE_H

#include "../utils/ppu_utils.h"

#define NAMETABLE_TEXTURE_WIDTH 256
#define NAMETABLE_TEXTURE_HEIGHT 240
#define NAMETABLE_ROWS_MAP 30
#define NAMETABLE_TILES_PER_ROW 32

FrameInfo nametable(NametableIndex index);

#endif //NESULATOR_GUI_NAMETABLE_H


