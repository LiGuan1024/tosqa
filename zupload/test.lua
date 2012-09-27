#!/usr/bin/env lua

local zapi = require 'zapi'

print(1, table.concat(zapi:version(),'.'))
print(2, zapi:sum(1,2))

local fd = assert(io.open('blink1.bin', 'rb'))
local data = fd:read('*a')
fd:close()

print(3, zapi:upload2lpc(data))

os.execute('sleep 10')

local fd = assert(io.open('blink2.bin', 'rb'))
local data = fd:read('*a')
fd:close()

print(4, zapi:upload2lpc(data))
