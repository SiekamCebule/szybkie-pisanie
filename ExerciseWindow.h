#pragma once

#include <QDialog>
#include <QKeyEvent>
#include <QString>
#include <QVBoxLayout>
#include <QVector>

#include "Exercise.h"

namespace Ui {
class ExerciseWindow;
}

class ExerciseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ExerciseWindow(Exercise * exercise, QWidget *parent = nullptr);
    ~ExerciseWindow();

    Exercise *getExercise() const;
    void setExercise(Exercise *newExercise);

protected:

private:
    Ui::ExerciseWindow *ui;
    void setupSegments();
    QString dynamicContent;
    int dynamicLineContentLength;
    QVBoxLayout * dynamicContentLayout;

    QVector<QWidget *>widgetsToDelete;


    Exercise * exercise;
};

