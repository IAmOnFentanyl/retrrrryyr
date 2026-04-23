# How to Compile Aetherflow DAW

To turn this code into a working program (.exe on Windows, executable on Mac/Linux), follow these steps:

## Prerequisites
- **CMake** (3.22 or higher)
- **C++ Compiler** (Visual Studio 2022 on Windows, Clang/Xcode on Mac, GCC on Linux)
- **Internet Connection** (to download the JUCE framework automatically)

## Build Steps

1. **Open a Terminal / Command Prompt** in this folder.
2. **Create a build directory**:
   ```bash
   mkdir build
   cd build
   ```
3. **Configure the project**:
   ```bash
   cmake ..
   ```
4. **Compile**:
   - On Windows: Open the generated `Aetherflow.sln` in Visual Studio and build, or run:
     ```bash
     cmake --build . --config Release
     ```
   - On Mac/Linux:
     ```bash
     make -j4
     ```

The resulting executable will be in the `build/Aetherflow_artefacts` folder.
