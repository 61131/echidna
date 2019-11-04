<p align="center"><img width="40%" src="https://github.com/61131/echidna/blob/master/media/logo.jpg?raw=true" /></p>

[![Codacy Badge](https://img.shields.io/codacy/grade/32bc0e41e0234262b81b82043babd41e)](https://www.codacy.com/manual/rcasey/echidna) ![Build Status](https://img.shields.io/circleci/build/github/61131/echidna/master) ![Coverage](https://img.shields.io/codecov/c/github/61131/echidna) ![GitHub](https://img.shields.io/github/license/61131/echidna)

## Overview

Echidna is a compiler and virtual machine run-time for IEC 61131-3 languages for programmable controllers. This project can be used to create programmable logic controllers for interface with industrial automation, Internet-of-Things (IoT) and I/O control applications. 

## Features

-   Preemptive, high performance virtual machine run-time
-   IEC 61131-3 language compiler supporting Instruction List (IL)
-   Support for all IEC 61131-3 standard functions, function blocks and configuration elements
-   API support for custom function and function block extensions
-   Comprehensive test suite

## Demonstration

The following shows an echidna application running on a Raspberry Pi 1 Model B with PiFace Digital I/O board.

<p align="center"><a href="https://www.youtube.com/watch?v=a_vYcMlqOW0"><img width="50%" src="https://github.com/61131/echidna/blob/master/media/raspberrypi.gif?raw=true" /></a></p>

## Dependencies

-   [libev](https://github.com/enki/libev) - High-performance event loop modelled after libevent
-   [protobuf-c](https://github.com/protobuf-c/protobuf-c) - Protocol Buffers implementation in C
-   [GNU bison](https://www.gnu.org/software/bison/) - General purpose parser-generator (build dependency)
-   [GNU flex](https://github.com/westes/flex) - Fast lexical analyser generator (build dependency)
-   [µnit](https://github.com/nemequ/munit/) - C unit testing framework (test dependency)
-   [gcovr](https://github.com/gcovr/gcovr) - Generate code coverage reports with gcc/gcov (test coverage)

## Installation

The echidna compiler and virtual machine run-time can only be built from source. No pre-built binary packages have been issued or released for this project.
```
    $ git clone https://github.com/61131/echidna.git
    $ cd echidna
    $ make tests
    $ make
```
Following a successful build, the echidna binary can be found in the src sub-directory. This can be used to compile and execute any of the supplied IEC 61131-3 language applications that can be found in the examples sub-directory.

## Further Information

-   [IEC 61131-3:2013](https://webstore.iec.ch/publication/4552) Programmable controllers - Part 3: Programming languages (Edition 3.0)
-   [IEC 61131-3:2003](https://webstore.iec.ch/publication/19081) Programmable controllers - Part 3: Programming languages (Edition 2.0)


