#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPixmap>
#include <QPalette>

#include "EditExercisesDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bc(":/img/menupattern.jpg");
    bc = bc.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bc);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_practice_editExercises_clicked()
{
    EditExercisesDialog dialog(this);
    dialog.setModal(true);
    dialog.exec();

}

