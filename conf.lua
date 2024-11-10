function love.conf(t)
    t.modules.physics = false
    t.console = true
    t.window.msaa = 4
    t.window.vsync = 1
    t.window.title = 'Geometry Solver'
    -- t.window.icon  = 'icon.png'
    t.window.resizable = true
end