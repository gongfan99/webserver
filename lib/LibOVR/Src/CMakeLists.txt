cmake_minimum_required(VERSION 3.0)

########################################################################

OPTION(WITH_SAMPLES "Include samples" OFF)

OPTION(WITH_LOCAL_STDINT "Include local stdint.h header" OFF)

OPTION(WITH_D3D "Include Direct3D" OFF)

OPTION(WITH_GL "Include OpenGL" OFF)

OPTION(OVR_BUILD_SHIPPING "Shipping" ON)

########################################################################

include_directories("../../i686-w64-mingw32/include")

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
FILE(GLOB INCL ./Include/*.h ../../MinGW64/include/*.h)
FILE(GLOB_RECURSE INCL2 ../../i686-w64-mingw32/include/*.h*)

get_filename_component(INCL3 "${INCL2}" PATH)
include_directories(${INCL3})

ADD_LIBRARY(ovr
	${SRCS}
	${HDRS}
	${INCL}
	${INCL2}
	)

IF (MINGW)
  TARGET_LINK_LIBRARIES(ovr
    )
ELSE (MINGW)
  TARGET_LINK_LIBRARIES(ovr
    )
ENDIF (MINGW)