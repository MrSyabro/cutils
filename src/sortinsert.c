#include <lua.h>
#include <lauxlib.h>

static int lua_defcomp(lua_State *L) {
    int iscomp = lua_compare(L, 1, 2, LUA_OPLT);
    lua_pushboolean(L, iscomp);
    return 1;
}

static int lua_sortinser(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checkany(L, 2);
    lua_Unsigned n = lua_rawlen(L, 1);
    if (!lua_isfunction(L, 3)) {
        lua_pushcfunction(L, lua_defcomp);
    }

    for (int i = n; i >= 1; i--) {
        lua_rawgeti(L, 1, i);

        // подготавливаем стек к вызову компоратора
        lua_pushvalue(L, 3);
        lua_pushvalue(L, 2);
        lua_pushvalue(L, -3);

        lua_call(L, 2, 1);

        if (lua_toboolean(L, -1)) {
            lua_pop(L, 1);
            lua_rawseti(L, 1, i+1);
            lua_pushnil(L);
            lua_rawseti(L, 1, i);
        } else {
            lua_pop(L, 3);
            lua_rawseti(L, 1, ++i);
            lua_pushinteger(L, i);
            return 1;
        }
    }

    lua_pop(L, 1);
    lua_rawseti(L, 1, 1);
    lua_pushinteger(L, 1);
    return 1;
}

#if defined(_WIN32) || defined(_WIN64)
__declspec(dllexport)
#endif
int luaopen_sortinsert(lua_State *L) {
    lua_getglobal(L, "table");
    lua_pushcfunction(L, lua_sortinser);
    lua_setfield(L, -2, "sortinsert");

    return 0;
}
