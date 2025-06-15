cmake_minimum_required(VERSION 3.10)
project(simple-game LANGUAGES C)

option(WASM_BUILD "Enable WebAssembly build" OFF)

# Wasm is half-working. It cannot find image files
# Emscripten/WebAssembly build settings per Raylib documentation - https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)
if(WASM_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    string(REPLACE "-rdynamic" "" CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS}")
endif()


# third-party libraries
add_subdirectory(vendor/raylib)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable("${CMAKE_PROJECT_NAME}" ${MY_SOURCES})

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib)

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "include")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

# Installation (optional, but good practice)
install(TARGETS "${CMAKE_PROJECT_NAME}" DESTINATION bin)
