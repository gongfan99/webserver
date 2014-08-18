cmake_minimum_required (VERSION 2.6)
project (try)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/TryConfigure.h.in"
#  "${PROJECT_BINARY_DIR}/TryConfigure.h"
#  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ../../../source/)

# add the executable
#add_executable(try AdapterForImageProduce_test.cpp ImageProduceCamera.c)
set(CFILES ${CFILES} ImageDecoderQR_test.cpp)
set(CFILES ${CFILES} ../../../source/utils.cpp)
set(CFILES ${CFILES} ../../../source/ImageProduceCamera.c)
set(CFILES ${CFILES} ../../../source/ImageDecoderQR.cpp)
add_executable(try ${CFILES})
#add_executable(try ImageDecoderQR_test.cpp ../../../source/ImageProduceCamera.c ../../../source/ImageDecoderQR.cpp)

add_library(LIB1 STATIC IMPORTED)
add_library(LIB2 STATIC IMPORTED)
add_library(LIB3 STATIC IMPORTED)

find_library(LIB1_ADDRESS libgcc.a "C:/MinGW/lib/gcc/mingw32/4.8.1")
find_library(LIB2_ADDRESS libstdc++.a "C:/MinGW/lib/gcc/mingw32/4.8.1")
find_library(LIB3_ADDRESS libzxing.a "../../../lib/zxing/cpp_build")

set_target_properties( LIB1 PROPERTIES IMPORTED_LOCATION "${LIB1_ADDRESS}" )
set_target_properties( LIB2 PROPERTIES IMPORTED_LOCATION "${LIB2_ADDRESS}" )
set_target_properties( LIB3 PROPERTIES IMPORTED_LOCATION "${LIB3_ADDRESS}" )

set(LIBS ${LIBS} LIB1 LIB2 LIB3)

include_directories( "../../../source" )
include_directories( "../../../lib/zxing/cpp/core/src" )

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} C:/Users/sam/Documents/User/Embeded/opencv/build/x64/MinGW)

find_package( OpenCV REQUIRED )
if (OpenCV_FOUND)
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  set(LIBS ${LIBS} ${OpenCV_LIBS})
  message( OpenCV found! )
  message( ${OpenCV_INCLUDE_DIRS} )
endif (OpenCV_FOUND)

target_link_libraries( try ${LIBS} )