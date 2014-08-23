cmake_minimum_required(VERSION 3.0)

########################################################################

OPTION(WITH_SAMPLES "Include samples" OFF)

OPTION(WITH_LOCAL_STDINT "Include local stdint.h header" OFF)

OPTION(WITH_D3D "Include Direct3D" OFF)

OPTION(WITH_GL "Include OpenGL" OFF)

OPTION(OVR_BUILD_SHIPPING "Shipping" ON)

########################################################################

# The name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# mingw32 versions of the different tools
# (change these depending on your system settings)
SET(CMAKE_C_COMPILER C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/gcc)
SET(CMAKE_CXX_COMPILER C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/g++)
SET(CMAKE_RC_COMPILER C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/windres)

FILE(GLOB_RECURSE SRCS ./*.cpp)
#FILE(GLOB_RECURSE SRCS ./Kernel/OVR_ThreadsWinAPI.cpp)
FILE(GLOB_RECURSE HDRS ./*.h)
IF (NOT WITH_D3D)
  FILE(GLOB_RECURSE SRCS_EXCL_D3D ./CAPI/D3D1X/*.cpp)
  FILE(GLOB_RECURSE HDRS_EXCL_D3D ./CAPI/D3D1X/*.h)
  LIST(REMOVE_ITEM SRCS ${SRCS_EXCL_D3D})
  LIST(REMOVE_ITEM HDRS ${HDRS_EXCL_D3D})
ENDIF (NOT WITH_D3D)
IF (NOT WITH_GL)
  FILE(GLOB_RECURSE SRCS_EXCL_GL ./CAPI/GL/*.cpp)
  FILE(GLOB_RECURSE HDRS_EXCL_GL ./CAPI/GL/*.h)
  LIST(REMOVE_ITEM SRCS ${SRCS_EXCL_GL})
  LIST(REMOVE_ITEM HDRS ${HDRS_EXCL_GL})
ENDIF (NOT WITH_GL)
FILE(GLOB INCL ./Include/*.h)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB new_list C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/i686-w64-mingw32/include/*.h*)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(INCL2)
INCLUDE_DIRECTORIES(${INCL2})
message(${INCL2})

ADD_LIBRARY(ovr
	${SRCS}
	${HDRS}
	${INCL}
	)

IF (MINGW)
  TARGET_LINK_LIBRARIES(ovr
    )
ELSE (MINGW)
  TARGET_LINK_LIBRARIES(ovr
    )
ENDIF (MINGW)