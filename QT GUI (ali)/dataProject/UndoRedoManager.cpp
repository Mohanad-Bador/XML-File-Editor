// UndoRedoManager.cpp
#include "UndoRedoManager.h"

UndoRedoManager::UndoRedoManager() {
    // Constructor: Initialize the undo and redo stacks
}

void UndoRedoManager::addToUndoStack(const QString &text) {
    undoStack.push(text);
    redoStack.clear();  // Clear redo stack when a new change is made
}

QString UndoRedoManager::undo() {
    if (!undoStack.isEmpty()) {
        QString currentText = undoStack.pop();
        redoStack.push(currentText);
        return undoStack.isEmpty() ? QString() : undoStack.top();
    }
    return QString();
}

QString UndoRedoManager::redo() {
    if (!redoStack.isEmpty()) {
        QString currentText = redoStack.pop();
        undoStack.push(currentText);
        return currentText;
    }
    return QString();
}
