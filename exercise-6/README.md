# Exercise 6

**Update this README with your answers to the questions below.**

## Adding Third Party Libraries or Source Code to Your Project

- There is a new file `src/spdlog-hello-world-main.cc`
- It uses the spdlog and fmt libraries. 
  [More info here](https://github.com/gabime/spdlog) - Fast C++ logging 
  library with various sink types and formatting options
- How do you compile this file using the `g++` CLI?
  * Clone the spdlog repo into current directory
  * g++ -std=c++17 -I./spdlog/include spdlog-hello-world-main.cc -o spdlog-hello-world
- What do you need to change in your makefile to use this library?
  * Add -I./spdlog/include to CXX_FLAGS
- How many different ways can this library be added into your project?
  * clone the repo and include the readers
  * clone the repo, compile into libraries and link them
- What are the tradeoffs in the different ways?
  * including directly is easier and more cross platform compatible
  * but linking the library would lead to faster compilation times
- Why are there so many different ways to do it?
  * The different ways provide different levels of convenience to compile and different compilation times.
  
## Static Linking vs Dynamic Linking

- What are the differences between static linking and dynamic linking?
  * In static linking linking the library code is directly copied into the executable
  * In dynamic linking the executable doesn't contain all the library code.
  * Instead it refers to external shared objects.
- What are the tradeoffs?
  * In static linking the program run start up is faster but the executable file size is larger.
  * In dynamic linking program startup is slower but executable size is slower.
  * Static linking is more portable.
- How do you enable static linking or dynamic linking in your makefile?
  * The linker flags needs to have-L/path/to/mylibs -l$(LIBNAME) added to it
  * By default this results in dynamic linking
  * Add -static flag to enable static linking.

## Git Clone and Building from Source

- Where is `g++` looking for the include files and library files?
  * libraries: =/usr/lib/gcc/aarch64-linux-gnu/14/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/aarch64-linux-gnu/14/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/aarch64-linux-gnu/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/../lib/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../aarch64-linux-gnu/14/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../aarch64-linux-gnu/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../lib/:/lib/aarch64-linux-gnu/14/:/lib/aarch64-linux-gnu/:/lib/../lib/:/usr/lib/aarch64-linux-gnu/14/:/usr/lib/aarch64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../:/lib/:/usr/lib/

- How do you find out?
  * running this on the terminal: g++ -print-search-dirs

## C++ Package Managers

- Why are there so many C++ package managers?
- Which one is the best one?
- Which are the most notable ways to manage the compilation of C++ projects?