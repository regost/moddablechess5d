# ModdableChess5D

A cross-platform C++ project using CMake.

## Building

### Linux

1. Ensure CMake is installed: `sudo apt-get install cmake` (or equivalent for your distro).
2. Create a build directory: `mkdir build && cd build`
3. Generate build files: `cmake ..`
4. Build: `make`

### Windows

1. Install CMake from https://cmake.org/download/
2. Open Command Prompt or PowerShell.
3. Create build directory: `mkdir build && cd build`
4. Generate build files: `cmake ..` (requires Visual Studio or MinGW)
5. Build: `cmake --build .`

## Adding Files

- Add .cpp files to `src/` directory - they will be automatically included in the build.
- Add .h files to `include/` directory - they will be automatically included via include_directories.

No need to modify CMakeLists.txt when adding new source or header files.
