#!/bin/bash

SCHEDFLAG=UNDEFINED

if [ "$#" -eq 1 ]
then
    if [ "$1" -eq 1 ]
    then
        SCHEDFLAG=DEFAULT
    elif [ "$1" -eq 2 ]
    then
        SCHEDFLAG=FCFS
    elif [ "$1" -eq 3 ] 
    then
        SCHEDFLAG=PRIORITY
    else 
        SCHEDFLAG=UNDEFINED
    fi
else
    SCHEDFLAG=UNDEFINED
fi

if [ $SCHEDFLAG == "UNDEFINED" ]
then
    echo "Usage: ./generate.sh [1 or 2 or 3 ]"
    echo "1 - default RR scheduler"
    echo "2 - fcfs scheduler"
    echo "3 - priority-based scheduler"
else
    make clean
    make SCHEDPOLICY=$SCHEDFLAG
    make SCHEDPOLICY=$SCHEDFLAG qemu-nox
fi
