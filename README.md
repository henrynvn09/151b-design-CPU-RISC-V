# Repository Overview

This repository contains multiple projects related to system-level programming and computer architecture. Below is an overview of each project:

| Project Name         | Description                                                                 | Tech Stack       |
|----------------------|-----------------------------------------------------------------------------|------------------|
| project1             | Contains various utilities and memory management tools, along with debug traces for RISC-V instruction set. | C++              |
| project2             | Implements a RISC-V processor emulator with various components like core, decode, execute, and more. | C++              |

## Project 1

### Description
Project 1 includes common utilities and memory management tools. It also contains debug traces for the RISC-V instruction set.

### Tech Stack
- C++

### Directory Structure
- `common/`: Contains utility and memory management headers and source files.
- `debug_traces/`: Contains log files for various RISC-V instructions.
- `debug_traces-1/`: Additional debug traces.
- `src/`: Source files for the project.
- `tests/`: Test scripts and files.
- `Makefile`: Build instructions for the project.

## Project 2

### Description
Project 2 focuses on implementing a RISC-V processor emulator. It includes various components such as the core, decode, execute, and more.

### Tech Stack
- C++

### Directory Structure
- 

project2

: Main directory for Project 2.
- `common/`: Shared utilities and memory management files.
- `src/`: Source files for the RISC-V processor emulator.
- `tests/`: Test scripts and files.
- `Makefile`: Build instructions for the project.

## How to Build

To build the projects, navigate to the respective project directory and run the following command:

```sh
make
```

## How to Run Tests

To run tests, navigate to the respective project directory and execute the test scripts:

```sh
./testCompare.sh
./timeCompare.sh
```

## Additional Information

For more details, refer to the individual 

README.md

 files located in each project directory.
