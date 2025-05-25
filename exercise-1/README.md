# Exercise 1

**Update this README with your answers to the questions below.**

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
- How can you tell if the source of your information is good?
- How would you define "good" in this situation?

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
- What are the most important command line arguments to learn for `g++`?
  * -c, -o, -Wall, -Wextra, -g, -std=c++xx, -Ox
- What is the difference between debug vs release versions?
  * Debug versions are compiled to run the code step by step suitable for debugging.
  * Release versions are compiled to be fast and well tested suitable for final production.
- What are the tradeoffs between debug and release versions?
  * Release versions are faster, optimized and tested code suitable for production.
  * Debug versions contain debugging information and is not very optimized and is suitable for debugging.
- What arguments would you use in a debug build?
  * -g, -Wall, -Wextra
- What about for release?
  * -O2/-O3
- What other kinds of build types are useful?
  * RelWithDebInfo - Release with Debug Info. Optimized for speed, but includes debug info.
  * MinSizeRel - Minimizes the size of the executables. Compromises on performance. Suitable for embedded systems.

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
  * Practicing
- How can you tell if the resource you are using is correct?
  * By reflecting if you are actually learning important stuff you didn't know about.
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
    * Make maintains the timestamps of the modification of the prerequisite file and trarget file. If the timestamp of the update of the prerequisite file is later than the target file, the commands are executed.
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
  * -s, -k, -n, -f, -d
- What are the most important directives to learn about in Makefile?
  * include, if, ifdef, ifndef, else, endif
- What are the most important commands to implement in your Makefile?
  * clean
- Which ones are essential, which ones are nice to haves?

## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
- What are the most important commands to know in git?
  * commit, push, pull, merge, rebase, add

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
- How do you find out which part of the below code comes from which header?
  * By commenting out the header and checking which line throws an error.
- How do you change the code so that you are sending messages to servers
  other than localhost?
    * Replace kServerAddress in the client code with the IP address of the server you wish to send to. Change the port to 35000 in both client and server. 
- How do you change the code to send to a IPv6 address instead of IPv4?
  * Make a few changes to both client and server code to use IPv6. Localhost is ::1
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
  * converts IP address from text to binary and stores in address.sin_addr
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
  * Connects to the server given by address
- What is the difference between a pointer and a reference?
  * A pointer stores the memory address of a variable whereas a reference acts as an alias to a variable. A pointer can be reassigned to a different address whereas a reference can act as an alias to only one variable.
- When is it better to use a pointer?
  * If we need the pointer to refer to multiple addresses through the run of the program and aslo need it to have NULL value. And pointers can be incremented to access adjacent memory addresses.
- When is it better to use a reference?
  * When "reseatiung"(assigning to another variable) is not needed. Can be accessed without dereferencing.
- What is the difference between `std::string` and a C-style string?
  * std::string is dynamically allocated in memory and the size can be changed freely. C-style string has fixed maximunm size that is allocated when the string is declared.
- What type is a C-style string?
  * A char array.
- What happens when you iterate a pointer?
  * It gets incremented by the size of the variable it references and updates the memory address.
- What are the most important safety tips to know when using pointers?
  * Always free pointer when you don't need to access it anymore.


## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?
  * g++ -o compile file.cpp
  * ./compile

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
  * man
- What is the most authoritative source of information about the TCP and IP
  protocols?
- What is the most authoritative source of information about the C++
  programming language?
  * man pages
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
  * https://www.markdownguide.org/getting-started/
- What is the difference between LLM and AI?
  * LLM is a Langauge Model like chatgpt. AI includes any artificial intelligence including LLMs, Face Recognition, Image Generation, Translation, etc.
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?
  * an LLM. Pronounced "el el em" and pronunciation starts with a vowel.