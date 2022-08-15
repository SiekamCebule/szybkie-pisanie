#include "ExerciseHeaderWidget.h"
#include "ui_ExerciseHeaderWidget.h"

#include <QPixmap>

#include "AddEditExerciseDialog.h"

ExerciseHeaderWidget::ExerciseHeaderWidget(Exercise * exercise, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExerciseHeaderWidget),
    exercise(exercise)
{
    ui->setupUi(this);
    QString img;

    if(exercise->getIsCompleted())
        img = "finished.png";
    else img = "unfinished.png";
    ui->label_iconIsCompleted->setPixmap(QPixmap(":/images/" + img).scaled(ui->label_iconIsCompleted->size()));
    ui->label_name->setText(exercise->getName());
    switch(exercise->getDifficulty())
    {
    case Exercise::Easy:
        ui->label_difficulty->setText("Łatwy");
        ui->label_difficulty->setStyleSheet("QLabel{\n	color: #45de4c;\n}");
        break;
    case Exercise::Medium:
        ui->label_difficulty->setText("Średni");
        ui->label_difficulty->setStyleSheet("QLabel{\n	color: #e6d753;\n}");
        break;
    case Exercise::Hard:
        ui->label_difficulty->setText("Trudny");
        ui->label_difficulty->setStyleSheet("QLabel{\n	color: #ed5858;\n}");
        break;
    }
}

ExerciseHeaderWidget::~ExerciseHeaderWidget()
{
    delete ui;
}

Exercise *ExerciseHeaderWidget::getExercise() const
{
    return exercise;
}

QVector<Exercise> *ExerciseHeaderWidget::getOriginalExercises() const
{
    return originalExercises;
}

void ExerciseHeaderWidget::setOriginalExercises(QVector<Exercise> *newOriginalExercises)
{
    originalExercises = newOriginalExercises;
}
void ExerciseHeaderWidget::on_pushButton_down_clicked()
{
    int thisIndex = 0;
    for(int i = 0; i < originalExercises->size(); i++)
    {
        if(this->exercise == &originalExercises->at(i))
            thisIndex = i;
    }
    if(thisIndex + 1 != originalExercises->size())
        originalExercises->swapItemsAt(thisIndex, thisIndex+1);

    editDialog->setLayoutExercises();
}

void ExerciseHeaderWidget::on_pushButton_up_clicked()
{
    int thisIndex = 0;
    for(int i = 0; i < originalExercises->size(); i++)
    {
        if(this->exercise == &originalExercises->at(i))
            thisIndex = i;
    }
    if(thisIndex != 0)
        originalExercises->swapItemsAt(thisIndex, thisIndex-1);

    editDialog->setLayoutExercises();
}

EditExercisesDialog *ExerciseHeaderWidget::getEditDialog() const
{
    return editDialog;
}

void ExerciseHeaderWidget::setEditDialog(EditExercisesDialog *newEditDialog)
{
    editDialog = newEditDialog;
}

void ExerciseHeaderWidget::transformToMiniWidget()
{
    delete ui->pushButton_edit;
    delete ui->pushButton_remove;
    delete ui->pushButton_up;
    delete ui->pushButton_down;

    practiceButton = new QPushButton(this);

    practiceButton->setFlat(true);
    practiceButton->setIcon(QIcon(":/images/play.png"));
    practiceButton->setIconSize(QSize(53, 53));
    practiceButton->setStyleSheet("QPushButton\n{\n	margin: 5px;\nborder: 1px solid;\n}");

    ui->horizontalLayout->addWidget(practiceButton);

    connect(practiceButton, &QPushButton::clicked, this, [this](){
        qDebug()<<"[practiceButton connect] --> clicked";
    });
}

void ExerciseHeaderWidget::on_pushButton_remove_clicked()
{
    int thisIndex = 0;
    for(int i = 0; i < originalExercises->size(); i++)
    {
        if(this->exercise == &originalExercises->at(i))
            thisIndex = i;
    }
    originalExercises->erase(originalExercises->constBegin() + thisIndex);

    editDialog->setLayoutExercises();
}

void ExerciseHeaderWidget::on_pushButton_edit_clicked()
{
    int thisIndex = 0;
    for(int i = 0; i < originalExercises->size(); i++)
    {
        if(this->exercise == &originalExercises->at(i))
            thisIndex = i;
    }

    AddEditExerciseDialog dialog(AddEditExerciseDialog::Edit, &originalExercises->operator[](thisIndex));
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {
        originalExercises->operator[](thisIndex).setName(dialog.getNewExercise().getName());
        originalExercises->operator[](thisIndex).setContent(dialog.getNewExercise().getContent());
        originalExercises->operator[](thisIndex).setDifficulty(dialog.getNewExercise().getDifficulty());
        originalExercises->operator[](thisIndex).setIsCompleted(dialog.getNewExercise().getIsCompleted());
        originalExercises->operator[](thisIndex).setBestTime(dialog.getNewExercise().getBestTime());

        editDialog->setLayoutExercises();
    }
}

