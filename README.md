[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE.md)

# What is this?

Void Engine is a small game-engine of mine. It aims to be usable, even without knowing OpenGL.

Currently implemented features include:
* OpenGL backend
* That's about it.

# Why does this exist? Aren't there enough game engines?

Yes, there are. But, I created this game engine to get a sense of what it takes to make a game engine.
This includes, but not limited to, some sort of ECS, easy customizability, handling delta-time, camera systems, etc.

For that reason, I don't expect, nor recommend, anyone to use this. It is merely a learning experience for myself.

# Building

As of now, the building process has only been tested on Linux.

## Dependencies
* C++11 compatible compiler.
* CMake v3.11+
* OpenGL 4.5+, can be acquired from Mesa or from your GPU-driver

## Building Void

Start by making a build-folder, where the compiled code will end up.

    mkdir build && cd build

Configure the build with CMake

    cmake ../ -DCMAKE_BUILD_TYPE=Debug -DVOID_ENABLE_EXAMPLES=ON

This is configure the build to compile examples, as well as the library itself. Now run make.

    make

Now, the build folder will contain both the static-library `libvoid.a`, as well as the `Examples`-folder, which will contain executable examples.

    ./Examples/01-Core/Example01
