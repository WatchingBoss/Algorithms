cmake_minimum_required (VERSION 3.6)

project (sort)

if(UNIX)
  set(CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) -Wall -Wpedantic")
endif()
set(CMAKE_BUILD_TYPE Debug)

file(GLOB PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/*.c)

source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
