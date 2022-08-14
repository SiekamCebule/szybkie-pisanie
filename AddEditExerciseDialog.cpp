#include "AddEditExerciseDialog.h"
#include "ui_AddEditExerciseDialog.h"

#include "Exercise.h"

AddEditExerciseDialog::AddEditExerciseDialog(int action, Exercise * previousExercise, QWidget *parent) :
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

    if(this->previousExercise != nullptr)
    {
        ui->lineEdit_name->setStyleSheet("QLineEdit{\npadding: 4px;\npadding-left: 14px;\ncolor: rgb(158, 216, 255);\nbackground-color: rgb(40, 40, 40);\n}");
        ui->lineEdit_name->setText(previousExercise->getName());
        ui->comboBox_difficulty->setCurrentIndex(previousExercise->getDifficulty() - 1);
        ui->radioButton_resetResults->setChecked(true);
        ui->textEdit_content->setText(previousExercise->getContent());

        switch(previousExercise->getDifficulty())
        {
        case Exercise::Easy:
            ui->comboBox_difficulty->setStyleSheet("QComboBox{\npadding: 4px;\npadding-left: 14px;\ncolor: #45de4c;\nbackground-color: rgb(40, 40, 40);\n}");
            break;
        case Exercise::Medium:
            ui->comboBox_difficulty->setStyleSheet("QComboBox{\npadding: 4px;\npadding-left: 14px;\ncolor: #e6d753;\nbackground-color: rgb(40, 40, 40);\n}");
            break;
        case Exercise::Hard:
            ui->comboBox_difficulty->setStyleSheet("QComboBox{\npadding: 4px;\npadding-left: 14px;\ncolor: #ed5858;\nbackground-color: rgb(40, 40, 40);\n}");
            break;
        }
    }
    else{
        ui->lineEdit_name->setStyleSheet("QLineEdit{\npadding: 4px;\npadding-left: 14px;\ncolor: lightGray;\nbackground-color: rgb(40, 40, 40);\n}");
        ui->comboBox_difficulty->setStyleSheet("QComboBox{\npadding: 4px;\npadding-left: 14px;\ncolor: #45de4c;\nbackground-color: rgb(40, 40, 40);\n}");
    }

    switch(this->action)
    {
    case Edit:
        ui->label_title->setText("Edytuj ćwiczenie");
        ui->radioButton_resetResults->show();
        break;
    case Add:
        ui->label_title->setText("Dodaj ćwiczenie");
        ui->radioButton_resetResults->hide();
        break;
    }

    connect(ui->lineEdit_name, &QLineEdit::textChanged, this, [this](){
        if(ui->lineEdit_name->text().isEmpty())
            ui->lineEdit_name->setStyleSheet("QLineEdit{\npadding: 4px;\npadding-left: 14px;\ncolor: lightGray;\nbackground-color: rgb(40, 40, 40);\n}");
        else {
            ui->lineEdit_name->setStyleSheet("QLineEdit{\npadding: 4px;\npadding-left: 14px;\ncolor: rgb(158, 216, 255);\nbackground-color: rgb(40, 40, 40);\n}");
        }
    });

    connect(ui->comboBox_difficulty, &QComboBox::currentIndexChanged, this, &AddEditExerciseDialog::on_comboBoxCurrentIndexChanged);
}

AddEditExerciseDialog::~AddEditExerciseDialog()
{
    delete ui;
}

void AddEditExerciseDialog::on_comboBoxCurrentIndexChanged(int index)
{
    switch(index + 1)
    {
    case Exercise::Easy:
        ui->comboBox_difficulty->setStyleSheet("QComboBox{\npadding: 4px;\npadding-left: 14px;\ncolor: #45de4c;\nbackground-color: rgb(40, 40, 40);\n}");
        break;
    case Exercise::Medium:
        ui->comboBox_difficulty->setStyleSheet("QComboBox{\npadding: 4px;\npadding-left: 14px;\ncolor: #e6d753;\nbackground-color: rgb(40, 40, 40);\n}");
        break;
    case Exercise::Hard:
        ui->comboBox_difficulty->setStyleSheet("QComboBox{\npadding: 4px;\npadding-left: 14px;\ncolor: #ed5858;\nbackground-color: rgb(40, 40, 40);\n}");
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

Exercise AddEditExerciseDialog::getNewExercise()
{
    QTime bestTime;
    bool completed = false;

    if(previousExercise != nullptr){
        bestTime = previousExercise->getBestTime();
        if(ui->radioButton_resetResults)
        {
            previousExercise->setBestTime(QTime(0, 0, 0, 0));
        }
        else if(previousExercise->getIsCompleted())
            completed = true;
    }
    else if(previousExercise == nullptr || ui->radioButton_resetResults) bestTime = QTime(0, 0, 0, 0);

    return Exercise(ui->lineEdit_name->text(), ui->textEdit_content->toPlainText(), ui->comboBox_difficulty->currentIndex() + 1, bestTime, completed);
}

void AddEditExerciseDialog::on_pushButton_accept_clicked()
{
    accept();
}