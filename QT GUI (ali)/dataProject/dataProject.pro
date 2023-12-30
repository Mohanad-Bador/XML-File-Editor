QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Functions.cpp \
    Graph.cpp \
    MyUniqueCompression.cpp \
    Post.cpp \
    UndoRedoManager.cpp \
    User.cpp \
    XMLParser.cpp \
    XMLtoTree.cpp \
    consistency.cpp \
    formatting.cpp \
    globals.cpp \
    main.cpp \
    mainwindow.cpp \
    tree.cpp \
    xml_parser.cpp \
    xmltojson.cpp

HEADERS += \
    Functions.h \
    Graph.h \
    MyUniqueCompression.h \
    Post.h \
    Tree.h \
    UndoRedoManager.h \
    User.h \
    XMLParser.h \
    XMLtoTree.h \
    consistency.h \
    formatting.h \
    globals.h \
    mainwindow.h \
    xml_parser.h \
    xmltojson.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ali.dot.png
