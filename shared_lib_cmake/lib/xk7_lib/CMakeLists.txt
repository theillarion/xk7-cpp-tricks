cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(xk7_api VERSION 0.0.1 DESCRIPTION "XK7 Test library" LANGUAGES CXX C)

# set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -Weffc++")

# Sources
set(source ${CMAKE_CURRENT_SOURCE_DIR}/src/my_api.c)

# Internal library
set(lib xk7_internal_lib)

# Headers
set(public_include ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(include ${CMAKE_CURRENT_SOURCE_DIR}/src ${public_include})

add_subdirectory(lib)

###################
# Headers library #
###################
add_library(xk7_headers INTERFACE)
add_library(xk7_headers::xk7_headers ALIAS xk7_headers)

target_include_directories(xk7_headers INTERFACE $<BUILD_INTERFACE:${public_include}>)

##################
# Shared library #
##################
add_library(${PROJECT_NAME} SHARED ${source})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})

target_compile_options(${PROJECT_NAME} PRIVATE -fvisibility=hidden)
target_link_options(${PROJECT_NAME} PRIVATE LINKER:--exclude-libs=ALL)

target_include_directories(${PROJECT_NAME} PRIVATE ${include})
target_link_libraries(${PROJECT_NAME} PRIVATE ${lib})

# Library interface headers
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${public_include}>)