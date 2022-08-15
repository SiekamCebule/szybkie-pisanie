QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# ddddddddddddddd

CONFIG += file_copies
COPIES += copies
copies.files = $$files(resources)
copies.path = $$OUT_PWD
# A dd
SOURCES += \
    AddEditExerciseDialog.cpp \
    EditExercisesDialog.cpp \
    Exercise.cpp \
    ExerciseHeaderWidget.cpp \
    PracticeChoiceDialog.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    AddEditExerciseDialog.h \
    EditExercisesDialog.h \
    Exercise.h \
    ExerciseHeaderWidget.h \
    MainWindow.h \
    PracticeChoiceDialog.h

FORMS += \
    AddEditExerciseDialog.ui \
    EditExercisesDialog.ui \
    ExerciseHeaderWidget.ui \
    MainWindow.ui \
    PracticeChoiceDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    resources/exercises.json
