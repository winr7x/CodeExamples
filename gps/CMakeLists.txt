SET(TARGET Gps)

IF(USE_QT5)
    FIND_PACKAGE(Qt5Core)
ELSE(USE_QT5)
    FIND_PACKAGE(Qt4 REQUIRED QtCore)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
ENDIF(USE_QT5)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

FIND_PACKAGE(QtSerialPort REQUIRED)

SET(SOURCES
    AbstractGpsPort.cpp
    CheckSum.cpp
    GpsConnection.cpp
    GgaSentence.cpp
    GllSentence.cpp
    GpsPort.cpp
    MockGpsPort.cpp
    SentenceCommon.cpp
    ComPorts.cpp
    ComPortSettings.cpp
)

SET(HEADERS
    AbstractGpsPort.h
    CheckSum.h
    GpsConnection.h
    GgaSentence.h
    GllSentence.h
    GpsPort.h
    MockGpsPort.h
    SentenceCommon.h
    ComPorts.h
    ComPortSettings.h
)

ADD_LIBRARY(
    ${TARGET}
    ${SOURCES}
    ${HEADERS}
)

TARGET_LINK_LIBRARIES(
    ${TARGET}
    ${QT_LIBRARIES}
    ${QT_SERIAL_PORT_LIBRARIES}
)

IF(USE_QT5)
    QT5_USE_MODULES(${TARGET} Core Gui Sql)
ENDIF(USE_QT5)
