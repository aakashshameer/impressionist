# Make sure we're using an up-to-date version of Qt
!versionAtLeast(QT_VERSION, 5.12): error("Qt version 5.12+ required")

# Specifices the QT modules used by the project
QT = core gui widgets printsupport
greaterThan(QT_MAJOR_VERSION, 5) {
    QT += openglwidgets
}

# What the output of the build process will be (app, lib, plugin, etc.)
TEMPLATE = app

# Executable name
TARGET = Impressionist

# Directory in which the executable will be placed
OBJECTS_DIR = tmp

# General project configuration options
CONFIG -= flat
CONFIG += c++14 precompile_header force_debug_info

# List of filesnames of header files used when building the project
HEADERS += \
    src/brushes/circlebrush.h \
    src/brushes/scatteredcirclebrush.h \
    src/brushes/scatteredlinebrush.h \
    src/brushes/scatteredpointbrush.h \
    src/brushes/singlelinebrush.h \
    src/brushes/trianglebrush.h \
    src/mainwindow.h \
    src/paintview.h \
    src/glinclude.h \
    src/layer.h \
    src/vectors.h \
    src/forms/filterkerneldialog.h \
    src/forms/bilateralgaussdialog.h \
    src/forms/bilateralmeandialog.h \
    src/forms/brushdialog.h \
    src/qlabeledslider.h \
    src/exceptions.h \
    src/circularbuffer.h \
    src/brushes/brush.h \
    src/brushes/linesegmentbrush.h \
    src/brushes/pointbrush.h \
    src/filters/filter.h \
    src/rgbabuffer.h

# List of source code files to be used when building the project
SOURCES += \
    src/brushes/circlebrush.cpp \
    src/brushes/scatteredcirclebrush.cpp \
    src/brushes/scatteredlinebrush.cpp \
    src/brushes/scatteredpointbrush.cpp \
    src/brushes/singlelinebrush.cpp \
    src/brushes/trianglebrush.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/paintview.cpp \
    src/layer.cpp \
    src/glerror.cpp \
    src/forms/filterkerneldialog.cpp \
    src/forms/bilateralgaussdialog.cpp \
    src/forms/brushdialog.cpp \
    src/qlabeledslider.cpp \
    src/brushes/brush.cpp \
    src/brushes/linesegmentbrush.cpp \
    src/brushes/pointbrush.cpp \
    src/filters/filter.cpp \
    src/forms/bilateralmeandialog.cpp

# List of UI files to be processed by user interface coimpiler
FORMS += \
    src/forms/mainwindow.ui \
    src/forms/filterkerneldialog.ui \
    src/forms/bilateralgaussdialog.ui \
    src/forms/bilateralmeandialog.ui \
    src/forms/brushdialog.ui

# Specifies the include directories which should be searched when compiling the project
INCLUDEPATH += \
    "$$_PRO_FILE_PWD_/src" \
    "$$_PRO_FILE_PWD_/../Libraries" \

#Copy assets to the build directory
win32 {
    # xcopy on Windows needs forward slashes to be converted to backslashes
    SRCDIR_WIN = $$PWD/assets
    DESTDIR_WIN = $$OUT_PWD/assets
    SRCDIR_WIN ~= s,/,\\,g
    DESTDIR_WIN ~= s,/,\\,g
    copyassets.commands = $(COPY_DIR) $$system_quote($${SRCDIR_WIN}) $$system_quote($${DESTDIR_WIN})
}
linux {
    copyassets.commands = $(COPY_DIR) $$system_quote($$PWD/assets) $$system_quote($$OUT_PWD)
}
macx {
    copyassets.commands = $(COPY_DIR) $$system_quote($$PWD/assets) $$system_quote($$OUT_PWD/Impressionist.app/Contents/MacOS/)
}
first.depends = $(first) copyassets
export(first.depends)
export(copyassets.commands)
QMAKE_EXTRA_TARGETS += first copyassets

# Depend on GLEW Library
win32:CONFIG(release, debug|release): LIBS += -L$$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin -lGLEW
else:win32:CONFIG(debug, debug|release): LIBS += -L$$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin -lGLEWd
else:linux: LIBS += -L$$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin -lglew-2

INCLUDEPATH += $$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/include
DEPENDPATH += $$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin/libGLEW.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin/libGLEWd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin/GLEW.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin/GLEWd.lib
else:linux: PRE_TARGETDEPS += $$_PRO_FILE_PWD_/../Libraries/glew-2.0.0/bin/libglew-2.a

# Depend on OpenGL
win32:LIBS += -lopengl32
linux:LIBS += -lGL
macx:LIBS += -framework OpenGL -framework CoreFoundation -framework GLUT


# Enable openmp
win32:!win32-g++ {
    QMAKE_CXXFLAGS += -openmp
} else:!macx {
    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_LFLAGS += -fopenmp
}
