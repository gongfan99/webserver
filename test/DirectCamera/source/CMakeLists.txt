cmake_minimum_required (VERSION 2.6)

# mingw32 versions of the different tools
# (change these depending on your system settings)
SET(CMAKE_C_COMPILER "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/g++.exe")
SET(CMAKE_RC_COMPILER "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/windres")

SET(GCC_COVERAGE_COMPILE_FLAGS "")
#SET(GCC_COVERAGE_LINK_FLAGS "-DBOOST_THREAD_POSIX -fno-tree-vectorize")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
message( ${CMAKE_CXX_FLAGS} )

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

# The name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# add the executable
set(CFILES
DirectCamera_test.cpp
../../../source/ImageProduceCamera.c
../../../source/DirectCamera.cpp
)
add_executable(try ${CFILES})

# add include directories
set(INCLUDE_DIR
../../../source
../../../lib
../../../lib/zxing/cpp/core/src
../../../lib/i686-w64-mingw32/lib/include
../../../../boost_1_56_0
)
include_directories( ${INCLUDE_DIR} )

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "../../../../../opencv/build/x64/MinGW")
find_package( OpenCV REQUIRED )
if (OpenCV_FOUND)
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  set(LIBS ${LIBS} ${OpenCV_LIBS})
  message( OpenCV found! )
  #message( ${OpenCV_INCLUDE_DIRS} )
endif (OpenCV_FOUND)

target_link_libraries( try ${LIBS} )