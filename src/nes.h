#ifndef NESULATOR_NES_H
#define NESULATOR_NES_H

#include "gui/mainWindow.h"
#include "log.h"
#include "cpu.h"
#include "ppu.h"
#include "rom.h"
#include "apu.h"
#include <stdio.h>

int stop_emulation(SDL_Event);

//So that SDL stops complaining
#undef main

int main();

void register_events();
void cleanup_events();

#endif //NESULATOR_NES_H
