cmake_minimum_required (VERSION 2.6)
project (try)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/TryConfigure.h.in"
  "${PROJECT_BINARY_DIR}/TryConfigure.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


# add the executable
add_executable(try ImageProduce_test.c ImageProduce.c)

add_library(LIB1 STATIC IMPORTED)
add_library(LIB2 STATIC IMPORTED)

find_library(LIB1_ADDRESS libgcc.a "C:/MinGW/lib/gcc/mingw32/4.8.1")
find_library(LIB2_ADDRESS libstdc++.a "C:/MinGW/lib/gcc/mingw32/4.8.1")

set_target_properties( LIB1 PROPERTIES IMPORTED_LOCATION "${LIB1_ADDRESS}" )
set_target_properties( LIB2 PROPERTIES IMPORTED_LOCATION "${LIB2_ADDRESS}" )

set(LIBS ${LIBS} LIB1 LIB2)

find_package( OpenCV REQUIRED )
if (OpenCV_FOUND)
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  set(LIBS ${LIBS} ${OpenCV_LIBS})
  message( OpenCV found! )
  message( ${OpenCV_INCLUDE_DIRS} )
endif (OpenCV_FOUND)

target_link_libraries( try ${LIBS} )