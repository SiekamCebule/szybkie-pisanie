#include "Exercise.h"

int Exercise::getPerSegment() const
{
    return perSegment;
}

void Exercise::setPerSegment(int newPerSegment)
{
    perSegment = newPerSegment;
}

Exercise::Exercise(QString name, const QString &content, int difficulty, const QTime &bestTime, bool isCompleted, int perSegment) : name(name),
    content(content),
    difficulty(difficulty),
    bestTime(bestTime),
    isCompleted(isCompleted),
    perSegment(perSegment)
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

void Exercise::removeWhitespacesFromContent()
{
    content = content.simplified();
    content.replace(" ", "");
}

void Exercise::eraseFromContentBegin(int howMany)
{
    content.erase(content.begin(), content.begin() + howMany);
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
