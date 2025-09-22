# File Scanner Utility

This project is a file scanning utility that detects "malicious" files in a specified directory by comparing MD5 hashes against a given database. The project is written in C++ with an object-oriented approach and uses CMake as the build system. Work oly for **Windows** and **Ubuntu**.

## Prerequisites

### Windows
- **CMake** Make sure to select "Add CMake to system PATH".
- **LLVM/Clang** Ensure `clang.exe` and `clang++.exe` are in your system PATH.
- **Ninja** Add `ninja.exe` to your PATH.
- **Python3** Needed only for GoogleTest discovery. Add `python.exe` to PATH if you want CTest to automatically run tests.

### Ubuntu
- **CMake**:
- **Clang**:
- **Ninja**:
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
    - `bin/app.exe` (Windows) or `bin/app` (Ubuntu)
    - `bin/libScannerLib.dll` (Windows) or `bin/libScannerLib.so` (Ubuntu)
    - `bin/tests.exe` (Windows) or `bin/tests` (Ubuntu)
---

## Running

./build/bin/app --base tests/data/base.csv --log log.log --path .

.\build\bin\app --base tests\data\base.csv --log log.log --path .

---
## Example
