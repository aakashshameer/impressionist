#include "scatteredcirclebrush.h"
#include <paintview.h>
#include <math.h>
#include <QFormLayout>

ScatteredCircleBrush::ScatteredCircleBrush(const std::string& name) :
    Brush(name),
    radius_slider_(new QLabeledSlider),
    density_slider_(new QLabeledSlider)
{
    radius_slider_->SetRange(1, 50);
    layout_->addRow("Radius", radius_slider_);

    density_slider_->SetRange(1, 20);
    layout_->addRow("Density", density_slider_);

    radius_slider_->SetValue(24);
    density_slider_->SetValue(3);
}

void ScatteredCircleBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void ScatteredCircleBrush::BrushMove(const glm::vec2 pos) {
    // Points to draw
    int radius = radius_slider_->GetValue();
    int density = density_slider_->GetValue();
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
