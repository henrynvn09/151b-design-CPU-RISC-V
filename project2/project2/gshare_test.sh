#!/bin/bash

hex_file="${1}"

# Clean and compile
make clean &&
  DEBUG=3 make &&

# Run the test
echo "======================== $hex_file =======================" >> tmp1.log
./tinyrv -sg "benchmarks/$hex_file" | tail -n 10 >> tmp1.log
