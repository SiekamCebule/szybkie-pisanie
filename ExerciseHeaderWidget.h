#pragma once

#include <QWidget>

namespace Ui {
class ExerciseHeaderWidget;
}

class ExerciseHeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExerciseHeaderWidget(QWidget *parent = nullptr);
    ~ExerciseHeaderWidget();

private:
    Ui::ExerciseHeaderWidget *ui;
};

