cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER clang++-3.6)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(CMAKE_EXE_LINKER_FLAGS "")

## Use the variable PROJECT_NAME for changing the target name
set( PROJECT_NAME "RubikCube" )

## Set our project name
project(${PROJECT_NAME})

aux_source_directory(src/ SRCS)

## Define the executable
add_executable(${PROJECT_NAME} ${SRCS})

add_custom_target(run
  COMMAND ${PROJECT_NAME}
  COMMENT "Runing 'RubikCube' programm"
  VERBATIM
)