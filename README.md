# File Scanner Utility

This project is a file scanning utility that detects "malicious" files in a specified directory by comparing MD5 hashes against a given database. The project is written in C++ with an object-oriented approach and uses CMake as the build system. Work only for **Windows** and **Linux**.

## Prerequisites

### Ubuntu/Windows
- **CMake**
- **Clang**
- **Ninja**
- **Python3**
- **Make sure cmake, clang, clang++ and ninja are in PATH.**
---
## Use build version for Windows 11
```
.\win_11\app.exe --base tests\data\base.csv --log log.log --path .
```
---

## Build Instructions

1. Create a `build/` directory:
2. In the `build/` directory run:
    ```
    cmake -G "Ninja" ..
    cmake --build .
    ```
Or just run the script: `build.cmd (.sh)`.

After building, the following files will be available in `build/`:
- `bin/app.exe` (Windows) or `bin/app` (Linux)
- `bin/libScannerLib.dll` (Windows) or `bin/libScannerLib.so` (Linux)
- `bin/tests.exe` (Windows) or `./bin/tests` (Linux)
---

## Running App
Example for Windows;
```
.\build\bin\app.exe --base tests\data\base.csv --log log.log --path .
```
Example for Linux;
```
./build/bin/app --base tests/data/base.csv --log log.log --path .
```
---

## Example of output
```
Scan report
-----------
Root path:        /home/user/scanner/.
Database file:    /home/user/scanner/tests/data/base.csv
Log file:         /home/user/scanner/log.log

Total files scanned:           740
Malicious files found:         1
Files failed to analyze:       0
Elapsed time:                  00:00:00.000
Total data hashed:             2283 KB
```
## Running test
Example for Windows;
```
.\build\bin\tests.exe
```
Example for Linux;
```
./build/bin/tests
```

just run the script: `./run_tests.cmd (.sh)`.

## Logging
The scanner writes logs to the file specified at startup:
```
80498e2eb9baa5af90d7a266dfa72be9;Hash not in base;./lib/include/logger.h
3687b16d5bafd9e44f27afa06d50d8b3;Hash not in base;./lib/CMakeLists.txt
```