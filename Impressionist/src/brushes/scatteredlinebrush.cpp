#include "scatteredlinebrush.h"
#include <paintview.h>
#include <QFormLayout>
#include <math.h>

ScatteredLineBrush::ScatteredLineBrush(const std::string& name) :
    Brush(name),
    angle_slider_(new QLabeledSlider),
    thiccness_slider_(new QLabeledSlider)
{
    angle_slider_->SetRange(0, 360);
    layout_->addRow("Angle", angle_slider_);

    thiccness_slider_->SetRange(1, 50);
    layout_->addRow("Thickness", thiccness_slider_);

    // Set default values
    SetSize(24);
    angle_slider_->SetValue(0);
    thiccness_slider_->SetValue(2);
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

        // Points to draw
        std::vector<std::vector<GLfloat>> lines;
        int size = GetSize();
        int thiccness = thiccness_slider_->GetValue();
        int angle = angle_slider_->GetValue()*M_PI/180;

        std::vector<GLfloat> triangle1 = {
            line_pos.x + cosf(angle)*(-size/2.0f) - sinf(angle)*(-thiccness/2.0f), line_pos.y + sinf(angle)*(-size/2.0f) + cosf(angle)*(-thiccness/2.0f),
            line_pos.x + cosf(angle)*(-size/2.0f) - sinf(angle)*(thiccness/2.0f), line_pos.y + sinf(angle)*(-size/2.0f) + cosf(angle)*(thiccness/2.0f),
            line_pos.x + cosf(angle)*(size/2.0f) - sinf(angle)*(thiccness/2.0f), line_pos.y + sinf(angle)*(size/2.0f) + cosf(angle)*(thiccness/2.0f)
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangle1.size(), triangle1.data(), GL_STREAM_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        std::vector<GLfloat> triangle2 = {
            line_pos.x + cosf(angle)*(-size/2.0f) - sinf(angle)*(-thiccness/2.0f), line_pos.y + sinf(angle)*(-size/2.0f) + cosf(angle)*(-thiccness/2.0f),
            line_pos.x + cosf(angle)*(size/2.0f) - sinf(angle)*(-thiccness/2.0f), line_pos.y + sinf(angle)*(size/2.0f) + cosf(angle)*(-thiccness/2.0f),
            line_pos.x + cosf(angle)*(size/2.0f) - sinf(angle)*(thiccness/2.0f), line_pos.y + sinf(angle)*(size/2.0f) + cosf(angle)*(thiccness/2.0f)
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangle2.size(), triangle2.data(), GL_STREAM_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

void ScatteredLineBrush::BrushEnd(const glm::vec2 pos) {

}
