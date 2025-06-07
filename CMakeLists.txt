cmake_minimum_required(VERSION 3.10)
project(emoji-game LANGUAGES C)

# Set C standard to C23
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Option for WebAssembly build
option(WASM_BUILD "Enable WebAssembly build" OFF)

# Find Raylib using a modern CMake approach
find_package(raylib CONFIG REQUIRED)

# Add the include directory
include_directories(include)

# Add the executable target
add_executable(emojigame
    src/main.c
    src/engine.c
    src/renderer.c
    src/input.c
    src/game.c
)

# Link Raylib to the target
target_link_libraries(emojigame PRIVATE raylib::raylib)
target_include_directories(emojigame PRIVATE include)

if(WASM_BUILD)
    # Emscripten-specific settings
    # To build for WASM, run from a `build` directory:
    #   emcmake cmake .. -DWASM_BUILD=ON
    #   cmake --build .
    set_target_properties(emojigame PROPERTIES SUFFIX ".html")

    # Necessary flags for web builds with Raylib
    target_compile_options(emojigame PRIVATE
        -s USE_GLFW=3
        -s ASYNCIFY
        -s LLD_REPORT_UNDEFINED
    )
    # This linker flag allows us to use a custom html template for the wasm output
    target_link_options(emojigame PRIVATE
        --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/src/shell.html
    )

endif()

# Installation (optional, but good practice)
install(TARGETS emojigame DESTINATION bin)
