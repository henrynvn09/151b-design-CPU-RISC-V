#!/bin/bash

hex_file="rv32ui-p-${1}.hex"

# Remove temporary files before running
rm -f tmp.log

# Clean and compile
make clean &&
  DEBUG=2 make &&

# Run the test
./tinyrv -s "tests/$hex_file" > tmp.log

# Check for errors
if [ $? -ne 0 ]; then
  echo "Error: Test failed."
  exit 1
fi

# Display differences
diff tmp.log "debug_traces-1/${hex_file}.log"

