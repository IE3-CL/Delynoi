SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

set(SOURCE_FILES TimeSquareTestMain.cpp)

add_executable(DelynoiTest ${SOURCE_FILES})
target_link_libraries(DelynoiTest Delynoi)

get_target_property(MAIN_CFLAGS DelynoiTest COMPILE_OPTIONS)