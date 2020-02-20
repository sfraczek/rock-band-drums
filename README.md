# ION-DrumPad

Connect your Ion Drum Rocker to your computer and play like on a real drum-kit.

## Windows
Instructions for Windows platform.

Its assumed you are always inside build dir:
```bash
Go to build directory:
```bash
mkdir build
cd build
```
### How to build
First cmake configure:
```bash
cmake .. -G "MinGW Makefiles"
```
if it doesn't work, add `-DCMAKE_SH="CMAKE_SH-NOTFOUND"`

 then build:
```bash
"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Users/sfraczek/Documents/C++/ion-drumpad/build --config Debug --target all
```

### How to run app
```bash
PATH=$PATH:_deps/sfml-build/lib:_deps/sfml-src/extlibs/bin/x64 ./app/app.exe
```

### How to run tests
```bash
tests/testlib.exe
```