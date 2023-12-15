QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/include/vtk-9.3/

CONFIG += debug_and_release
CONFIG(debug,debug|release){
LIBS += -L$$PWD/lib -lvtkCommonColor-9.3d
LIBS += -L$$PWD/lib -lvtkCommonCore-9.3d
LIBS += -L$$PWD/lib -lvtkCommonMath-9.3d
LIBS += -L$$PWD/lib -lvtkCommonDataModel-9.3d
LIBS += -L$$PWD/lib -lvtkCommonExecutionModel-9.3d
LIBS += -L$$PWD/lib -lvtkCommonMisc-9.3d
LIBS += -L$$PWD/lib -lvtkCommonTransforms-9.3d
LIBS += -L$$PWD/lib -lvtkFiltersCore-9.3d
LIBS += -L$$PWD/lib -lvtkFiltersModeling-9.3d
LIBS += -L$$PWD/lib -lvtkFiltersSources-9.3d
LIBS += -L$$PWD/lib -lvtkGUISupportQt-9.3d
LIBS += -L$$PWD/lib -lvtkImagingCore-9.3d
LIBS += -L$$PWD/lib -lvtkImagingSources-9.3d
LIBS += -L$$PWD/lib -lvtkInteractionImage-9.3d
LIBS += -L$$PWD/lib -lvtkInteractionStyle-9.3d
LIBS += -L$$PWD/lib -lvtkInteractionWidgets-9.3d
LIBS += -L$$PWD/lib -lvtkIOCore-9.3d
LIBS += -L$$PWD/lib -lvtkIOExport-9.3d
LIBS += -L$$PWD/lib -lvtkIOImage-9.3d
LIBS += -L$$PWD/lib -lvtkIOImport-9.3d
LIBS += -L$$PWD/lib -lvtkIOLegacy-9.3d
LIBS += -L$$PWD/lib -lvtkjpeg-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingAnnotation-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingCore-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingFreeType-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingGL2PSOpenGL2-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingImage-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingOpenGL2-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingVolume-9.3d
LIBS += -L$$PWD/lib -lvtkRenderingVolumeOpenGL2-9.3d
LIBS += -L$$PWD/lib -lvtksys-9.3d
TARGET = helloVTKd
CONFIG += console
}
CONFIG(release,debug|release){
LIBS += -L$$PWD/lib -lvtkCommonColor-9.3
LIBS += -L$$PWD/lib -lvtkCommonCore-9.3
LIBS += -L$$PWD/lib -lvtkCommonMath-9.3
LIBS += -L$$PWD/lib -lvtkCommonDataModel-9.3
LIBS += -L$$PWD/lib -lvtkCommonExecutionModel-9.3
LIBS += -L$$PWD/lib -lvtkCommonMisc-9.3
LIBS += -L$$PWD/lib -lvtkCommonTransforms-9.3
LIBS += -L$$PWD/lib -lvtkFiltersCore-9.3
LIBS += -L$$PWD/lib -lvtkFiltersModeling-9.3
LIBS += -L$$PWD/lib -lvtkFiltersSources-9.3
LIBS += -L$$PWD/lib -lvtkGUISupportQt-9.3
LIBS += -L$$PWD/lib -lvtkImagingCore-9.3
LIBS += -L$$PWD/lib -lvtkImagingSources-9.3
LIBS += -L$$PWD/lib -lvtkInteractionImage-9.3
LIBS += -L$$PWD/lib -lvtkInteractionStyle-9.3
LIBS += -L$$PWD/lib -lvtkInteractionWidgets-9.3
LIBS += -L$$PWD/lib -lvtkIOCore-9.3
LIBS += -L$$PWD/lib -lvtkIOExport-9.3
LIBS += -L$$PWD/lib -lvtkIOImage-9.3
LIBS += -L$$PWD/lib -lvtkIOImport-9.3
LIBS += -L$$PWD/lib -lvtkIOLegacy-9.3
LIBS += -L$$PWD/lib -lvtkjpeg-9.3
LIBS += -L$$PWD/lib -lvtkRenderingAnnotation-9.3
LIBS += -L$$PWD/lib -lvtkRenderingCore-9.3
LIBS += -L$$PWD/lib -lvtkRenderingFreeType-9.3
LIBS += -L$$PWD/lib -lvtkRenderingGL2PSOpenGL2-9.3
LIBS += -L$$PWD/lib -lvtkRenderingImage-9.3
LIBS += -L$$PWD/lib -lvtkRenderingOpenGL2-9.3
LIBS += -L$$PWD/lib -lvtkRenderingVolume-9.3
LIBS += -L$$PWD/lib -lvtkRenderingVolumeOpenGL2-9.3
LIBS += -L$$PWD/lib -lvtksys-9.3
TARGET = helloVTK
}

DESTDIR = $$PWD/bin/

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    utils.cpp

HEADERS += \
    header.h \
    mainwindow.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
