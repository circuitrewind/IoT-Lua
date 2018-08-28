#include <stdlib.h>
#include "arduino.h"




////////////////////////////////////////////////////////////////////////////////
//LINKED LIST WITH A STRING BUFFER ATTACHED
////////////////////////////////////////////////////////////////////////////////
typedef struct lua_flash_string {
	lua_flash_string *next;
	char buffer[];
} lua_flash_string;




////////////////////////////////////////////////////////////////////////////////
//REFERENCE TO THE FIRST STRING IN RAM
////////////////////////////////////////////////////////////////////////////////
static lua_flash_string *lua_flash_first = nullptr;




////////////////////////////////////////////////////////////////////////////////
//COPY A STRING FROM FLASH INTO RAM
////////////////////////////////////////////////////////////////////////////////
LUA_API const char *lua_flash_allocate(const char *string) {
	auto len			= strlen_P(string);
	auto item			= (lua_flash_string*) malloc(len + sizeof(lua_flash_string) + 1);

	if (!item) return "";

	item->next			= nullptr;
	memcpy_P(item->buffer, string, len);
	item->buffer[len]	= '\0';

	if (lua_flash_first) {
		lua_flash_string	*tmp = lua_flash_first;
		while (tmp->next)	 tmp = tmp->next;
		tmp->next = item;
	} else {
		lua_flash_first	= item;
	}

	return item->buffer;
}




////////////////////////////////////////////////////////////////////////////////
//FREE ALL COPIED STRINGS FROM RAM
////////////////////////////////////////////////////////////////////////////////
LUA_API void lua_flash_free() {
	while (lua_flash_first) {
		lua_flash_string *next = lua_flash_first->next;
		free(lua_flash_first);
		lua_flash_first = next;
	}
}
