################################################
#	CMake Basic Setting
################################################
#	CMake minimu version required
cmake_minimum_required(VERSION 2.8.11)

#	Solution Name
project(Kinova_Testing)

#	Set configuration : Debug, Release
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)

################################################
#	Operation System Identification
################################################

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")



IF (CMAKE_SYSTEM_NAME MATCHES "Linux")

	MESSAGE(STATUS "current platform: Linux ")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

	MESSAGE(STATUS "current platform: Windows")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")

	MESSAGE(STATUS "current platform: FreeBSD")

ELSE ()

	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
 


MESSAGE(STATUS "###################################")


IF (WIN32)

	MESSAGE(STATUS "Call the Windows CMake files")

	include(CMakeLists.win.txt)
ELSEIF (APPLE)

	MESSAGE(STATUS "No CMakeLists for APPLE Now")

ELSEIF (UNIX)

	MESSAGE(STATUS "Now is UNIX-like OS's.")

	include(CMakeLists.unix.txt)
ENDIF ()



################################################
#	Sub Project
################################################
add_subdirectory(Finding_MICO)




