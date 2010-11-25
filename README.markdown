# JFCPP

This project  which does  not have  a significant name  for the  moment contains
various utilities coded in C++.

This library use template and meta-programming a lot and consists only of header
files.


## Directory structure

The main directories are:

- examples: various examples which show how to use the library;
- include: the headers themselves;
- tests: the unit tests.


## Requirements

JFCPP uses the  “contracts.h” header which provides several  macros for contract
programing and unit testing for C/C++.

This files can be found there: http://github.com/julien-f/contracts/

By default  it will  be searched in  the standard include  directories (commonly
“/usr/include”  and “/usr/local/include”),  if it  is somewhere  else,  you must
configure the compilation options in  the Makefiles by adding the following line
at the begining of the “example/Makefile” “tests/Makefile” files:

    CXXFLAGS += -I /path/to/look/for/contracts.h/
