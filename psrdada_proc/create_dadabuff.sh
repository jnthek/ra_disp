#! /bin/bash

# -a hdrsz    size of each header buffer (in bytes) [default: 4096]
# -b bufsz    size of each buffer (in bytes) [default: 524288]
# -d          destroy the shared memory area [default: create]
# -h          show help
# -k key      hexadecimal shared memory key  [default: dada]
# -l          lock the shared memory in RAM
# -n nbufs    number of buffers in ring      [default: 4]
# -p          page all blocks into RAM
# -r nread    number of readers             [default: 1]
# -w          persistance mode, wait for signal before destroying db

dada_db -b 524288 -k da123 -n 4 -l -p
