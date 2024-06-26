#include "EditExercisesDialog.h"
#include "ui_EditExercisesDialog.h"

#include "ExerciseHeaderWidget.h"
#include "AddEditExerciseDialog.h"

#include <QPixmap>
#include <QPalette>

EditExercisesDialog::EditExercisesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditExercisesDialog)
{
    ui->setupUi(this);

    exercisesLayout = new QVBoxLayout;
    ui->widget_exercises->setLayout(exercisesLayout);

    QPixmap bc(":/images/menupattern.jpg");
    bc = bc.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bc);
    this->setPalette(palette);
}

EditExercisesDialog::~EditExercisesDialog()
{
    delete ui;
}

void EditExercisesDialog::setLayoutExercises()
{
    QLayoutItem * child;
    while((child = exercisesLayout->takeAt(0))!= nullptr)
    {
        delete child->widget();
        delete child;
    }
    for(auto & e : *exercises)
    {
        ExerciseHeaderWidget * widget = new ExerciseHeaderWidget(&e, this);
        widget->setOriginalExercises(exercises);
        widget->setEditDialog(this);
        exercisesLayout->addWidget(widget);
    }
}
QVector<Exercise> *EditExercisesDialog::getExercises() const
{
    return exercises;
}

void EditExercisesDialog::setExercises(QVector<Exercise> *newExercises)
{
    exercises = newExercises;
}

void EditExercisesDialog::on_pushButton_add_clicked()
{
    AddEditExerciseDialog dialog(AddEditExerciseDialog::Add);
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {
        Exercise exercise = dialog.getNewExercise();
        exercises->push_back(dialog.getNewExercise());
        setLayoutExercises();
    }
}

