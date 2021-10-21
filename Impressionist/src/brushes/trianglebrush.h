#ifndef TRIANGLEBRUSH_H
#define TRIANGLEBRUSH_H

#include <brushes/brush.h>
#include <qlabeledslider.h>

class TriangleBrush : public Brush {
public:
    TriangleBrush(const std::string& name);

    virtual void BrushBegin(const glm::vec2 pos) override;
    virtual void BrushMove(const glm::vec2 pos) override;
    virtual void BrushEnd(const glm::vec2 pos) override;
};

#endif // TRIANGLEBRUSH_H
