<p align="center"><img width="40%" src="https://github.com/61131/echidna/blob/master/media/logo.jpg?raw=true"></p>

[![Codacy Badge](https://img.shields.io/codacy/grade/32bc0e41e0234262b81b82043babd41e)](https://www.codacy.com/manual/rcasey/echidna) ![Build Status](https://img.shields.io/circleci/build/github/61131/echidna/master) ![Coverage](https://img.shields.io/codecov/c/github/61131/echidna)

## Overview

Echidna is a compiler and virtual-machine run-time for IEC 61131-3 languages for programmable controllers. This compiler supports only a single language at this time, Instruction List (IL), but includes full support for all standard functions and function blocks and elements of the IEC 61131-3 configuration model.

## Dependencies

-   GNU bison - General purpose parser-generator (build dependency only)
-   GNU flex - Fast lexical analyser generator (build dependency only)
-   libev - High-performance event loop modelled after libevent
-   protobuf-c - Protocol Buffers implementation in C
-   gcovr - Generate code coverage reports with gcc/gcov (code coverage only)
