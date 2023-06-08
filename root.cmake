cmake_minimum_required(VERSION 2.8)

if( "${CMAKE_BUILD_TYPE}" STREQUAL "" )
        set(CMAKE_BUILD_TYPE Debug)
endif()

set(QT_VERSION_MAJOR 5)

set( EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE} )
set( LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE} )

set(MY_CXX_FLAGS "-std=c++14 -D${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS}")

find_path (SHARED_LIBS NAMES "shared_libs" PATHS ./ )
#message("root.cmake.SHARED_LIBS = " ${SHARED_LIBS} )

set( shared_libs ${SHARED_LIBS} )
