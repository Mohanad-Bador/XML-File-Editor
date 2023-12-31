
// UndoRedoManager.h
#ifndef UNDOREDOMANAGER_H
#define UNDOREDOMANAGER_H

#include <QString>
#include <QStack>

class UndoRedoManager {
public:
    UndoRedoManager();

    void addToUndoStack(const QString &text);
    QString undo();
    QString redo();

private:
    QStack<QString> undoStack;
    QStack<QString> redoStack;
};

#endif // UNDOREDOMANAGER_H
