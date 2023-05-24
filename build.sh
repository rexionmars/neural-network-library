#!/bin/sh

set -xe

clang -Wall -Wextra -o core core.c -lm
clang -Wall -Wextra -o gate gates.c -lm
clang -Wall -Wextra -o xor xor.c -lm
