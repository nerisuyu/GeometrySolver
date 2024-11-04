local ffi = require("ffi")
local input = {
    shift = false
}
local dialog = { }

function love.load()
    ffi.cdef[[
      char* Dialog_OpenFile();
      char* Dialog_SaveAsFile();
    ]]
    dialog = ffi.load("./windialog")
end

function love.update(dt)
    
end

function love.draw()
    love.graphics.print('Test', 0, 0)
end

function love.keypressed(key)
    if key == 'rshift' or key == 'lshift' then input.shift = true end
    
    if input.shift then
        if     key == 'o' then
            ffi.string(dialog.Dialog_OpenFile())
        elseif key == 's' then
            ffi.string(dialog.Dialog_SaveAsFile())
        end
    end
end

function love.keyreleased(key)
    if key == 'rshift' or key == 'lshift' then input.shift = false end
end