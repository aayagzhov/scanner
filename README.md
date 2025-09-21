# File Scanner Utility

This project is a file scanning utility that detects "malicious" files in a specified directory by comparing MD5 hashes against a given database. The project is written in C++ with an object-oriented approach and uses CMake as the build system.

## Prerequisites

### Windows
- **CMake** (>= 3.20): [Download](https://cmake.org/download/)  
  Make sure to select "Add CMake to system PATH".
- **LLVM/Clang**: [Download](https://llvm.org/builds/)  
  Ensure `clang.exe` and `clang++.exe` are in your system PATH.
- **Ninja**: [Download](https://github.com/ninja-build/ninja/releases)  
  Add `ninja.exe` to your PATH.
- **Python3** (optional, >= 3.7): Needed only for GoogleTest discovery. Add `python.exe` to PATH if you want CTest to automatically run tests.

### Linux
- **CMake**: Install via your package manager, e.g., `sudo apt install cmake`.
- **Clang**: Install via your package manager, e.g., `sudo apt install clang`.
- **Ninja**: Install via your package manager, e.g., `sudo apt install ninja-build`.
- **Python3** (optional, >= 3.7): Needed only for GoogleTest discovery.
- **Make sure clang, clang++ and ninja are in PATH.**

---

## Build Instructions

1. Clone the repository:
    ```bash
    git clone <repository-url>
    cd <repository-folder>
    ```

2. Create a build directory:
    ```bash
    mkdir build
    cd build
    ```

3. Configure the project with CMake:
    ```bash
    cmake -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
    ```

4. Build the project:
    ```bash
    cmake --build .
    ```

5. After building, the following files will be available in `build/`:
    - `app/app.exe` (Windows) or `app/app` (Linux)
    - `lib/ScannerLib.dll` (Windows) or `lib/libScannerLib.so` (Linux)
    - `tests/tests.exe` (Windows) or `tests/tests` (Linux)

> **Note:** On Windows, make sure `ScannerLib.dll` is in the same folder as `app.exe` and `tests.exe` when running.

---

## Verify Components

After building, ensure all components are present:

```bash
# Windows
dir build\app
dir build\lib
dir build\tests

# Linux
ls build/app
ls build/lib
ls build/tests
