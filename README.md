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

## Integrating into Another Project

If you want to use this chess lib in your own C++ project, you can integrate it easily. Here are two common ways:

### Method 1: Using as a Subdirectory (Recommended for CMake Projects)

1. Copy the entire `moddablechess5d` folder into your project's directory, for example, into a `libs/` or `third_party/` folder.
2. In your main `CMakeLists.txt` file, add these lines:
   ```
   add_subdirectory(libs/moddablechess5d)  # Adjust the path to where you placed it
   target_link_libraries(your_target_name ModdableChess5D)  # Link the library to your executable
   ```
   This tells CMake to build ModdableChess5D as part of your project and link it to your main program.

### Method 2: Copying Files Directly

1. Copy all `.cpp` files from `src/` to your project's source directory.
2. Copy all `.h` files from `include/` to your project's include directory.
3. In your `CMakeLists.txt`, make sure to include the headers and add the sources:
   ```
   include_directories(include)  # Path to where you copied the headers
   add_executable(your_target_name your_sources.cpp copied_sources.cpp)  # Include the copied .cpp files
   ```

Make sure your project uses C++17 or later, as this project requires it.

This will make the chess engine's classes and functions available in your code.
