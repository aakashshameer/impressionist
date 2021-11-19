#include "trianglebrush.h"
#include <paintview.h>
#include <math.h>
#include <QFormLayout>

TriangleBrush::TriangleBrush(const std::string& name) :
    Brush(name)
{
}

void TriangleBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void TriangleBrush::BrushMove(const glm::vec2 pos) {
    // Set the color
    UseColor(GetColor(pos));
    float size = GetSize()/2.0f;

    for (int i = 0; i < 360; i++) {
        // Points to draw
        std::vector<GLfloat> vertex = {
            pos.x, pos.y - size,
            pos.x + size, pos.y + size,
            pos.x - size, pos.y + size
        };

        // Upload the vertex data to GPU buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(), GL_STREAM_DRAW);

        // Set the size of the points and draw them
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

void TriangleBrush::BrushEnd(const glm::vec2 pos) {

}
