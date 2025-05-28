# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise
  to another?
  * diff <file1> <file2>
    
## Using Classes

- Here is one way to separate out the code into multiple files
- Is this the best way to do it? 
  * Depends on the use case. If we would need multiple instances of the attributes, this is better.
  * If we need private functions, this works better.
- What are the advantages and disadvantages?
  * Multiple instances of the class can be created.
  * Can have private functions.

## Introduction to Namespace

- There are different ways namespace is being used in this exercise
- Which way is better? What are the advantages and disadvantages?
  * namespace works better in this case.
  * It provides a logical grouping of the functions and that is the only requirement here.
  * It does not allow any private functions like classes.

## Abstracting Code into Classes

- Abstract the client and server logic into a `Client` and `Server` class
- **Note**: You don't have to use the code in this exercise as a starting point
- You can use the code you wrote from previous exercises instead
- How should you divide the code into files?
  * Divide the Server class and Client into different files
  * Further the declaration of the class and its methods are seperated from the definition of the methods.
- What namespace and directory structure should you use? Why?

## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory
  structure? 
- How do you judge what makes a good naming convention or programming style?

## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code
  smell?
- What does it mean to have a sense of taste in programming? How can code
  taste?
- Is there an analogue for every sense?
- What other code senses can you think of?
- How many senses do humans have?
- When would you want to see something before you touch it?
- When would you want to touch something before you see it?