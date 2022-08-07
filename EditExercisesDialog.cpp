#include "EditExercisesDialog.h"
#include "ui_EditExercisesDialog.h"

#include <QPixmap>
#include <QPalette>

EditExercisesDialog::EditExercisesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditExercisesDialog)
{
    ui->setupUi(this);

    QPixmap bc(":/img/menupattern.jpg");
    bc = bc.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bc);
    this->setPalette(palette);
}

EditExercisesDialog::~EditExercisesDialog()
{
    delete ui;
}
