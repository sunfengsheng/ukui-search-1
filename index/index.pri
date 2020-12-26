INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/chinesecharacterstopinyin.h \
    $$PWD/document.h \
    $$PWD/index-generator.h \
#    $$PWD/inotify-manager.h \
    $$PWD/inotify.h \
    $$PWD/messagelist-manager.h \
    $$PWD/traverse_bfs.h \
    $$PWD/messagelist-manager.h \
    $$PWD/text-content-indexer.h

SOURCES += \
    $$PWD/chinesecharacterstopinyin.cpp \
    $$PWD/document.cpp \
    $$PWD/index-generator.cpp \
#    $$PWD/inotify-manager.cpp \
    $$PWD/inotify.cpp \
    $$PWD/messagelist-manager.cpp \
    $$PWD/test-Inotify-Manager.cpp \
    $$PWD/traverse_bfs.cpp \
    $$PWD/text-content-indexer.cpp
