#include "singlelinebrush.h"
#include <paintview.h>

SingleLineBrush::SingleLineBrush(const std::string& name) : Brush(name) {
}

void SingleLineBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void SingleLineBrush::BrushMove(const glm::vec2 pos) {
    // Set the color
    UseColor(GetColor(pos));

    // Points to draw
    std::vector<std::vector<GLfloat>> lines;
    int thiccness = 10;
    for (int i = -thiccness/2; i <= thiccness/2; i++) {
        std::vector<GLfloat> vertex = {
            pos.x - GetSize()/2, pos.y + i,
            pos.x + GetSize()/2, pos.y + i
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(), GL_STREAM_DRAW);
        glDrawArrays(GL_LINES, 0, 2);
    }


    // Upload the vertex data to GPU buffer
}

void SingleLineBrush::BrushEnd(const glm::vec2 pos) {

}
