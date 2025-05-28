# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cc` and 
  `tcp_echo_client.cc` to separate `.h` and `.cc` files
- How would you compile from the command line?
  * Add the common .cpp file to the compilation command
- How would you compile using make?
  * Add the common .cpp file to the compilation command in the make file
- How would you compile using VS Code?
  * By setting up a tasks.json file and inclusing the other .cpp file to it to compile as an arg

### Compiling vs Linking

- What is the difference between compiling and linking in C++?
  * Compiling converts all .cc/.cpp into object files(.o)
  * Linking combines all object files into an executable
- What is the difference between creating an executable and creating a 
  library?
  * Executables are standalone programs that can be executed as a single file.
  * Libraries contain code which can be combined with other programs. 
- How do you compile a library, and then use that library to compile an
  executable?
  * g++ -c network_utils.cpp
  * ar rcs network_utils.a network_utils.o
  * g++ tcp_echo_client.cpp network_utils.a -o client.out

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
  * Depends on the use cases. Usually to make the more code readable it is beneficial to group related functions and seperate different functions across files.
  * Ideal to make sure no functions are repeated.
- Is there a difference in compilation time between the two?
  * Splitting into two files increases compilation time.
- How can you assess performance other than compilation speed?
  * The size of the compile file using `du -sh <filename>`
  * Maximum RAM usage during compilation can be assessed using `time -v <compilation command>` and looking at Maximum resident set size
