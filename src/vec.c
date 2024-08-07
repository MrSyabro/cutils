#include <math.h>
#include <lua.h>
#include <lauxlib.h>

static int lvec_new (lua_State *L) {
    int top = lua_gettop(L);

    lua_createtable(L, top, 0);
    luaL_getmetatable(L, "vec");
    lua_setmetatable(L, -2);

    for (int i = 1; i <= top; i++) {
        lua_pushvalue(L, i);
        lua_rawseti(L, -2, i);
    }

    return 1;
}

static int lvec_newzero (lua_State *L) {
    lua_Integer n = luaL_checkinteger(L, 1);

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    for (lua_Integer i = 1; i <= n; i++) {
        lua_pushnumber(L, 0);
        lua_rawseti(L, -2, i);
    }

    return 1;
}

static int lvec_newsingle (lua_State *L) {
    lua_Integer n = luaL_checkinteger(L, 1);

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    for (lua_Integer i = 1; i <= n; i++) {
        lua_pushnumber(L, 1);
        lua_rawseti(L, -2, i);
    }

    return 1;
}

static int lvec_add (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Unsigned n = lua_rawlen(L, 1);
    lua_Number secop, result;

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    if (lua_isnumber(L, 2)) {
        lua_Number secop = lua_tonumber(L, 2);
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 1, i);
            
            lua_Number result = lua_tonumber(L, -1) + secop;
            lua_pop(L, 1);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    } else if (lua_istable(L, 2)) {
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 2, i);

            if (lua_isnumber(L, -1)) {
                secop = lua_tonumber(L, -1);
            } else secop = 0;
            
            lua_rawgeti(L, 1, i);
            result = lua_tonumber(L, -1) + secop;
            lua_pop(L, 2);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    }

    return 1;
}

static int lvec_sub (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Unsigned n = lua_rawlen(L, 1);
    lua_Number secop, result;

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    if (lua_isnumber(L, 2)) {
        secop = lua_tonumber(L, 2);
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 1, (lua_Integer)i);
            
            result = lua_tonumber(L, -1) - secop;
            lua_pop(L, 1);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    } else if (lua_istable(L, 2)) {
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 2, i);

            if (lua_isnumber(L, -1)) {
                secop = lua_tonumber(L, -1);
            } else secop = 0;

            lua_rawgeti(L, 1, i);
            result = lua_tonumber(L, -1) - secop;
            lua_pop(L, 2);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    }

    return 1;
}

static int lvec_mul (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Unsigned n = lua_rawlen(L, 1);
    lua_Number secop, result;

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    if (lua_isnumber(L, 2)) {
        lua_Number secop = lua_tonumber(L, 2);
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 1, i);
            
            lua_Number result = lua_tonumber(L, -1) * secop;
            lua_pop(L, 1);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    } else if (lua_istable(L, 2)) {
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 2, i);
            
            if (lua_isnumber(L, -1)) {
                secop = lua_tonumber(L, -1);
            } else secop = 1;
            
            lua_rawgeti(L, 1, i);
            result = lua_tonumber(L, -1) * secop;
            lua_pop(L, 2);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    }

    return 1;
}

static int lvec_div (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Unsigned n = lua_rawlen(L, 1);
    lua_Number secop, result;

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    if (lua_isnumber(L, 2)) {
        lua_Number secop = lua_tonumber(L, 2);
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 1, i);
            
            result = lua_tonumber(L, -1) / secop;
            lua_pop(L, 1);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    } else if (lua_istable(L, 2)) {
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 2, i);

            if (lua_isnumber(L, -1)) {
                secop = lua_tonumber(L, -1);
            } else secop = 1;
            
            lua_rawgeti(L, 1, i);
            result = lua_tonumber(L, -1) / secop;
            lua_pop(L, 2);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    }

    return 1;
}

static int lvec_unm (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Unsigned n = lua_rawlen(L, 1);

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    for (lua_Unsigned i = 1; i <= n; i++) {
        lua_rawgeti(L, 1, i);
        lua_pushnumber(L, -lua_tonumber(L, -1));
        lua_rawseti(L, -3, i);
        lua_pop(L, 1);
    }

    return 1;
}

static int lvec_pow (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Unsigned n = lua_rawlen(L, 1);
    lua_Number secop, result;

    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    if (lua_isnumber(L, 2)) {
        lua_Number secop = lua_tonumber(L, 2);
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 1, i);
            
            result = pow(lua_tonumber(L, -1), secop);
            lua_pop(L, 1);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    } else if (lua_istable(L, 2)) {
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 2, i);

            if (lua_isnumber(L, -1)) {
                secop = lua_tonumber(L, -1);
            } else secop = 1;
            
            lua_rawgeti(L, 1, i);
            result = pow(lua_tonumber(L, -1), secop);
            lua_pop(L, 2);

            lua_pushnumber(L, result);
            lua_rawseti(L, -2, i);
        }
    }

    lua_settop(L, 3);

    return 1;
}

static int lvec_eq (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Unsigned n = lua_rawlen(L, 1);

    if (lua_isnumber(L, 2)) {
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 1, i);
            if (lua_compare(L, -1, -2, LUA_OPEQ) == 0) {
                lua_pushboolean(L, 0);
                return 1;
            }
            lua_pop(L, 1);
        }
    } else if (lua_istable(L, 2)) {
        for (lua_Unsigned i = 1; i <= n; i++) {
            lua_rawgeti(L, 2, i);
            lua_rawgeti(L, 1, i);
            if (lua_compare(L, -1, -2, LUA_OPEQ) == 0) {
                lua_pushboolean(L, 0);
                return 1;
            }
            lua_pop(L, 2);
        }
    }

    lua_pushboolean(L, 1);
    return 1;
}

static int lvec_lensqr (lua_State *L) {
    double result = 0;
    double tmp;
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Integer n = lua_rawlen(L, 1);
    
    for (lua_Integer i = 1; i <= n; i++) {
        lua_rawgeti(L, 1, i);
        tmp = (double)lua_tonumber(L, -1);
        result += tmp*tmp;
        lua_pop(L, 1);
    }

    lua_pushnumber(L, result);

    return 1;
}

static int lvec_len (lua_State *L) {
    lvec_lensqr(L);
    double result = lua_tonumber(L, -1);
    lua_settop(L, 1);
    lua_pushnumber(L, sqrt(result));
    return 1;
}

static int lvec_dot (lua_State *L) {
    lua_Number out = 0;
    lua_Number secop;
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TTABLE);

    lua_Unsigned n = lua_rawlen(L, 1);
    for (lua_Unsigned i = 1; i <= n; i++) {
        lua_rawgeti(L, 2, i);
        if (lua_isnumber(L, -1)) {
            secop = lua_tonumber(L, -1);
        } else secop = 0;
        lua_rawgeti(L, 1, i);
        out += lua_tonumber(L, -1) * secop;
        lua_pop(L, 2);
    }

    lua_pushnumber(L, out);

    return 1;
}

static int lvec_normalize (lua_State *L) {
    lvec_len(L);
    lvec_div(L);
    lua_pushvalue(L, -2);
    return 2;
}

static int lvec_lerp (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_Number secop, subres;
    lua_Number _param = luaL_checknumber(L, 3);
    lua_Number param = ((_param >= 1) ? 1 : ((_param <= 0) ? 0 : _param));
    lua_Unsigned n = lua_rawlen(L, 2);

    lua_pop(L, 1);
    lua_createtable(L, (int)n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    for (lua_Unsigned i = 1; i <= n; i++) {
        lua_rawgeti(L, 1, i);
        if (lua_isnumber(L, -1)) {
            secop = lua_tonumber(L, -1);
        } else secop = 0;
        lua_rawgeti(L, 2, i);

        subres = lua_tonumber(L, -1) - secop;
        lua_pop(L, 2);
        lua_pushnumber(L, secop + subres * param);
        lua_rawseti(L, -2, i);
    }

    return 1;
}

static int lvec_copy (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Integer n = (lua_Integer)lua_rawlen(L, 1);
    lua_Integer _n = n;
    if (lua_isinteger(L, 2)) {
        _n = lua_tointeger(L, 2);
    }
    n = (n < _n) ? n : _n;

    lua_createtable(L, (int)_n, 0);
    luaL_getmetatable(L, "vec");    
    lua_setmetatable(L, -2);

    for (lua_Integer i = 1; i <= n; i++) {
        lua_rawgeti(L, 1, i);
        lua_rawseti(L, -2, i);
    }

    return 1;
}

static int lvec_tostring (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Integer n = (lua_Integer)lua_rawlen(L, 1);

    luaL_Buffer out;
    luaL_buffinit(L, &out);

    luaL_addchar(&out, '[');
    for (lua_Integer i = 1; i <= n; i++) {
        lua_rawgeti(L, 1, i);
        luaL_addvalue(&out);
        if (i < n) {
            luaL_addchar(&out, ',');
            luaL_addchar(&out, ' ');
        }
    }
    luaL_addchar(&out, ']');
    luaL_pushresult(&out);

    return 1;
}

static unsigned char hexclamp(lua_Number num) {
    if (num > 255) return 255U;
    if (num < 0) return 0U;
    return (unsigned char)num;
}

static char* fmt = "%02X";
static int lvec_tohex (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Integer n = (lua_Integer)lua_rawlen(L, 1);

    unsigned char num;
    char numstr[3];
    luaL_Buffer out;
    luaL_buffinit(L, &out);

    luaL_addchar(&out, '#');
    for (lua_Integer i = 1; i <= n; i++) {
        lua_rawgeti(L, 1, i);
        num = hexclamp(lua_tonumber(L, -1));
        sprintf(numstr, fmt, num);
        luaL_addstring(&out, numstr);
    }
    luaL_pushresult(&out);

    return 1;
}

static int lvec_serialize (lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_Integer n = (lua_Integer)lua_rawlen(L, 1);

    luaL_Buffer out;
    luaL_buffinit(L, &out);

    luaL_addchar(&out, '{');
    for (lua_Integer i = 1; i <= n; i++) {
        lua_rawgeti(L, 1, i);
        luaL_addvalue(&out);
        luaL_addchar(&out, ',');
    }
    luaL_addchar(&out, '}');
    luaL_pushresult(&out);

    return 1;
}

static const struct luaL_Reg vec_m [] = {
    {"add", lvec_add}, {"__add", lvec_add},
    {"sub", lvec_sub}, {"__sub", lvec_sub},
    {"mul", lvec_mul}, {"__mul", lvec_mul},
    {"div", lvec_div}, {"__div", lvec_div},
    {"unm", lvec_unm}, {"__unm", lvec_unm},
    {"pow", lvec_pow}, {"__pow", lvec_pow},
    {"eq", lvec_eq}, {"__eq", lvec_eq},
    {"__tostring", lvec_tostring},
    {"__serialize", lvec_serialize},
    {"tohex", lvec_tohex},
    {"lensqr", lvec_lensqr},
    {"len", lvec_len},
    {"lerp", lvec_lerp},
    {"dot", lvec_dot},
    {"normalize", lvec_normalize},
    {"copy", lvec_copy},
    {NULL, NULL} /* sentinel */
};

static const struct luaL_Reg vec [] = {
    {"new", lvec_new},
    {"newzero", lvec_newzero},
    {"newsingle", lvec_newsingle},
    {"add", lvec_add},
    {"sub", lvec_sub},
    {"mul", lvec_mul},
    {"div", lvec_div},
    {"unm", lvec_unm},
    {"pow", lvec_pow},
    {"eq", lvec_eq},
    {"lensqr", lvec_lensqr},
    {"len", lvec_len},
    {"lerp", lvec_lerp},
    {"dot", lvec_dot},
    {"normalize", lvec_normalize},
    {"copy", lvec_copy},
    {"tostring", lvec_tostring},
    {"tohex", lvec_tohex},
    {NULL, NULL} /* sentinel */
};

#if defined(_WIN32) || defined(_WIN64)
__declspec(dllexport)
#endif
int luaopen_vec(lua_State *L) {
    luaL_newmetatable(L, "vec");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, vec_m, 0);
    lua_pop(L, 1); // фикс для применения в клиенте

    luaL_newlib(L, vec);

    return 1;
}

// Для подключения в другом Си коде
int luasetglobal_vec (lua_State *L) {
    luaopen_vec(L);
    lua_setglobal(L, "vec");
    
    return 0;
}