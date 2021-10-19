#include "scatteredcirclebrush.h"
#include <paintview.h>
#include <math.h>

ScatteredCircleBrush::ScatteredCircleBrush(const std::string& name) :
    Brush(name)
{
}

void ScatteredCircleBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void ScatteredCircleBrush::BrushMove(const glm::vec2 pos) {
    // Points to draw
    int radius = 20;
    int density = 3;
    for (int i = 0; i < density; i++) {
        int x_offset = rand() % (2*radius+1) - radius;
        int y_offset = rand() % (2*radius+1) - radius;

        // Set the color
        glm::vec2 circle_pos = { pos.x + x_offset, pos.y + y_offset };
        UseColor(GetColor(circle_pos));

        float circ_rad = GetSize()/2;

        for (int i = 0; i < 360; i++) {
            // Points to draw
            std::vector<GLfloat> vertex = {
                pos.x + x_offset, pos.y + y_offset,
                pos.x + cosf(M_PI/180*i)*circ_rad + x_offset, pos.y + sinf(M_PI/180*i)*circ_rad + y_offset
            };

            // Upload the vertex data to GPU buffer
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(), GL_STREAM_DRAW);

            // Set the size of the points and draw them
            glDrawArrays(GL_LINES, 0, 2);
        }
    }
}

void ScatteredCircleBrush::BrushEnd(const glm::vec2 pos) {

}
