#include "scatteredlinebrush.h"
#include <paintview.h>

ScatteredLineBrush::ScatteredLineBrush(const std::string& name) : Brush(name) {
}

void ScatteredLineBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void ScatteredLineBrush::BrushMove(const glm::vec2 pos) {
    // Points to draw
    int radius = 20;
    int density = 3;
    for (int i = 0; i < density; i++) {
        int x_offset = rand() % (2*radius+1) - radius;
        int y_offset = rand() % (2*radius+1) - radius;

        // Set the color
        glm::vec2 line_pos = { pos.x + x_offset, pos.y + y_offset };
        UseColor(GetColor(line_pos));

        std::vector<std::vector<GLfloat>> lines;
        int thiccness = 10;
        for (int i = -thiccness/2; i <= thiccness/2; i++) {
            std::vector<GLfloat> vertex = {
                pos.x - GetSize()/2 + x_offset, pos.y + i + y_offset,
                pos.x + GetSize()/2 + x_offset, pos.y + i + y_offset
            };

            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(), GL_STREAM_DRAW);
            glDrawArrays(GL_LINES, 0, 2);
        }
    }

    // Upload the vertex data to GPU buffer
}

void ScatteredLineBrush::BrushEnd(const glm::vec2 pos) {

}
