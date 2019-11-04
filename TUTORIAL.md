<p align="center"><img width="40%" src="https://github.com/61131/echidna/blob/master/media/logo.jpg?raw=true" /></p>

## Overview

Echidna is a compiler and virtual machine run-time for IEC 61131-3 languages for programmable controllers. This project can be used to create programmable logic controllers for interface with industrial automation, Internet-of-Things (IoT) and I/O control applications. 

This tutorial is intended to provide an overview of a basic project to blink an LED on example hardware. The example hardware used for this tutorial is a Raspberry Pi 1 Model B with PiFace Digital I/O board.

## Installation

By default, the echidna compiler and virtual machine run-time does not include support for any specific hardware platform. Support for the Raspberry Pi PiFace Digital I/O board can be included through the definition of `HARDWARE_PIFACE` environment variable when building the echidna binary. 
 ```
     $ git clone https://github.com/61131/echidna.git
     $ cd echidna
     $ HARDWARE_PIFACE=1 make
 ```

## Code

The following example IEC 61131-3 language application will blink the first LED on the Raspberry Pi PiFace Digital I/O board.

### Example 1
```
    program tutorial
    var output: byte := false; end_var

    ld output
    xor 1
    st output
    piface_write output

    end_program

    configuration config1
    task task1 (interval := t#500ms, priority := 1);
    program program1 with task1: tutorial;
    end_configuration
```
This code can be written in a text editor and then executed in the echidna virtual machine run-time from the command line on the Raspberry Pi. This example code can also be found in the examples/tutorial sub-directory of the project source tree.
```
    $ echidna ./example1.il
    notice: Running echidna version b01970e-dirty (20191102)
    notice: Function signature: f3a1edd..f269662
    info: Starting config: config1
    info: Starting task: task1
```
This blinking of the LED is based upon the toggling of the first bit of the byte written to the board hardware on every cycle of task execution. 

One limitation of this example however is that it ties the update of I/O state to the cycle time of interval task. This may be an issue if there are other actions which should be performed on each cycle of execution. This could be addressed by either introducing a second task to perform these other actions or updating the example code to offer a more robust solution.

The following example IEC 61131-3 language application uses a pair of `TON` function blocks to toggle the LED on the Raspberry Pi PiFace Digital I/O board independent of the task interval time.

### Example 2
```
    program tutorial
    var cycle: time := t#500ms; end_var
    var q: bool; end_var
    var output: byte := false; end_var
    var t1, t2: ton; end_var

    ldn t2.q
    st q
    cal t1(
        in := q,
        pt := cycle
    )
    cal t2(
        in := t1.q,
        pt := cycle
    )
    bool_to_byte t1.q
    st output
    piface_write output

    end_program

    configuration config1
    task task1 (interval := t#50ms, priority := 1);
    program program1 with task1: tutorial;
    end_configuration
```
This example code allows task execution to be performed every 50 milliseconds while the LED on the Raspberry Pi PiFace Digital I/O board is only updated every 500 milliseconds. 

This application is equivalent to the following ladder diagram code:

<p align="center"><img width="40%" src="https://github.com/61131/echidna/blob/master/media/tutorial2.png?raw=true" /></p>

In this ladder diagram code, the output of both `TON` timer function blocks are initially off and their elapsed time output is 0 ms. The output of the second `TON` timer function block is negated and supplied to first `TON` function block, causing this (first) function block to begin increasing the elapsed time. After 500 ms, the output of the first `TON` timer function block will be asserted causing the second `TON` function block to begin increasing its elapsed time. Again, after 500 ms the output of the second `TON` timer function block will be asserted, causing the input to the first `TON` function block to be deasserted, resetting this function block. This in turn will deassert the input to the second `TON` function block, similarly causing this function block to be reset and output to be deasserted. This establishes a periodic cycle of assertion and deassertion that can be used to blink the LED on the Raspberry Pi PiFace Digital I/O board.

The timing of this arrangement of `TON` timer function blocks can be represented as follows:

<p align="center"><img width="40%" src="https://github.com/61131/echidna/blob/master/media/tutorial3.png?raw=true" /></p>

## Links

-   [Contact and Coil - Flasher](http://www.contactandcoil.com/patterns-of-ladder-logic-programming/flasher/)
