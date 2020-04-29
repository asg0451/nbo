CC := clang++
CC_OPTS := -g -Wall -Werror -Wextra -Wpedantic -std=c++17

all: build/nbo

# debug core dump
# run in shell ulimit -c unlimited
# gdb build/nbo ./core
# bt
# up down
# info locals

clean:
	rm -rf build/*

build/%: src/*.cpp
	$(CC) $(CC_OPTS) $^ -o $@ -I./src

src/%.h: src/*.h
