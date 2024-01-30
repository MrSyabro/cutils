local lm = require "luamake"
lm:lua_dll "vec" {
    sources = "src/vec.c"
}

lm:lua_dll "createtable" {
    sources = "src/createtable.c"
}