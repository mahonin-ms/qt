cmake_minimum_required(VERSION 2.8)

project(common)

# Подключение корневого файла с правилами
find_path (ROOT_CMAKE NAMES "root.cmake" PATHS ./ )
include( ${ROOT_CMAKE}/root.cmake )



find_package(QT NAMES Qt5 COMPONENTS Core Xml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Xml REQUIRED)
#find_package(Qt5Xml)

# Пути для копирования результата
set( EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE} )
set( LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE} )

message("shared_libs = " ${shared_libs} )
set(INSTALL 
#	../../tlv_srv/libs
        ${shared_libs}/shared_libs
	)

set( PUBLIC_HEADERS
	src/common.h
   )

# Заголовочные файлы.
set( PRIVATE_HEADERS
                    src/common.h
   )

# Исходные файлы.
set( SOURCE_FILES
                    src/common.cpp
   )

# Цель сборки.
add_library( ${PROJECT_NAME} SHARED ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCE_FILES} )

##################################################
# Подключаемые библиотеки.
set( ADDITIONAL_LIBRARIES
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Xml
)

target_link_libraries( ${PROJECT_NAME} ${ADDITIONAL_LIBRARIES} )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy ${LIBRARY_OUTPUT_PATH}/lib${PROJECT_NAME}.so ${INSTALL}
  COMMENT "Copying lib${PROJECT_NAME}.so to ${INSTALL}"
  COMMAND "${CMAKE_COMMAND}" -E remove -f ${INSTALL}/headers/common.h
  COMMENT "rm ${PUBLIC_HEADERS} to ${INSTALL}/headers"
  COMMAND "${CMAKE_COMMAND}" -E copy ${PROJECT_SOURCE_DIR}/src/*.h ${INSTALL}/headers/
  COMMENT "Copying ${PUBLIC_HEADERS} to ${INSTALL}/headers"
  )
