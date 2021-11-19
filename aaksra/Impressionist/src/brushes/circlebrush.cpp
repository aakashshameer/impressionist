#include "circlebrush.h"
#include <paintview.h>
#include <math.h>

CircleBrush::CircleBrush(const std::string& name) :
    Brush(name)
{
}

void CircleBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void CircleBrush::BrushMove(const glm::vec2 pos) {
    // Set the color
    UseColor(GetColor(pos));
    float radius = GetSize()/2;

    for (int i = 0; i < 360; i++) {
        // Points to draw
        std::vector<GLfloat> vertex = {
            pos.x, pos.y,
            pos.x + cosf(M_PI/180*i)*radius, pos.y + sinf(M_PI/180*i)*radius
        };

        // Upload the vertex data to GPU buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(), GL_STREAM_DRAW);

        // Set the size of the points and draw them
        glDrawArrays(GL_LINES, 0, 2);
    }
}

void CircleBrush::BrushEnd(const glm::vec2 pos) {

}
