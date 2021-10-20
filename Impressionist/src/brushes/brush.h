/****************************************************************************
 * Copyright ©2017 Brian Curless.  All rights reserved.  Permission is hereby
 * granted to students registered for University of Washington CSE 457 or CSE
 * 557 for use solely during Autumn Quarter 2017 for purposes of the course.
 * No other use, copying, distribution, or modification is permitted without
 * prior written consent. Copyrights for third-party components of this work
 * must be honored.  Instructors interested in reusing these course materials
 * should contact the author.
 ****************************************************************************/

#ifndef BRUSH_H
#define BRUSH_H

#include <glinclude.h>
#include <string>
#include <vectors.h>
#include <circularbuffer.h>

class QWidget;
class QFormLayout;
class QLabeledSlider;
class QComboBox;

// Different types of brushes
enum class Brushes {
    Point,
    Line,
    Circle,
    ScatterPoint,
    ScatterLine,
    ScatterCircle
};

// How to control the angle of the brush
enum class AngleMode {
    Direct,
    CursorMovement,
    Gradient
};

// How to get the color to draw with
enum class ColorMode {
    Solid,
    Sample
};

class Brush {
public:
    Brush(const std::string& name);
    virtual ~Brush(){}

    QWidget* GetWidget() const;
    std::string GetName() const;

    virtual void SetSize(unsigned int size);
    virtual void SetAngle(unsigned int angle);
    virtual void SetColor(const glm::vec3& color);
    virtual void SetColorImage(const unsigned char* color_image, unsigned int width, unsigned int height);
    virtual void SetColorMode(ColorMode color_mode);

    // Must be called before drawing
    virtual void SetColorLocation(GLint color_location);

    // Called for drawing
    virtual void BrushBegin(const glm::vec2 pos) = 0;
    virtual void BrushMove(const glm::vec2 pos) = 0;
    virtual void BrushEnd(const glm::vec2 pos) = 0;

    virtual void SavePos(const glm::vec2 pos);
    virtual glm::vec2 GetSavedPos();

    CircularBuffer<int>* prev_angles;

protected:
    QWidget* widget_;
    QFormLayout* layout_;
    std::string name_;
    QLabeledSlider* opacity_slider_;
    QLabeledSlider* size_slider_;
    QLabeledSlider* angle_slider_;
    ColorMode color_mode_;
    GLint color_location_;
    glm::vec3 color_;
    AngleMode angle_mode_;
    glm::vec2 saved_pos_;

    // Image to sample colors from
    const unsigned char* color_image_;
    unsigned int color_image_width_;
    unsigned int color_image_height_;

    // Called inside the BrushBegin/BrushMove/BrushEnd methods
    unsigned int GetSize() const;
    unsigned int GetAngle() const;
    AngleMode GetAngleMode() const;

    glm::vec4 GetColor(glm::ivec2 position = glm::ivec2(0, 0)) const;
    void UseColor(const glm::vec4& color);


};

#endif // BRUSH_H
