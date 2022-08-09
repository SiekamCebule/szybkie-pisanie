#include "EditExercisesDialog.h"
#include "ui_EditExercisesDialog.h"

#include "ExerciseHeaderWidget.h"

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
        ExerciseHeaderWidget * ehw = static_cast<ExerciseHeaderWidget *>(child->widget());
        Exercise * ex = ehw->getExercise();
        qDebug()<<"child->widget(): "<<ex->getName()<<" "<<ex->getBestTime().toString()<<" "<<ex->getDifficulty()<<" "<<ex->getIsCompleted()<<" "<<ex->getContent();
        delete child->widget();
        qDebug()<<"delete child->widget()";
        delete child;
        qDebug()<<"delete main child";
    }

    for(auto & e : *exercises)
    {        qDebug()<<"goto loop";
        ExerciseHeaderWidget * widget = new ExerciseHeaderWidget(&e, this);
        qDebug()<<"create new widget";
        widget->setOriginalExercises(exercises);
        qDebug()<<"setOriginalExercises";
        widget->setEditDialog(this);
        qDebug()<<"setEditDialog";
        exercisesLayout->addWidget(widget);
        qDebug()<<"add widget\n";
    }
    qDebug()<<"end!  great :DDDD, oh wait...";
}
QVector<Exercise> *EditExercisesDialog::getExercises() const
{
    return exercises;
}

void EditExercisesDialog::setExercises(QVector<Exercise> *newExercises)
{
    exercises = newExercises;
}
