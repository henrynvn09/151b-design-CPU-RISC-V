#!/bin/bash

hex_file="rv32ui-p-${1}.hex"


make clean &&
  DEBUG=2 make &&
    ./tinyrv -s "tests/$hex_file" > tmp.log

vimdiff tmp.log "debug_traces-1/${hex_file}.log"
