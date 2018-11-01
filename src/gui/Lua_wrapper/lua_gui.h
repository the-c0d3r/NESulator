#ifndef NESULATOR_GUI
#define NESULATOR_GUI

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "../../nes.h"
#include "../../rom.h"
#include "../../utils/ppu_utils.h"
#include "../gui.h"


int luaopen_GUItulator (lua_State *L);

static int open_rom(lua_State *state);

static int get_cycle_count();

static int stop_backgroumd_emulation(lua_State *state);

static int get_patterntable(lua_State *state);

static int get_patterntable_pixel(lua_State *state);

#endif //NESULATOR_GUI