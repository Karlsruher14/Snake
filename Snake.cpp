
#include <iostream>
#include <vector>
#include "Vec2.h"
#include "Snake.h"

Snake::Snake() 
{
    direction = vec2i{1,0};
    body.push_back(vec2i{5,5});
    
}

void Snake::move()
{
    vec2i head = body.front();
    vec2i newHead = head + direction;
    body.insert(body.begin(), newHead);

    if (!grow)
        body.pop_back();
    grow = false;
}
