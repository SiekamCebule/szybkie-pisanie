#pragma once

#include <QString>
#include <QTime>

class Exercise
{
    QString name;
    QString content;
    int difficulty;
    QTime bestTime;
    bool isCompleted;
    int perSegment;

public:
    Exercise(const QString name = "", const QString &content = "", int difficulty = 1, const QTime &bestTime = QTime(0, 0, 0, 0), bool isCompleted = false, int perSegment = 0);

    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getContent() const;
    void setContent(const QString &newContent);
    int getDifficulty() const;
    void setDifficulty(int newDifficulty);
    const QTime &getBestTime() const;
    void setBestTime(const QTime &newBestTime);
    bool getIsCompleted() const;
    void setIsCompleted(bool newIsCompleted);
    int getPerSegment() const;
    void setPerSegment(int newPerSegment);

    enum Difficulty{
        Easy = 1,
        Medium,
        Hard
    };

    void swapBestTimeParameters();
    void removeWhitespacesFromContent();
    void eraseFromContentBegin(int howMany);
};

