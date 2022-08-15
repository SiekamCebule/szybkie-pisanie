#pragma once

#include <QMainWindow>
#include <QVector>

#include "Exercise.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_practice_editExercises_clicked();
    void on_pushButton_practice_clicked();

private:
    Ui::MainWindow *ui;

    void loadExercisesFromFile();
    QVector<Exercise> exercises;
};
