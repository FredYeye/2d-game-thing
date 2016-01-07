cmake_minimum_required(VERSION 2.8.3)

set(project_name 2dtest)
project(${project_name})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_path(GLFW_INCLUDE GLFW/glfw3.h PATHS NO_DEFAULT_PATH DOC "GLFW include path")
find_path(GLFW_LIB glfw3.dll PATHS NO_DEFAULT_PATH DOC "GLFW lib path")
include_directories(${GLFW_INCLUDE})
include_directories(${GLFW_LIB})
find_library(GLFW_LIBRARY "glfw3" HINTS ${GLFW_LIB})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native")
add_definitions(-lglfw3 -lopengl32)

set(source_files
	src/main.cpp
	src/game.cpp
	src/entity.cpp
	src/file.cpp
	src/render.cpp
	src/gl_core/gl_core_3_3.c
	)

set(header_files
	src/main.hpp
	src/game.hpp
	src/entity.hpp
	src/file.hpp
	src/render.hpp
	src/animations.hpp
	src/gl_core/gl_core_3_3.h
	)

add_executable(${project_name} ${header_files} ${source_files})
target_link_libraries(${project_name} ${GLFW_LIBRARY} opengl32)


set(BUILD_IC TRUE CACHE BOOL "build rgb888->rgba555 converter")
IF(BUILD_IC)
set(source_files
	src/imageconvert/main.cpp
	src/file.cpp
	)

set(header_files
	src/imageconvert/main.hpp
	src/file.hpp
	)

add_executable(imageconvert ${header_files} ${source_files})
endif(BUILD_IC)
