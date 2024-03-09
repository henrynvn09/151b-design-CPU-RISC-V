#!/bin/bash

hex_file="rv32ui-p-${1}.hex"

# Remove temporary files before running
rm -f tmp.log

# Clean and compile
make clean &&
  DEBUG=3 make &&

# Run the test
./tinyrv -so "tests/$hex_file" > tmp.log
