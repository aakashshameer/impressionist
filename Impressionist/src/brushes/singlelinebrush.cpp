#include "singlelinebrush.h"
#include <paintview.h>
#include <QFormLayout>
#include <math.h>

SingleLineBrush::SingleLineBrush(const std::string& name) :
    Brush(name),
    thiccness_slider_(new QLabeledSlider)
{
    angle_slider_->SetRange(0, 360);
    layout_->addRow("Angle", angle_slider_);

    thiccness_slider_->SetRange(1, 50);
    layout_->addRow("Thickness", thiccness_slider_);

    // Set default values
    SetSize(24);
    SetAngle(0);
    thiccness_slider_->SetValue(2);
}

void SingleLineBrush::BrushBegin(const glm::vec2 pos) {
    BrushMove(pos);
}

void SingleLineBrush::BrushMove(const glm::vec2 pos) {
    // Set the color
    UseColor(GetColor(pos));

    // Points to draw
    int size = GetSize();
    int thiccness = thiccness_slider_->GetValue();
    float angle = GetAngle()*M_PI/180;

    std::vector<GLfloat> triangle1 = {
        pos.x + cosf(angle)*(-size/2.0f) - sinf(angle)*(-thiccness/2.0f), pos.y + sinf(angle)*(-size/2.0f) + cosf(angle)*(-thiccness/2.0f),
        pos.x + cosf(angle)*(-size/2.0f) - sinf(angle)*(thiccness/2.0f), pos.y + sinf(angle)*(-size/2.0f) + cosf(angle)*(thiccness/2.0f),
        pos.x + cosf(angle)*(size/2.0f) - sinf(angle)*(thiccness/2.0f), pos.y + sinf(angle)*(size/2.0f) + cosf(angle)*(thiccness/2.0f)
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangle1.size(), triangle1.data(), GL_STREAM_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    std::vector<GLfloat> triangle2 = {
        pos.x + cosf(angle)*(-size/2.0f) - sinf(angle)*(-thiccness/2.0f), pos.y + sinf(angle)*(-size/2.0f) + cosf(angle)*(-thiccness/2.0f),
        pos.x + cosf(angle)*(size/2.0f) - sinf(angle)*(-thiccness/2.0f), pos.y + sinf(angle)*(size/2.0f) + cosf(angle)*(-thiccness/2.0f),
        pos.x + cosf(angle)*(size/2.0f) - sinf(angle)*(thiccness/2.0f), pos.y + sinf(angle)*(size/2.0f) + cosf(angle)*(thiccness/2.0f)
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangle2.size(), triangle2.data(), GL_STREAM_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SingleLineBrush::BrushEnd(const glm::vec2 pos) {

}
