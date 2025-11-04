#pragma once

#include <iostream>
#include <vector>
#include "Vec2.h"

class Snake
{
    private:
        std:::vector<vec2i> body;
        vec2i direction;
        bool grow;
    
    public:
        Snake();
        void move();
        void move();
        void setDirection(const vec2i& dir);
        void growNext();
        bool checkCollision() const;
        const std::vector<vec2i>& getBody() const;
};
