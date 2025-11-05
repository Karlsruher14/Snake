
#include <iostream>
#include <vector>
#include "Vec2.h"
#include "Snake.h"

Snake::Snake() : direction{1.0f,0.0f}
{
    body.push_back(vec2{5.0f,5.0f});
    
}

void Snake::move()
{
    vec2 head = body.front();
    vec2 newHead = head + direction;
    body.insert(body.begin(), newHead);

    if (!grow)
        body.pop_back();
    grow = false;
}

const std::vector<vec2>& Snake::getBody() const
{
    return body;
}
