cmake_minimum_required(VERSION 2.8)
project(Delynoi)

if (APPLE)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
endif ()

# Must use GNUInstallDirs to install libraries into correct locations on all platforms
include(GNUInstallDirs)

# Targets that we develop here
enable_testing()
add_subdirectory(Delynoi)
add_subdirectory(test)