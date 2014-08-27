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

# The name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# mingw32 versions of the different tools
# (change these depending on your system settings)
SET(CMAKE_C_COMPILER C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/gcc)
SET(CMAKE_CXX_COMPILER C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/g++)
SET(CMAKE_RC_COMPILER C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/windres)

# add the executable
set(CFILES
Server_pp_test.cpp
../../../source/Server_pp.cpp
../../../source/OculusDK2.cpp
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

# add static libraries
add_library(LIB1 STATIC IMPORTED)
set_target_properties( LIB1 PROPERTIES IMPORTED_LOCATION "../../../lib/zxing/cpp_build/libzxing.a")
set(LIBS ${LIBS} LIB1)

add_library(LIB2 STATIC IMPORTED)
set_target_properties( LIB2 PROPERTIES IMPORTED_LOCATION "../../../lib/LibOVR/build/libovr.a")
set(LIBS ${LIBS} LIB2)

add_library(LIB3 STATIC IMPORTED)
set_target_properties( LIB3 PROPERTIES IMPORTED_LOCATION "../../../lib/i686-w64-mingw32/lib/libwsock32.a")
set(LIBS ${LIBS} LIB3)

add_library(LIB4 STATIC IMPORTED)
set_target_properties( LIB4 PROPERTIES IMPORTED_LOCATION "../../../lib/i686-w64-mingw32/lib/libws2_32.a")
set(LIBS ${LIBS} LIB4)

add_library(LIB5 STATIC IMPORTED)
set_target_properties( LIB5 PROPERTIES IMPORTED_LOCATION "../../../../boost_1_56_0/stage/lib/libboost_system-mgw48-mt-1_56.a")
set(LIBS ${LIBS} LIB5)

add_library(LIB6 STATIC IMPORTED)
set_target_properties( LIB6 PROPERTIES IMPORTED_LOCATION "../../../lib/i686-w64-mingw32/lib/libwinmm.a")
set(LIBS ${LIBS} LIB6)

add_library(LIB7 STATIC IMPORTED)
set_target_properties( LIB7 PROPERTIES IMPORTED_LOCATION "../../../lib/i686-w64-mingw32/lib/libdbghelp.a")
set(LIBS ${LIBS} LIB7)

# add opencv library
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} C:/Users/sam/Documents/User/Embeded/opencv/build/x64/MinGW)
find_package( OpenCV REQUIRED )
if (OpenCV_FOUND)
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  #set(LIBS ${LIBS} ${OpenCV_LIBS})
  message( OpenCV found! )
  #message( ${OpenCV_INCLUDE_DIRS} )
endif (OpenCV_FOUND)

target_link_libraries( try ${LIBS} )