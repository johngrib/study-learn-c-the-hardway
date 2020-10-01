#!/usr/bin/env bash

cc -Wall -g -DNDEBUG -c -o ex22.o ex22.c

cc -Wall -g -DNDEBUG ex22_main.c ex22.o -o ex22_main

./ex22_main
