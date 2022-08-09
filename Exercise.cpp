#include "Exercise.h"

Exercise::Exercise(QString name, const QString &content, int difficulty, const QTime &bestTime, bool isCompleted) : content(content),
    name(name),
    difficulty(difficulty),
    bestTime(bestTime),
    isCompleted(isCompleted)
{}

const QString &Exercise::getName() const
{
    return name;
}

void Exercise::setName(const QString &newName)
{
    name = newName;
}

const QTime &Exercise::getBestTime() const
{
    return bestTime;
}

void Exercise::setBestTime(const QTime &newBestTime)
{
    bestTime = newBestTime;
}

bool Exercise::getIsCompleted() const
{
    return isCompleted;
}

void Exercise::setIsCompleted(bool newIsCompleted)
{
    isCompleted = newIsCompleted;
}

void Exercise::swapBestTimeParameters()
{
    bestTime.setHMS(0, bestTime.hour(), bestTime.minute(), bestTime.second());
}

int Exercise::getDifficulty() const
{
    return difficulty;
}

void Exercise::setDifficulty(int newDifficulty)
{
    difficulty = newDifficulty;
}

const QString &Exercise::getContent() const
{
    return content;
}

void Exercise::setContent(const QString &newContent)
{
    content = newContent;
}
