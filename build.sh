#!/bin/sh

set -xe

clang -Wall -Wextra -o code core.c
clang -Wall -Wextra -o gates gates.c
