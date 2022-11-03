#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

#include <QPixmap>
#include <QPalette>

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>

#include <QMessageBox>

#include "Exercise.h"
#include "EditExercisesDialog.h"
#include "PracticeChoiceDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bc(":/images/menupattern.jpg");
    bc = bc.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bc);
    this->setPalette(palette);

    loadExercisesFromFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_practice_editExercises_clicked()
{
    EditExercisesDialog dialog(this);
    dialog.setModal(true);
    dialog.setExercises(&exercises);
    dialog.setLayoutExercises();
    if(dialog.exec() == QDialog::Rejected)
    {
        qDebug()<<exercises.length();
        saveExercisesToFile();
    }
}

void MainWindow::loadExercisesFromFile()
{
    QFile file("resources/exercises.json");
    file.open(QFile::ReadOnly | QFile::Text);

    QByteArray jsonData = file.readAll();
    QJsonParseError error;

    QJsonDocument document = QJsonDocument::fromJson(jsonData, &error);
    if(error.error != QJsonParseError::NoError)
    {
        QMessageBox::warning(this, "Błąd wczytywania ćwiczeń", "Nie udało się wczytać ćwiczen z pliku resources/exercises.json: " + error.errorString());
    }

    QJsonObject object = document.object();
    QJsonValue value = object.value("exercises");
    QJsonArray array = value.toArray();
    for(const auto & v : array)
    {
        Exercise exercise;
        exercise.setName(v.toObject().value("name").toString());
        exercise.setContent(v.toObject().value("content").toString());
        exercise.setDifficulty(v.toObject().value("difficulty").toInt());
        exercise.setBestTime(QTime::fromString(v.toObject().value("bestTime").toString(), Qt::DateFormat::TextDate));
        exercise.swapBestTimeParameters();
        exercise.setIsCompleted(v.toObject().value("isCompleted").toBool());
        exercise.setPerSegment(v.toObject().value("perSegment").toInt());

        exercises.push_back(exercise);
    }
}

void MainWindow::saveExercisesToFile()
{

    QJsonArray array;
    for(const auto & ex : exercises)
    {
        QJsonObject obj;
        obj["name"] = ex.getName();
        obj["difficulty"] = ex.getDifficulty();
        obj["content"] = ex.getContent();
        obj["bestTime"] = ex.getBestTime().toString();
        obj["isCompleted"] = ex.getIsCompleted();
        obj["perSegment"] = ex.getPerSegment();
        array.push_back(obj);
    }

    QJsonObject title;
    title["exercises"] = array;

    QJsonDocument doc(title);
    QFile file("resources/exercises.json");
    file.open(QFile::WriteOnly | QFile::Text);
    file.write(doc.toJson());
    file.close();
}

void MainWindow::on_pushButton_practice_clicked()
{
    PracticeChoiceDialog dialog(&exercises, this);
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
    {
        qDebug()<<"Practice button clicked in main menu";
    }
}

