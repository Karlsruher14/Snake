#include <iostream>
#include <vector>

std::vector<vec2> GetCellVertices(float x, float y, int SCRWIDTH, int SCRHEIGHT, float GRIDCOLS, float GRIDROWS)
{
    float cellW = SCRWIDTH / GRIDCOLS;
    float cellH = SCRHEIGHT / GRIDROWS;

    float pixelX = x * cellW;
    float pixelY = y * cellH;

    float ndcX = (pixelX / SCRWIDTH) * 2 - 1;
    float ndcY = (pixelY / SCRHEIGHT) * 2 - 1;

    float hNDC = (cellH / SCRHEIGHT) * 2;
    float wNDC = (cellW / SCRWIDTH) * 2;

    //lower left corner
    vec2 llCorner(ndcX, ndcY);

    //lower right corner
    vec2 lrCorner(ndcX + wNDC, ndcY);

    //upper right corner
    vec2 urCorner(ndcX + wNDC, ndcY + hNDC);

    //upper left corner
    vec2 ulCorner(ndcX, ndcY + hNDC);

    return {llCorner, lrCorner, urCorner, urCorner, ulCorner, llCorner};
};
