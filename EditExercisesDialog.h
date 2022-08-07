#pragma once

#include <QDialog>

namespace Ui {
class EditExercisesDialog;
}

class EditExercisesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditExercisesDialog(QWidget *parent = nullptr);
    ~EditExercisesDialog();

private:
    Ui::EditExercisesDialog *ui;
};

