# Add more folders to ship with the application, here
folder_01.source = qml/qtgui
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE68F86F5

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

LIBS += -lpthread -lwiringPi -L/usr/lib

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    ../source/ServoControl.c \
    ../source/PumpControllingSystem.c \
    ../source/PortIO_Thread.c \
    ../source/HardwareControl.c \
    ../source/debounce.c \
    ../source/CupSenseT.c \
    UserButtons.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    ../source/ServoControl.h \
    ../source/PumpControllingSystem.h \
    ../source/PortIO_Thread.h \
    ../source/HardwareControl.h \
    ../source/defs.h \
    ../source/debounce.h \
    ../source/CupSenseT.h \
    UserButtons.h
