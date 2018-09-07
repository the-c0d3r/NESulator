#ifndef NESULATOR_PATTERNTABLEVIEWER_H
#define NESULATOR_PATTERNTABLEVIEWER_H

#include "gui.h"
#include "../utils/ppu_utils.h"
#include "../memory.h"

#define PATTERNTABLE_WINDOW_WIDTH 512
#define PATTERNTABLE_WINDOW_HEIGHT 512
#define PATTERNTABLE_TEXTURE_WIDTH 128
#define PATTERNTABLE_TEXTURE_HEIGHT 128
#define PATTERNTABLE_WINDOW_TITLE "Patterntable Viewer"

struct patterntable_viewer_window {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *back_buffer_tex;
	int refresh_rate;
};

int build_patterntable_viewer(int refresh_rate);

int on_quit_patterntable_viewer_window(SDL_Event);

int cycle_patterntable_viewer();

#endif //NESULATOR_PATTERNTABLEVIEWER_H