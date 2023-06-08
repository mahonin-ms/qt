cmake_minimum_required(VERSION 3.5)

project(tlv_srv LANGUAGES CXX)

find_path (ROOT_CMAKE NAMES "root.cmake" PATHS ./ )
include( ${ROOT_CMAKE}/root.cmake )



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L ../shared_libs")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets Core Network Xml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Network Xml REQUIRED)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../shared_libs/headers )


message("CMAKE_BUILD_TYPE=" ${CMAKE_BUILD_TYPE})
message("CMAKE_CXX_FLAGS=" ${CMAKE_CXX_FLAGS})

set(PRIVATE_HEADERS
    src/server.h
    src/model/db/db.h
    src/model/painter.h
    )

set( SOURCE_FILES
    src/main.cpp
    src/server.cpp
    src/model/db/db.cpp
    src/model/painter.cpp
    resources/config
    )


set( FORMS
    forms/variables.ui
    forms/variables.cpp
    forms/variables.h )

  add_executable(tlv_srv
    ${SOURCE_FILES}
    ${PRIVATE_HEADERS}
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${FORMS}
  )

set( LIBS
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Xml
    common
    )
target_link_libraries(tlv_srv PRIVATE ${LIBS}
    )

