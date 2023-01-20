Flag = Class{}

function Flag:init(map)

    self.map = map

    self.x = (map.mapWidth - 5) * map.tileWidth
    self.y = (map.mapHeight / 2 - 4) * map.tileHeight

    -- animation frames
    self.frames = {}

    -- current animation frame
    self.currentFrame = nil

    -- used to determine behavior and animations
    self.state = 'idle'

    self.texture = love.graphics.newImage('graphics/spritesheet.png')
    
    --self.map:setTile(self.x, self.y, FLAG1)

    self.animations = {
        ['idle'] = Animation({
            texture = self.texture,
            frames = {
                love.graphics.newQuad(0, 48, 16, 16, self.texture:getDimensions()),
                love.graphics.newQuad(16, 48, 16, 16, self.texture:getDimensions()),
                love.graphics.newQuad(16, 48, 16, 16, self.texture:getDimensions())
            },
            interval = 0.2
        }),
        ['falling'] =  Animation({
            texture = self.texture,
            frames = {
                love.graphics.newQuad(32, 48, 16, 16, self.texture:getDimensions())
            }
        })
    }

    -- Initialize animation
    self.animation = self.animations['idle']
    self.currentFrame = self.animation:getCurrentFrame()

end

function Flag:update(dt)
    self.animation:update(dt)
    self.currentFrame = self.animation:getCurrentFrame()
end

function Flag:render()
    love.graphics.draw(self.texture, self.currentFrame, self.x, self.y)
end
