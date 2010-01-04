#!/bin/bash
# put everything together and execute C and octave code

make && ./test && octave < trsv.m
