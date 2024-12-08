cmake_minimum_required(VERSION 3.15)

if(WIN32)
	message("Сборка на Windows")
	set(CMAKE_C_COMPILER mingw32-gcc)
	set(CMAKE_CXX_COMPILER mingw32-g++)
elseif(APPLE)
	message("Сборка на macOS")
	set(CMAKE_C_COMPILER clang)
	set(CMAKE_CXX_COMPILER clang++)
elseif(UNIX)
	message("Сборка на Linux")
	set(CMAKE_C_COMPILER gcc)
	set(CMAKE_CXX_COMPILER g++)
else()
	message(FATAL_ERROR "Неизвестная операционная система")
endif()


project(sapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
	-Wall -Wextra -pedantic
)

include_directories(src/game)
include_directories(src/glcore)
include_directories(src/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../cmakebin)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/**/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
#message("PROJECT_SOURCE_DIR: ${SOURCES}")

if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
	target_link_libraries(${PROJECT_NAME} mingw32 gcc_s_dw2-1 SDL2main SDL2 opengl32 glu32)
else()
	target_link_libraries(${PROJECT_NAME} GL GLU SDL2)
endif()
