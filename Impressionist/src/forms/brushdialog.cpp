/****************************************************************************
 * Copyright ©2017 Brian Curless.  All rights reserved.  Permission is hereby
 * granted to students registered for University of Washington CSE 457 or CSE
 * 557 for use solely during Autumn Quarter 2017 for purposes of the course.
 * No other use, copying, distribution, or modification is permitted without
 * prior written consent. Copyrights for third-party components of this work
 * must be honored.  Instructors interested in reusing these course materials
 * should contact the author.
 ****************************************************************************/

#include "brushdialog.h"
#include "ui_brushdialog.h"
#include <brushes/pointbrush.h>

BrushDialog::BrushDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushDialog),
    current_brush_choice_(0),
    current_angle_choice_(0)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    // Create the brushes
    brushes_[Brushes::Point] = std::make_unique<PointBrush>("Points");
    // REQUIREMENT: Implement these five brushes. They are set to all be the same for now.
    //              You should create a new class (e.g. CircleBrush) in new files (e.g. circlebrush.h/.cpp)
    brushes_[Brushes::Line] = std::make_unique<PointBrush>("Lines");
    brushes_[Brushes::Circle] = std::make_unique<PointBrush>("Circles");
    brushes_[Brushes::ScatterPoint] = std::make_unique<PointBrush>("Scattered Points");
    brushes_[Brushes::ScatterLine] = std::make_unique<PointBrush>("Scattered Lines");
    brushes_[Brushes::ScatterCircle] = std::make_unique<PointBrush>("Scattered Circles");

    // Add the brushes to the combo box
    for (auto& kv : brushes_) {
        brush_choices_.push_back(kv.first);
        ui->brush_choices->addItem(QString::fromStdString(kv.second->GetName()));
        ui->brush_props->addWidget(kv.second->GetWidget());
    }

    // Angle control methods
    ui->angle_control_choices->addItem("Slider / RMB");
    ui->angle_control_choices->addItem("Gradient");
    ui->angle_control_choices->addItem("Cursor Movement");
    angle_choices_ = {
        AngleMode::Direct,
        AngleMode::Gradient,
        AngleMode::CursorMovement
    };

    // Connect the combo box to select the current brush
    connect(ui->brush_choices, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this](int index){
        current_brush_choice_ = index;
        ui->brush_props->setCurrentIndex(index);
    });

    // Connect the combo box to select the angle control type
    connect(ui->angle_control_choices, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this](int index){
        current_angle_choice_ = index;
    });
}

BrushDialog::~BrushDialog() {
    delete ui;
}

Brush& BrushDialog::GetCurrentBrush() {
    Brushes brush_type = brush_choices_[current_brush_choice_];
    assert(brushes_.count(brush_type) > 0);
    return *brushes_[brush_type];
}

AngleMode BrushDialog::GetCurrentAngleControl() {
    return angle_choices_[current_angle_choice_];

}