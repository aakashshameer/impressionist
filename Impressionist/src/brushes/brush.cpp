/****************************************************************************
 * Copyright ©2017 Brian Curless.  All rights reserved.  Permission is hereby
 * granted to students registered for University of Washington CSE 457 or CSE
 * 557 for use solely during Autumn Quarter 2017 for purposes of the course.
 * No other use, copying, distribution, or modification is permitted without
 * prior written consent. Copyrights for third-party components of this work
 * must be honored.  Instructors interested in reusing these course materials
 * should contact the author.
 ****************************************************************************/

#include "brush.h"
#include <filters/filter.h>
#include <QWidget>
#include <QFormLayout>
#include <QComboBox>
#include <qlabeledslider.h>

Brush::Brush(const std::string& name) :
    prev_angles(new CircularBuffer<int>(10)),
    widget_(new QWidget),
    layout_(new QFormLayout),
    name_(name),
    size_slider_(new QLabeledSlider),
    angle_slider_(new QLabeledSlider),
    color_mode_(ColorMode::Solid),
    color_location_(-1),
    color_(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
    angle_mode_(AngleMode::Direct),
    color_image_(nullptr),
    color_image_width_(0),
    color_image_height_(0)
{
    widget_->setLayout(layout_);

    // Size Slider
    size_slider_->SetRange(1, 100);
    layout_->addRow("Size", size_slider_);

    // REQUIREMENT: Allow user to control the opacity via a slider

    // Default Values
    SetSize(12);
}

QWidget* Brush::GetWidget() const {
    return widget_;
}

std::string Brush::GetName() const {
    return name_;
}
void Brush::SetSize(unsigned int size) {
    size = size > 100 ? 100 : size;
    size_slider_->SetValue(size);
}

void Brush::SetAngle(unsigned int angle) {
    angle = angle > 360 ? angle-180 : angle;
    angle = angle < 0 ? angle+180 : angle;
    angle_slider_->SetValue(angle);
}

void Brush::SetColor(const glm::vec3& color) {
    color_ = color;
}

void Brush::SetColorImage(const unsigned char* color_image, unsigned int width, unsigned int height) {
    color_image_ = color_image;
    color_image_width_ = width;
    color_image_height_ = height;
}

void Brush::SetColorMode(ColorMode color_mode) {
    color_mode_ = color_mode;
}

void Brush::SetColorLocation(GLint color_location) {
    color_location_ = color_location;
}

void Brush::UseColor(const glm::vec4& color) {
    assert(color_location_ != -1);
    glUniform4fv(color_location_, 1, glm::value_ptr(color));
}

unsigned int Brush::GetSize() const {
    return size_slider_->GetValue();
}

unsigned int Brush::GetAngle() const {
    return angle_slider_->GetValue();
}

glm::vec4 Brush::GetColor(glm::ivec2 position) const {
    if (color_mode_ == ColorMode::Sample && color_image_ != nullptr) {
        unsigned int width = color_image_width_;
        unsigned int height = color_image_height_;

        // Don't exceed the coordinates of the color image
        if (position.x < 0) position.x = 0;
        else if (position.x >= width) position.x = width - 1;
        if (position.y < 0) position.y = 0;
        else if (position.y >= height) position.y = height - 1;

        // Sample the color image at the position
        glm::vec4 color;
        int index = (position.y * 4) * width + (position.x * 4);
        color.r = color_image_[index++] / 255.0f;
        color.g = color_image_[index++] / 255.0f;
        color.b = color_image_[index++] / 255.0f;
        color.a = color_image_[index++] / 255.0f;

        return color;
    } else {
        return glm::vec4(color_, 1.0f);
    }
}

void Brush::SavePos(const glm::vec2 pos) {
    saved_pos_ = pos;
}

glm::vec2 Brush::GetSavedPos(){
    return saved_pos_;
}

AngleMode Brush::GetAngleMode() const{
    return angle_mode_;
}
