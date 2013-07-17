QT += widgets webkit webkitwidgets


HEADERS     = dragwidget.h \
    menu.h \
    apiController.h \
    widget.h
RESOURCES   = draggableicons.qrc
SOURCES     = dragwidget.cpp \
              main.cpp \
    menu.cpp \
    apiController.cpp \
    widget.cpp

# install
target.path = /home/vcupif
INSTALLS += target

FORMS +=
