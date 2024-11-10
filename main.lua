local ffi = require("ffi")
local core = require("wrapper")
local input = {
    shift = false,
    ctrl  = false,
    click = {x = 0, y = 0, button = -1, dwx = 0, dwy = 0, isMoved = false}
}
local nearest_point = -1
local selected_points = {}

local palette = require("palettes").std

function love.load()
    core.Drawing_Init()
end

function love.quit()
    core.Drawing_Free()
end

function love.update(dt)
    
end


function love.draw()
    love.graphics.clear(palette.background[1]/255, palette.background[2]/255, palette.background[3]/255)
    local point_count = core.PointsCount()
    love.graphics.setColor(palette.geometry[1]/255, palette.geometry[2]/255, palette.geometry[3]/255)
    for i=1,point_count do
        local point = core.GetPoint(i-1)
        local x, y = fromDrawingSpaceToScreenSpace(point.x, point.y)
        love.graphics.circle('fill', x, y, 3)
    end
    local line_count = core.LinesCount()
    for i=1,line_count do
        local line = core.GetLine(i-1)
        local p1 = core.GetPoint(line.point1)
        local p2 = core.GetPoint(line.point2)
        local x1, y1 = fromDrawingSpaceToScreenSpace(p1.x, p1.y)
        local x2, y2 = fromDrawingSpaceToScreenSpace(p2.x, p2.y)
        love.graphics.line(x1, y1, x2, y2)
    end
    for i=1,#selected_points do
        local point = core.GetPoint(selected_points[i])
        local x, y = fromDrawingSpaceToScreenSpace(point.x, point.y)
        love.graphics.setColor(palette.selected[1]/255, palette.selected[2]/255, palette.selected[3]/255)
        love.graphics.circle('fill', x, y, 3)
    end
    
    if nearest_point > -1 then
        love.graphics.setColor(palette.nearest[1]/255, palette.nearest[2]/255, palette.nearest[3]/255)
        local point = core.GetPoint(nearest_point)
        local x, y = fromDrawingSpaceToScreenSpace(point.x, point.y)
        love.graphics.circle('fill', x, y, 3)
    end
    love.graphics.setColor(palette.text[1]/255, palette.text[2]/255, palette.text[3]/255)
    love.graphics.print(point_count, 0, 0)
end

function love.keypressed(key)
    if key == 'rshift' or key == 'lshift' then input.shift = true end
    if key == 'rctrl'  or key == 'lctrl'  then input.ctrl  = true end
    if key == 'f' then
        if #selected_points == 2 then
            core.AddLine(selected_points[1], selected_points[2])
        end
    end
    
    --if input.ctrl then
    --    if     key == 'o' then
    --        ffi.string(dialog.Dialog_OpenFile())
    --    elseif key == 's' then
    --        ffi.string(dialog.Dialog_SaveAsFile())
    --    end
    --end
end

function love.keyreleased(key)
    if key == 'rshift' or key == 'lshift' then input.shift = false; selected_points = {} end
    if key == 'rctrl'  or key == 'lctrl'  then input.ctrl  = false end
end

local camera_x = 20;
local camera_y = 10;
local px_per_mm = 100;
local win_height = love.graphics.getHeight
local win_width = love.graphics.getWidth

function fromDrawingSpaceToScreenSpace(x, y)
    x = (x - camera_x) * px_per_mm + win_width()  / 2
    y = (y - camera_y) * px_per_mm + win_height() / 2
    return x, y
end

function fromScreenSpaceToDrawingSpace(x, y)
    x = (x - win_width()  / 2) / px_per_mm + camera_x
    y = (y - win_height() / 2) / px_per_mm + camera_y
    return x, y
end

function love.mousepressed(x, y, button)
    input.click.x = x
    input.click.y = y
    input.click.button = button
    input.click.dwx, input.click.dwy = fromScreenSpaceToDrawingSpace(x, y)
    input.click.isMoved = false
    if nearest_point ~= -1 then
        for i=1,#selected_points do
            if selected_points[i] == nearest_point then return end
        end
        table.insert(selected_points, nearest_point)
    end
end

function love.mousemoved(x, y, dx, dy)
    input.click.isMoved = true
    local dwx, dwy = fromScreenSpaceToDrawingSpace(x, y)
    local value = core.GetNearestPointIndex(dwx, dwy)
    if value.distance < 0.0025 * px_per_mm then
        nearest_point = value.index
    else
        nearest_point = -1
    end
    
    if #selected_points > 0 and input.click.button == 1 then
        local ddwx = dwx - input.click.dwx
        local ddwy = dwy - input.click.dwy
        for i=1,#selected_points do
            core.MovePoint(ddwx, ddwy, selected_points[i])
        end
        input.click.dwx = dwx
        input.click.dwy = dwy
    end
end

function love.mousereleased(x, y, button)
    if not input.click.isMoved then
        if input.click.button == 1 then
            if nearest_point == -1 and #selected_points == 0 then
                local x, y = fromScreenSpaceToDrawingSpace(x, y)
                nearest_point = core.AddPoint(x, y)
            end
        elseif input.click.button == 2 then
            if nearest_point ~= -1 then
                core.RemovePoint(nearest_point)
                nearest_point = -1
            end
        end
    end
    if not input.shift then selected_points = {} end
    input.click.button = -1
end