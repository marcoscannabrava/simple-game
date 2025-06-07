# Emoji Game

*   **`emoji-game/`**: Root directory containing all project files.
*   **`CMakeLists.txt`**: Modern CMake build script.
*   **`.gitignore`**: Standard ignore file for C/CMake projects.
*   **`include/`**: Contains all header files (`engine.h`, `renderer.h`, `input.h`, `game.h`), defining the public interface for each module.
*   **`src/`**: Contains all implementation files (`main.c`, `engine.c`, `renderer.c`, `input.c`, `game.c`) and the HTML shell for WASM builds.

The code adheres to the principles of simplicity and modularity, with the `Engine` struct acting as a central context to avoid global state.

### How to Build and Run

You can now compile the project using CMake and your chosen toolchain.

#### 1. Native Linux Build

**Prerequisites:**
*   A C compiler (like GCC or Clang)
*   CMake
*   Raylib installed system-wide (e.g., via your package manager `sudo apt install libraylib-dev`)

**Build Steps:**
```bash
# 1. Create a build directory
mkdir emoji-game/build
cd emoji-game/build

# 2. Configure the project with CMake
cmake ..

# 3. Compile the game
make

# 4. Run the executable
./emojigame 
```
A window should appear where you can move the rocket emoji with your arrow keys.

#### 2. WebAssembly (WASM) Build

**Prerequisites:**
*   The Emscripten SDK (`emsdk`) installed and activated.
*   Raylib installed for the Emscripten toolchain (often done via `emscripten-ports`).

**Build Steps:**
```bash
# 1. Ensure your shell is configured for Emscripten (e.g., source ./emsdk_env.sh)
# 2. Create a build directory
mkdir emoji-game/build-web
cd emoji-game/build-web

# 3. Configure the project using the emcmake wrapper and enable the WASM option
emcmake cmake .. -DWASM_BUILD=ON

# 4. Compile the project
make

# 5. Run a local web server to host the files
python3 -m http.server 8000 
```
This will generate `emojigame.html`, `emojigame.js`, and `emojigame.wasm`. Open your web browser and navigate to `http://localhost:8000/emojigame.html` to see the game running.
