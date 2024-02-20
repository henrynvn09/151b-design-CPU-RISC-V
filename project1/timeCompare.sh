#!/bin/bash

hex_file="rv32ui-p-${1}.hex"

# Remove temporary files before running
rm -f tmp.log

# Clean and compile
make clean &&
  DEBUG=3 make &&

# Run the test
./tinyrv -s "tests/$hex_file" > tmp.log 2> err

echo $err

# Check for errors
if [ $? -ne 0 ]; then
  echo "Error: Test failed."
  exit 1
fi

# Display differences
vimdiff tmp.log "debug_traces/${hex_file}.log"

