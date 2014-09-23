cmake_minimum_required (VERSION 2.6)

# mingw32 versions of the different tools
# (change these depending on your system settings)
SET(CMAKE_C_COMPILER "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/g++.exe")
SET(CMAKE_RC_COMPILER "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/bin/windres")

#reserve for setting up the compile flags in the future
#SET(GCC_COVERAGE_COMPILE_FLAGS "")
#SET(GCC_COVERAGE_LINK_FLAGS "-DBOOST_THREAD_POSIX -fno-tree-vectorize")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

#set the project source path
SET(PROJ_SRC "C:/Users/Sam/Documents/User/Embeded/ServerApp/webserver/source")

#set the library path
SET(ALL_LIBS MINGWW64 BOOST ZXING OVR WEBSOCKETPP)
SET(MINGWW64_INC "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/i686-w64-mingw32/include")
SET(MINGWW64_LIB "C:/mingw-w64/i686-4.8.1-win32-sjlj-rt_v3-rev2/mingw32/i686-w64-mingw32/lib")
SET(BOOST_INC "C:/Users/Sam/Documents/User/Embeded/ServerApp/boost_1_56_0")
SET(BOOST_LIB "C:/Users/Sam/Documents/User/Embeded/ServerApp/boost_1_56_0/stage/lib")
SET(ZXING_INC "C:/Users/Sam/Documents/User/Embeded/ServerApp/zxing/cpp/core/src")
SET(ZXING_LIB "C:/Users/Sam/Documents/User/Embeded/ServerApp/zxing/cpp_build")
SET(OVR_INC "C:/Users/Sam/Documents/User/Embeded/ServerApp/LibOVR/Src")
SET(OVR_LIB "C:/Users/Sam/Documents/User/Embeded/ServerApp/LibOVR/build")
SET(WEBSOCKETPP_INC "C:/Users/Sam/Documents/User/Embeded/ServerApp") #header only library

#extra path for packages or programs
SET(OPENCV_PATH "C:/Users/Sam/Documents/User/Embeded/ServerApp/opencv/build/x86/MinGW-W64")
SET(CODEBLOCKS_PATH "C:/Program Files (x86)/CodeBlocks")

#set the search path
FOREACH(LIB ${ALL_LIBS})
	set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${${LIB}_INC})
	set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${${LIB}_LIB})
ENDFOREACH(LIB)
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${PROJ_SRC})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${OPENCV_PATH} ${CODEBLOCKS_PATH})
