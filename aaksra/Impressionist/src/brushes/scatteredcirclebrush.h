#ifndef SCATTEREDCIRCLEBRUSH_H
#define SCATTEREDCIRCLEBRUSH_H

#include <brushes/brush.h>
#include <qlabeledslider.h>

class ScatteredCircleBrush : public Brush {
public:
    ScatteredCircleBrush(const std::string& name);

    virtual void BrushBegin(const glm::vec2 pos) override;
    virtual void BrushMove(const glm::vec2 pos) override;
    virtual void BrushEnd(const glm::vec2 pos) override;
protected:
    QLabeledSlider* radius_slider_;
    QLabeledSlider* density_slider_;
};

#endif // SCATTEREDCIRCLEBRUSH_H
