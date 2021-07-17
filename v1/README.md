# T3Vtech

This is a 3D game engine.

Currently I am developing its basics and its first renderer, which happens to be a software rasterizer.
The software rasterizer supports multithreading and single threading.

## Examples

This is an example rendered with the software rasterizer of the engine.

![image info](screenshots/21.06.23-some-sky.png)

## Compilation

For a first time compilation it is necessary to have SDL2, CMake and a compiler, which can compile
C++-20. I use G++-11 but others will work as well.

For the first time compilation you need the following commands:

```
git clone git@github.com:tevoran/T3Vtech.git
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

Starting with the second compilation you simply need:

```
cmake ..
make
```
