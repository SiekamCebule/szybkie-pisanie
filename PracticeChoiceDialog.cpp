#include "PracticeChoiceDialog.h"
#include "ui_PracticeChoiceDialog.h"

#include "ExerciseHeaderWidget.h"

PracticeChoiceDialog::PracticeChoiceDialog(QVector<Exercise> * exercises, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PracticeChoiceDialog),
    exercises(exercises)
{
    ui->setupUi(this);

    QPixmap bc(":/images/menupattern.jpg");
    bc = bc.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bc);
    this->setPalette(palette);

    for(auto & e : *exercises)
    {
        ExerciseHeaderWidget * widget = new ExerciseHeaderWidget(&e, this);
        widget->setOriginalExercises(exercises);
        widget->transformToMiniWidget();
        ui->verticalLayout_exercises->addWidget(widget);
    }
}

PracticeChoiceDialog::~PracticeChoiceDialog()
{
    delete ui;
}

QVector<Exercise> *PracticeChoiceDialog::getExercises() const
{
    return exercises;
}

void PracticeChoiceDialog::setExercises(QVector<Exercise> *newExercises)
{
    exercises = newExercises;
}
