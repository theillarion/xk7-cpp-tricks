cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(xk7_app VERSION 0.0.1 DESCRIPTION "XK7 Test application" LANGUAGES CXX C)

# Let applications to search for libraries in their working directory
SET(CMAKE_INSTALL_RPATH "$ORIGIN/libs")
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

file(GLOB_RECURSE source "src/*.cpp")

set(include ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(lib dl xk7_headers)

add_executable(${PROJECT_NAME} ${source})
target_include_directories(${PROJECT_NAME} PRIVATE ${include})
target_link_libraries(${PROJECT_NAME} PRIVATE ${lib})