@echo off
cd /d "runtime"

if not exist build (
    mkdir build
)

cd build

cmake -G Ninja ..

cmake --build .