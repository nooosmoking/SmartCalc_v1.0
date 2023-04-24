cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(SmartCalc)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

set(RAYGUI_VERSION 3.2)
find_package(raygui ${RAYGUI_VERSION} QUIET) # QUIET or REQUIRED

include(ExternalProject)
FetchContent_Declare(
                raygui
                URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.tar.gz
    )
FetchContent_MakeAvailable(raygui)
include_directories(${raygui_SOURCE_DIR}/src)
# Directory Variables
set(RAYGUI_ROOT ${raygui_SOURCE_DIR})
set(RAYGUI_SRC ${raygui_SOURCE_DIR}/src)
set(RAYGUI_EXAMPLES ${raygui_SOURCE_DIR}/examples)
add_library(raygui INTERFACE)
file(GLOB raygui_sources ${RAYGUI_SRC}/*.h)
set(RAYGUI_HEADERS ${raygui_sources})
# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# Our Project
set(SOURCE_EXE main.c validate.c calculate.c string_edit.c array_stack_help.c)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} raylib raygui)

target_compile_definitions(${PROJECT_NAME} PUBLIC IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/img/")

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
