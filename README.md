# Repository Overview

This repository contains multiple projects related to system-level programming and computer architecture. Below is an overview of each project:

| Project Name         | Description                                                                 | Tech Stack       |
|----------------------|-----------------------------------------------------------------------------|------------------|
| project1             | Implements a RISC-V 5-stage pipelined processor simulator.                  | C++              |
| project2             | Implements an out-of-order RISC-V processor emulator with gshare predictor.  | C++              |

## Project 1: Pipelined RISC-V CPU Simulator

In this project, you will design a RISC-V 5-stage pipelined processor using C++. The ISA of this processor is the standard RV32-I base extension. The provided source code contains an incomplete implementation of the CPU. The processor implementation consists of two parts:
- The CPU emulator: decode and execute instructions to generate instruction trace.
- The CPU simulator: Use the instruction trace to perform cycle-level simulation.

You are responsible for completing the code of the emulator and simulator such that you can successfully execute the provided tests on the processor.

## Project 2: Out-of-order RISC-V CPU Simulator
In this project, you will design an out-of-order RISC-V processor using C++. The ISA of this processor is the standard RV32-I base extension. The provided source code contains an incomplete implementation of the CPU. The processor implementation consists of two parts:

- The CPU emulator: decode and execute instructions to generate instruction trace.
- The CPU simulator: Use the instruction trace to perform cycle-level simulation.
You are responsible for completing the code of the out-of-order pipeline and gshare branch predictor such that you can successfully execute the provided tests with the correct timing.

### Project Parts
- Out-of-order Pipeline: Complete the implementation of the processor's scoreboard and re-order buffer. Refer to TODO entries inside scoreboard.cpp and ROB.cpp for where you should make your changes.
- Gshare Predictor: Complete the implementation of the processor's branch predictor. It will consist of a GShare predictor containing an 8-bit BHR and 256-entry BHT, matched with a 256-entry BTB. Assume all counters, including the BHR, to be initialized to zero at boot. You should complete the implementation of the GShare class by implementing the predict() method. Note that we are only interested in timing. Your predict() method should first determine the current predicted outcome, and then update the predictor. Also note that a successful prediction is a combination of branch direction and branch target hits.
