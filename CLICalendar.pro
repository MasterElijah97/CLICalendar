######################################################################
# Automatically generated by qmake (3.1) Tue Sep 29 00:45:23 2020
######################################################################

TEMPLATE = app
TARGET = CLICalendar
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/black_magic.h \
           src/commandMonitor.h \
           src/day.h \
           src/deal.h \
           src/idatabase.h \
           src/important.h \
           src/iuniqueid.h \
           src/iversion.h \
           src/MD5.h \
           src/note.h \
           src/session.h \
           src/sqlite3.h \
           src/sqlite_orm.h \
           src/task.h \
           src/user.h \
           src/visitor.h
SOURCES += main.cpp \
           src/commandMonitor.cpp \
           src/day.cpp \
           src/deal.cpp \
           src/idatabase.cpp \
           src/important.cpp \
           src/iuniqueid.cpp \
           src/iversion.cpp \
           src/MD5.cpp \
           src/note.cpp \
           src/session.cpp \
           src/sqlite3.c \
           src/task.cpp \
           src/user.cpp \
           src/visitor.cpp
