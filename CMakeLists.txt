cmake_minimum_required(VERSION 3.10)
project(simple-game LANGUAGES C)

# third-party libraries
add_subdirectory(vendor/raylib)

# collect all source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "src/*.c")

# collect all resource files
file(GLOB MY_RESOURCES "assets/*")

# set the executable name
add_executable("${CMAKE_PROJECT_NAME}" ${MY_SOURCES})

# link libraries
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "include")


option(WASM_BUILD "Enable WebAssembly build" OFF)

# Emscripten/WebAssembly (WASM) build settings per Raylib documentation - https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)
if(WASM_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    string(REPLACE "-rdynamic" "" CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS}")
    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "--preload-file assets/")
endif()


# copy assets to build directory
file(COPY ${MY_RESOURCES} DESTINATION "assets/")

# Installation (optional, but good practice)
install(TARGETS "${CMAKE_PROJECT_NAME}" DESTINATION bin)