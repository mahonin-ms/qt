
cmake_minimum_required(VERSION 2.8)

project(rasu)

add_subdirectory( "tlv_srv" )
add_subdirectory( "libs" )

#find_path (ROOT_CMAKE NAMES "root.cmake" PATHS ./ )
#message("root.cmake.ROOT_CMAKE = " ${ROOT_CMAKE} )
include (./root.cmake)
