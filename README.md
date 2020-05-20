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
or:
```bash
cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug
# cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release
```

 then build:
```bash
# This doesn't work
# cmake --build . --config Debug --target all -j 4
"C:\Program Files\CMake\bin\cmake.EXE" --build c:/Users/sfraczek/Documents/C++/ion-drumpad/build --config Debug --target ALL_BUILD -- /maxcpucount:10

cp _deps/sfml-build/lib/Debug/*.dll app/Debug/
cp _deps/sfml-src/extlibs/bin/x64/*.dll app/Debug/
cp ../config.json app/Debug/
cp -r ../sounds app/Debug/
cp -r ../images app/Debug/

# cp _deps/sfml-build/lib/Release/*.dll app/Release/
# cp _deps/sfml-src/extlibs/bin/x64/*.dll app/Release/
# cp ../config.json app/Release/
# cp -r ../sounds app/Release/
# cp -r ../images app/Release/
```

### How to run app
```bash
#PATH=$PATH:_deps/sfml-build/lib:_deps/sfml-src/extlibs/bin/x64 ./app/app.exe
./app/Debug/app.exe
```

### How to run tests
```bash
tests/testlib.exe
```

## Ubuntu
Instruction for Ubuntu platform.

Its assumed you are always inside build dir:
```bash
Go to build directory:
```bash
mkdir build
cd build
```

## Install prerequisites
```bash
sudo apt-get install libx11-dev xorg-dev libopenal-dev libudev-dev libflac-dev libvorbis-dev libgl1-mesa-dev libfreetype6-dev
```

### How to build
First cmake configure:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```
 then build:
```bash
make -j 4
```

### How to run app
```bash
```

### How to run tests
```bash
tests/testlib
```
