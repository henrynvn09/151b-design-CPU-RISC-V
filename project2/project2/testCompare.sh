#!/bin/bash

hex_file="rv32ui-p-${1}.hex"

# Remove temporary files before running
rm -f tmp.log

# Clean and compile
make clean &&
  DEBUG=3 make &&

# Run the test
./tinyrv -so "tests/$hex_file" > tmp.log

# Check for error
if [ $? -ne 0 ]; then
  echo "Error: Test failed."
  exit 1
fi

answer_file="ooo_trace/trace-o-rv32ui-p-${1}.hex.log"
# Display differences
diff tmp.log "${answer_file}"

