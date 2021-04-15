#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9 10
do
    # cat /dev/random | head -c <bytecount>
    cat /dev/random | head -c 100000 > step4In$i.dat
done
