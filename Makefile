CC := clang++
CC_OPTS := -g -Wall -Werror -Wextra -Wpedantic -std=c++17 -lpthread

all: build/nbo

# debug core dump
# run in shell ulimit -c unlimited
# gdb build/nbo ./core
# bt
# up down
# info locals

clean:
	rm -rf build/*

### nope
## requiring c++20, clang 10
# wget https://apt.llvm.org/llvm.sh
# chmod +x llvm.sh
# sudo ./llvm.sh 10

# $(CC) $(CC_OPTS) $^ -o $@ -I./src
build/nbo: src/*.cpp src/*.h
	$(CC) $(CC_OPTS) src/*.cpp -o $@ -I./src

# build/%.o: src/%.cpp src/*.h
# 	$(CC) $(CC_OPTS) src/$*.cpp -c -o $@ -I./src

# -c, -o
