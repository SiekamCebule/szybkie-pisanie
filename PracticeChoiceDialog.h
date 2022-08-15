#pragma once

#include <QDialog>
#include <QVector>

#include "Exercise.h"

namespace Ui {
class PracticeChoiceDialog;
}

class PracticeChoiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PracticeChoiceDialog(QVector<Exercise> * exercises, QWidget *parent = nullptr);
    ~PracticeChoiceDialog();

    QVector<Exercise> *getExercises() const;
    void setExercises(QVector<Exercise> *newExercises);

private:
    Ui::PracticeChoiceDialog *ui;

    QVector<Exercise> * exercises;
};

