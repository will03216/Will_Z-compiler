
The features we implemented is shown in table below:

| Features                                                                               |   Radaan  |    Will      |
|----------------------------------------------------------------------------------------|:---------:|:------------:|
| **Basic Features**                                                                     |                          |
| A file containing just a single function with no arguments                             |          |              |
| Variables of int type                                                                  |          |              |
| Local variables                                                                        |           |             |
| Arithmetic and logical expressions                                                     |          |              |
| If-then-else statements                                                                |          |              |
| While loops                                                                            |          |              |
| **Intermediate Features**                                                              |                          |
| Files containing multiple functions that call each other                               |           |             |
| Functions that take up to 8 parameters                                                 |           |             |
| For loops                                                                              |          |              |
| Arrays declared globally (i.e. outside of any function in your file)                   |           |             |
| Arrays declared locally (i.e. inside a function)                                       |           |             |
| Array initialization                                                                   |           |             |
| Reading and writing elements of an array                                               |           |             |
| Recursive function calls                                                               |           |             |
| The enum keyword                                                                       |          |             |
| Switch statements                                                                      |          |              |
| The break and continue keywords                                                        |           |             |
| Ternary operator (x ? y : z)                                                           |          |             |
| **Advanced Features**                                                                  |                          |
| Variables of double, float, char, unsigned, structs, and pointer types                 |          |              |
| Calling externally-defined functions                                                   |           |             |
| Functions that take more than 8 parameters                                             |           |             |
| Mutually recursive function calls                                                      |           |             |
| Locally scoped variable declarations                                                   |          |             |
| The typedef keyword                                                                    |          |             |
| The sizeof(...) function                                                               |          |              |
| Taking the address of a variable using the & operator                                  |           |             |
| Dereferencing a pointer-variable using the * operator                                  |           |             |
| Pointer arithmetic                                                                     |           |             |
| Character literals, including escape sequences like \n                                 |           |              |
| Strings (as NULL-terminated character arrays)                                          |           |             |
| Declaration and use of structs                                                         |          |             |


Mile Stone:

- **26/02** - [Built the repository.]
- **03/03** - [Completed the first version of context, parser, and lexer.]
- **04/03** - [Implemented binary operations for basic arithmetic.]
- **10/03** - [Implemented local variable support.]

Week-by-week View

- **first week(26/02-03/03)**
  1. Get basic understanding of the compiler project
  2. Review material on slide that relates to this project
  3. Try to finish work for other module(e.g. control report) in order to give time for compiler

2 hours each day

- **second week(04/03-10/03)**
  1. work together to finish the basic features
  2. modify the context
  3. start adding higher level features

  About 4 hours each day

- **third week(11/03-17/03)**
  1. work on medium and high level features
  2. debugging and testing with the .sh file

 whole day from home

- **fourth week(18/03-22/03)**
  1. continue to add features as much as we can
  2. improve the coding layout and add comments
  3. do the finial testing to avoid error like memory leakage
  4. check all the test case we done work well

About 6 hours each day

  Detailed Time Taken for Each Milestone

| Features                                                     |                   Time                    | Estimation | Note                      |
| ------------------------------------------------------------ | :---------------------------------------: | :--------: | ------------------------- |
| **Basic Features**                                           |                                           |         |                           |
| A file containing just a single function with no arguments   |                   6 hrs                   |           |                           |
| Variables of int type                                        |                   2 hrs                   |           |                           |
| Local variables                                              |                   10 hrs                  |           |                           |
| Arithmetic and logical expressions                           |                   4 hrs                   |           |                           |
| If-then-else statements                                      |                   1 hrs                   |           |                           |
| While loops                                                  |                   1 hrs                   |          |                           |
| **Intermediate Features**                                    |                                           |            |                           |
| Files containing multiple functions that call each other     |                   4 hrs                   |           |                           |
| Functions that take up to 8 parameters                       |                   2 hrs                   |           |                           |
| For loops                                                    |                   1 hrs                   |           |                           |
| Arrays declared globally (i.e. outside of any function in your file) |          10 hrs (Array in total)  |        |                               |
| Arrays declared locally (i.e. inside a function)             |          10 hrs (Array in total)          |           |                           |
| Array initialization                                         |          10 hrs (Array in total)          |           |                           |
| Reading and writing elements of an array                     |          10 hrs (Array in total)          |           |                           |
| Recursive function calls                                     |                   4 hrs                   |           |                           |
| The enum keyword                                             |                                          |           |                             |
| Switch statements                                            |        2 hrs (more time in debug)         |           |                           |
| The break and continue keywords                              |                   1 hrs                   |           |                           |
| Ternary operator (x ? y : z)                                 |                   3 hrs                   |           |                           |
| **Advanced Features**                                        |                                           |            |                           |
| Variables of double, float, char, unsigned, structs, and pointer types |                   6 hrs         |         |                             |
| Calling externally-defined functions                         |                   6 hrs                   |           |                           |
| Functions that take more than 8 parameters                   |                   3 hrs                   |           |                           |
| Mutually recursive function calls                            |                   2 hrs                   |           |                           |
| Locally scoped variable declarations                         |                   2 hrs                   |           |                           |
| The typedef keyword                                          |                                          |             |                           |
| The sizeof(...) function                                     |                                            |           |                           |
| Taking the address of a variable using the & operator        |                                           |           |                           |
| Dereferencing a pointer-variable using the * operator        |                                            |           |                           |
| Pointer arithmetic                                           |                                            |           |                           |
| Character literals, including escape sequences like \n       |                                            |           |                           |
| Strings (as NULL-terminated character arrays)                |                                             |           |                           |
| Declaration and use of structs                               |                                            |           |                            |
| **Lexer**                                                    |          Inherited from template          |            |                           |
| **Parser**                                                   | Completed after each feature is completed |            |                           |
