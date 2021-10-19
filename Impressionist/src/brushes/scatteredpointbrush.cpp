#include "scatteredpointbrush.h"
#include <paintview.h>

ScatteredPointBrush::ScatteredPointBrush(const std::string& name) :
    Brush(name)
{
}

void ScatteredPointBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void ScatteredPointBrush::BrushMove(const glm::vec2 pos) {
    // Points to draw
    int radius = 20;
    int density = 3;
    for (int i = 0; i < density; i++) {
        int x_offset = rand() % (2*radius+1) - radius;
        int y_offset = rand() % (2*radius+1) - radius;
        // Set the color
        glm::vec2 point_pos = { pos.x + x_offset, pos.y + y_offset };
        UseColor(GetColor(point_pos));

        std::vector<GLfloat> vertex = {
            pos.x + x_offset, pos.y + y_offset
        };

        // Upload the vertex data to GPU buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(), GL_STREAM_DRAW);

        // Set the size of the points and draw them
        glPointSize(GetSize());
        glDrawArrays(GL_POINTS, 0, 1);
    }
}

void ScatteredPointBrush::BrushEnd(const glm::vec2 pos) {

}
