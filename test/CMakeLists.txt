cmake_minimum_required(VERSION 2.6)
include(../Common.cmake NO_POLICY_SCOPE)

project (test)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
 "${PROJECT_SOURCE_DIR}/TestConfigure.hpp.in"
 "${PROJECT_BINARY_DIR}/TestConfigure.hpp"
 )
configure_file (
"${PROJ_SRC}/OzoConfigure.hpp.in"
"${PROJECT_BINARY_DIR}/OzoConfigure.hpp"
)
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


# add include directories
include_directories( ${CMAKE_INCLUDE_PATH} )

# create libraries
SET(C_FILES
	SourceCamera.cpp
	DecoderQR.cpp
	OculusDK2.cpp
	Server_pp.cpp
	utils.cpp
)
FOREACH(C_FILE ${C_FILES})
	SET(C_FILES2 ${C_FILES2} ${PROJ_SRC}/${C_FILE})
ENDFOREACH(C_FILE)
add_library(ozo STATIC ${C_FILES2})
set(LIBS ${LIBS} ozo)

# add external static libraries, do not put "lib" as prefix or ".a" as suffix
set(LibFiles
zxing
ovr
wsock32
ws2_32
winmm
dbghelp
boost_system-mgw48-mt-1_56
boost_thread-mgw48-mt-1_56
boost_chrono-mgw48-mt-1_56
)
FOREACH(LIB ${LibFiles})
	find_library(LOCATION_${LIB} NAMES ${LIB})
	message("Library ${LOCATION_${LIB}} is added!")
	add_library(LIB_${LIB} STATIC IMPORTED)
	set_target_properties( LIB_${LIB} PROPERTIES IMPORTED_LOCATION "${LOCATION_${LIB}}")
	set(LIBS ${LIBS} LIB_${LIB})
ENDFOREACH(LIB)

# add packages
find_package( OpenCV REQUIRED )
if (OpenCV_FOUND)
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  set(LIBS ${LIBS} ${OpenCV_LIBS})
  message( "OpenCV found!" )
  #message( ${OpenCV_INCLUDE_DIRS} )
endif (OpenCV_FOUND)

# add the executable
add_executable(DecoderQR_test DecoderQR_test.cpp)
add_executable(OculusDK2_test OculusDK2_test.cpp)

target_link_libraries( DecoderQR_test ${LIBS} )
target_link_libraries( OculusDK2_test ${LIBS} )