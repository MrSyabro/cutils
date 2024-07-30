require "sortinsert"
assert(type(table.sortinsert) == "function")

local t = {2,3,5,6}

table.sortinsert(t, 4)
assert(t[3] == 4)

table.sortinsert(t, 1)
assert(t[1] == 1)

t = {5, 4, 2, 1}

table.sortinsert(t, 3, function(a,b) return a > b end)
assert(t[3] == 3)
