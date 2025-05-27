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
- How do you compile a library, and then use that library to compile an
  executable?

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
- Is there a difference in compilation time between the two?
- How can you assess performance other than compilation speed?