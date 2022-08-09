#include "AddEditExerciseDialog.h"
#include "ui_AddEditExerciseDialog.h"

#include "Exercise.h"

AddEditExerciseDialog::AddEditExerciseDialog(int action, QWidget *parent, Exercise * previousExercise) :
    QDialog(parent),
    ui(new Ui::AddEditExerciseDialog),
    action(action),
    previousExercise(previousExercise)
{
    ui->setupUi(this);

    QPixmap bc(":/images/menupattern.jpg");
    bc = bc.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bc);
    this->setPalette(palette);

    if(this->action == Edit)
    {
        ui->lineEdit_name->setText(previousExercise->getName());
        ui->comboBox_difficulty->setCurrentIndex(previousExercise->getDifficulty());
        ui->radioButton_resetResults->setChecked(true);
        ui->textEdit_content->setText(previousExercise->getContent());
    }
}

AddEditExerciseDialog::~AddEditExerciseDialog()
{
    delete ui;
}

void AddEditExerciseDialog::on_comboBox_currentIndexChanged(int index)
{
    switch(index + 1)
    {
    case Exercise::Easy:
        ui->comboBox_difficulty->setStyleSheet("QComboBox{\n	color: #45de4c;\n}");
        break;
    case Exercise::Medium:
        ui->comboBox_difficulty->setStyleSheet("QComboBox{\n	color: #e6d753;\n}");
        break;
    case Exercise::Hard:
        ui->comboBox_difficulty->setStyleSheet("QComboBox{\n	color: #ed5858;\n}");
        break;
    }
}

int AddEditExerciseDialog::getAction() const
{
    return action;
}

void AddEditExerciseDialog::setAction(int newAction)
{
    action = newAction;
}

Exercise *AddEditExerciseDialog::getNewExercise()
{
    bool completed = false;
    if(ui->radioButton_resetResults)
    {
        completed = false;
        previousExercise->setBestTime(QTime(0, 0, 0, 0));
    }
    else if(previousExercise->getIsCompleted())
        completed = true;

    return new Exercise(ui->lineEdit_name->text(), ui->textEdit_content->toPlainText(), ui->comboBox_difficulty->currentIndex() + 1, previousExercise->getBestTime(), completed);
}

void AddEditExerciseDialog::on_pushButton_accept_clicked()
{
    accept();
}