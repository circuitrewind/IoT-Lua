#ifndef __LUA_ARDUINO_H__
#define __LUA_ARDUINO_H__



#include <pgmspace.h>
#include "luaconf.h"



LUA_API const char *lua_flash_allocate(const char *item);
LUA_API void lua_flash_free();

#define LUASTR(x) (lua_flash_allocate(PSTR(x)))



#endif // __LUA_ARDUINO_H__
