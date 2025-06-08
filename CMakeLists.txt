cmake_minimum_required(VERSION 3.10)
project(emoji-game LANGUAGES C)

# Option for WebAssembly build
option(WASM_BUILD "Enable WebAssembly build" OFF)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable("${CMAKE_PROJECT_NAME}" ${MY_SOURCES})


# third-party libraries
add_subdirectory(vendor/raylib)			# renderer

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib)

# WASM - Emscripten-specific settings
# To build for WASM, run from a `build` directory:
#   emcmake cmake .. -DWASM_BUILD=ON
#   cmake --build .
if(WASM_BUILD)
    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES SUFFIX ".html")

    # Necessary flags for web builds with Raylib
    target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE
        -s USE_GLFW=3
        -s ASYNCIFY
        -s LLD_REPORT_UNDEFINED
    )
    # This linker flag allows us to use a custom html template for the wasm output
    target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE
        --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/src/shell.html
    )
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "include")


# Installation (optional, but good practice)
install(TARGETS "${CMAKE_PROJECT_NAME}" DESTINATION bin)
