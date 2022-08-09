#pragma once

#include <QWidget>
#include <QVector>

#include "Exercise.h"
#include "EditExercisesDialog.h"

namespace Ui {
class ExerciseHeaderWidget;
}

class ExerciseHeaderWidget : public QWidget
{
    Q_OBJECT

public:
    ExerciseHeaderWidget(Exercise * exercise, QWidget *parent = nullptr);
    ~ExerciseHeaderWidget();

    Exercise *getExercise() const;

    QVector<Exercise> *getOriginalExercises() const;
    void setOriginalExercises(QVector<Exercise> *newOriginalExercises);

    EditExercisesDialog *getEditDialog() const;
    void setEditDialog(EditExercisesDialog *newEditDialog);

private slots:
    void on_pushButton_down_clicked();
    void on_pushButton_up_clicked();
    void on_pushButton_remove_clicked();
    void on_pushButton_edit_clicked();

private:
    Ui::ExerciseHeaderWidget *ui;

    Exercise * exercise;
    QVector<Exercise> * originalExercises;
    EditExercisesDialog * editDialog;
};

