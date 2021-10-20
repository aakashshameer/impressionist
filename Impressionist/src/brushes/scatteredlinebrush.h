#ifndef SCATTEREDLINEBRUSH_H
#define SCATTEREDLINEBRUSH_H

#include <brushes/brush.h>
#include <qlabeledslider.h>

class ScatteredLineBrush : public Brush {
public:
    ScatteredLineBrush(const std::string& name);

    virtual void BrushBegin(const glm::vec2 pos) override;
    virtual void BrushMove(const glm::vec2 pos) override;
    virtual void BrushEnd(const glm::vec2 pos) override;

private:
    QLabeledSlider* angle_slider_;
    QLabeledSlider* thiccness_slider_;
};

#endif // SCATTEREDLINEBRUSH_H
