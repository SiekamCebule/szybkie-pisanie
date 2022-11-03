#include "ExerciseWindow.h"
#include "ui_ExerciseWindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QtCore5Compat/QStringRef>


ExerciseWindow::ExerciseWindow(Exercise * exercise, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExerciseWindow),
    exercise(exercise)
{
    ui->setupUi(this);

    QPixmap bc(":/images/menupattern.jpg");
    bc = bc.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bc);
    this->setPalette(palette);

    dynamicContent = exercise->getContent();
    dynamicContentLayout = new QVBoxLayout;
    ui->scrollAreaWidget_content->setLayout(dynamicContentLayout);

    setupSegments();
}

ExerciseWindow::~ExerciseWindow()
{
    delete ui;
}

Exercise *ExerciseWindow::getExercise() const
{
    return exercise;
}

void ExerciseWindow::setExercise(Exercise *newExercise)
{
    exercise = newExercise;
}

void ExerciseWindow::setupSegments()
{
    qDebug()<<"setupSegments";
    widgetsToDelete.clear();
    exercise->removeWhitespacesFromContent();
    qDebug()<<"content at begin: "<<dynamicContent;
    int letters = dynamicContent.size();
    int perSegment = exercise->getPerSegment();
    int segments = letters / perSegment;
    int lastSegmentLetters = (letters) % (exercise->getPerSegment());
    if(lastSegmentLetters == 0) lastSegmentLetters = perSegment;

    qDebug()<<letters <<", "<<perSegment<< ", "<<segments<< ", "<<lastSegmentLetters;
    qDebug()<<"NOWE";

    for(int i = 0; i < segments; i++)
    {
        QVBoxLayout * vlayout = new QVBoxLayout();

        dynamicLineContentLength = perSegment;
        if(i+1 == segments)
            dynamicLineContentLength = lastSegmentLetters;

        QString lineContent;
        for(int j = 0; j < dynamicLineContentLength; j++)
        {
            lineContent.append(dynamicContent.at(i * perSegment + j));
        }
        qDebug()<<"git1";

        QLabel * label = new QLabel(lineContent);
        label->setFont(QFont("Noto Sans Light", 11));
        label->setStyleSheet("QLabel{\n	color: rgb(255, 197, 138);\n}");
        vlayout->addWidget(label);
        widgetsToDelete.push_back(label);
        qDebug()<<"git2";

        QLineEdit * lineEdit = new QLineEdit();
        lineEdit->setMaxLength(dynamicLineContentLength);
        vlayout->addWidget(lineEdit);
        widgetsToDelete.push_back(lineEdit);
        qDebug()<<"git3";

        connect(lineEdit, &QLineEdit::textChanged, this, [this, lineEdit](){
            qDebug()<<"connect";
            if(lineEdit->text().length() == dynamicLineContentLength)
            {
                qDebug()<<"dynamicLineContentLength: "<<dynamicLineContentLength;
                qDebug()<<"dynamicContent 1: "<<dynamicContent;
                dynamicContent.erase(dynamicContent.begin(), dynamicContent.begin() + dynamicLineContentLength);
                qDebug()<<"dynamicContent 2: "<<dynamicContent;
                // tworzenie layoutu na nowo
                if(dynamicContentLayout != nullptr)
                {
                    QLayoutItem * item;
                    while((item = dynamicContentLayout->takeAt(0)) != nullptr)
                    {
                        delete item->layout();
                        qDebug()<<"delete item->layout()";
                        //delete item;
                    }
                    qDebug()<<"before widgetsToDelete";
                    for(auto & widget : widgetsToDelete)
                    {
                        delete widget;
                    }
                    qDebug()<<"after widgetsToDelete";

                    /*qDebug()<<dynamicContentLayout->count();
                    delete dynamicContentLayout->layout();
                    qDebug()<<"delete dynamicContentLayout->layout()";
                    delete dynamicContentLayout;
                    qDebug()<<"delete dynamicContentLayout";
                    qDebug()<<"setparent null";*/
                }
                setupSegments();
                qDebug()<<"dynamicContentLayout->count()"<<dynamicContentLayout->count();
                qDebug()<<"ui->scrollAreaWidget_content->layout()"<<ui->scrollAreaWidget_content->layout();
            }
        });
        qDebug()<<"dynamicContentLayout->addLayout(vlayout);";
        dynamicContentLayout->addLayout(vlayout);
        qDebug()<<"dynamicContentLayout: "<<dynamicContentLayout->count();
        qDebug()<<"end";
    }
    qDebug()<<"before absolute end";
    dynamicContentLayout->itemAt(0)->layout()->itemAt(1)->widget()->setFocus();
    qDebug()<<"absolute end";
}
// po operacji usuwania nie ma już widgetów w layoucie ale są dalej ustawione swobodnie na ekranie