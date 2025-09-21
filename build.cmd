if exist build (
    rmdir /S /Q build
)
mkdir build
cd build
cmake -G "Ninja" ..
cmake --build .
cd ..
pause
