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
    qDebug()<<"setupSegments wywołane";
    widgetsToDelete.clear();
    exercise->removeWhitespacesFromContent();
    qDebug()<<"content na początku: "<<dynamicContent;
    int letters = dynamicContent.size();
    int perSegment = exercise->getPerSegment();
    int segments = letters / perSegment;
    int lastSegmentLetters = (letters) % (exercise->getPerSegment());
    if(lastSegmentLetters == 0) lastSegmentLetters = perSegment;

    qDebug()<<letters <<" ilość contentu , "<<perSegment<< " na segment , "<<segments<< " segmentów , "<<lastSegmentLetters<<" w ostatnim segmencie";

    for(int i = 0; i < segments; i++)
    {
        QVBoxLayout * vlayout = new QVBoxLayout();

        dynamicLineContentLength = perSegment;
        if(i+1 == segments)
            dynamicLineContentLength = lastSegmentLetters;

        qDebug()<<"dynamicLineContentLength: "<<dynamicLineContentLength;

        QString lineContent;
        for(int j = 0; j < dynamicLineContentLength; j++)
        {
            lineContent.append(dynamicContent.at(i * perSegment + j));
        }
        qDebug()<<"lineContent: "<<lineContent;

        QLabel * label = new QLabel(lineContent);
        label->setFont(QFont("Noto Sans Light", 11));
        label->setStyleSheet("QLabel{\n	color: rgb(255, 197, 138);\n}");
        vlayout->addWidget(label);
        widgetsToDelete.push_back(label);

        QLineEdit * lineEdit = new QLineEdit();
        lineEdit->setMaxLength(dynamicLineContentLength);
        vlayout->addWidget(lineEdit);
        widgetsToDelete.push_back(lineEdit);

        dynamicContentLayout->addLayout(vlayout);
        qDebug()<<"Dodano vlayout do dynamicContentLayout";
        qDebug()<<"koniec funkcji setupSegments (przed connect)";

        connect(lineEdit, &QLineEdit::textChanged, this, [this, lineEdit](){
            qDebug()<<"Slot wywołany";
            if(lineEdit->text().length() == dynamicLineContentLength)
            {
                dynamicContent.erase(dynamicContent.constBegin(), dynamicContent.constBegin() + dynamicLineContentLength);
                qDebug()<<"content po odcięciu: "<<dynamicContent;
                // tworzenie layoutu na nowo
                /*if(dynamicContentLayout != nullptr)
                {
                    qDebug()<<"ADRES dynamicContentLayout: "<<dynamicContentLayout;
                    QLayoutItem * item;
                    while((item = dynamicContentLayout->itemAt(0)) != nullptr)
                    {
                        if(item->layout() != nullptr)
                        {
                            qDebug()<<"usunięto layout "<<item->layout();
                            delete item->layout();
                        }
                    }
                    for(auto & widget : widgetsToDelete)
                    {
                        qDebug()<<"usunięto widget "<<widget;
                        delete widget;
                    }
                    widgetsToDelete.clear();

                    qDebug()<<"Ilośc widgetów w widgetsToDelete: "<<widgetsToDelete.size();
                }*/
                if(dynamicContentLayout->count() > 0)
                {
                    QLayoutItem * item = dynamicContentLayout->itemAt(0);
                    qDebug()<<"ustawiono item";
                    qDebug()<<"item-layout()->item0->widget(): "<<item->layout()->itemAt(0)->widget();
                    delete item->layout()->itemAt(0)->widget();
                    qDebug()<<"usunięto item-layout()->item0";
                    qDebug()<<"item-layout()->item1->widget(): "<<item->layout()->itemAt(0)->widget();
                    delete item->layout()->itemAt(0)->widget();
                    qDebug()<<"usunięto item-layout()->item1";
                    //delete item->layout();
                    //qDebug()<<"usunięto item-layout()";
                }
                qDebug()<<"dynamicContentLayout: "<<dynamicContentLayout;
                qDebug()<<"Ilość layoutów przed ponowną konfiguracją (prawidłowo 0): "<<dynamicContentLayout->count();
                //setupSegments();
                qDebug()<<"Ilość layoutów po ponownej konfiguracji: (prawidłowo tyle ile segmentów czyli liter / na segment): "<<dynamicContentLayout->count();
                qDebug()<<"scrollArea z ui (nie powinno się zmieniać): "<<ui->scrollAreaWidget_content;
            }
        });
    }
    //dynamicContentLayout->itemAt(0)->layout()->itemAt(1)->widget()->setFocus();
    //qDebug()<<"ustawiono fokus na 1 LineEdit";
}
// po operacji usuwania nie ma już widgetów w layoucie ale są dalej ustawione swobodnie na ekranie 0x23a79f54410, 0x23a79f54410