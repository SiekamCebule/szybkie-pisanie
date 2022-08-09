#pragma once

#include <QDialog>
#include <QVector>
#include <QVBoxLayout>
#include "Exercise.h"

namespace Ui {
class EditExercisesDialog;
}

class EditExercisesDialog : public QDialog
{
    Q_OBJECT

public:
    EditExercisesDialog(QWidget *parent = nullptr);
    ~EditExercisesDialog();

    void setLayoutExercises();
    void swapWidgets(int index1, int index2);

    QVector<Exercise> *getExercises() const;
    void setExercises(QVector<Exercise> *newExercises);

private:
    Ui::EditExercisesDialog *ui;
    QVector<Exercise> * exercises;

    QVBoxLayout * exercisesLayout;
};

