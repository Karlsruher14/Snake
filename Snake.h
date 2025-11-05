#pragma once

#include <iostream>
#include <vector>
#include "Vec2.h"

class Snake
{
    private:
        std::vector<vec2> body;
        vec2 direction;
        bool grow;
    
    public:
        Snake();
        void move();
        void setDirection(const vec2& dir);
        void growNext();
        bool checkCollision() const;
        const std::vector<vec2>& getBody() const;
};
