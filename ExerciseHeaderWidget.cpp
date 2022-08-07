#include "ExerciseHeaderWidget.h"
#include "ui_ExerciseHeaderWidget.h"

ExerciseHeaderWidget::ExerciseHeaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExerciseHeaderWidget)
{
    ui->setupUi(this);
}

ExerciseHeaderWidget::~ExerciseHeaderWidget()
{
    delete ui;
}
