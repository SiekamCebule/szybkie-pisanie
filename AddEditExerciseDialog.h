#pragma once

#include <QDialog>
#include <QTime>

#include "Exercise.h"

namespace Ui {
class AddEditExerciseDialog;
}

class AddEditExerciseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditExerciseDialog(int action = Add, Exercise * previousExercise = nullptr,  QWidget *parent = nullptr);
    ~AddEditExerciseDialog();

    enum Action{
        Add,
        Edit
    };

    int getAction() const;
    void setAction(int newAction);
    Exercise getNewExercise();

private slots:
    void on_comboBoxCurrentIndexChanged(int index);
    void on_pushButton_accept_clicked();

private:
    Ui::AddEditExerciseDialog *ui;

    int action;
    Exercise * previousExercise;
};

