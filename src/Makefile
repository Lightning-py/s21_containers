.PHONY: test

CC=g++ -std=c++17

SOURCES=./array/* ./linked_list/* ./map/* ./queue/* ./set/* ./shared/* ./stack/* ./vector/*

TESTS=./test/test.cpp

FILES= $(SOURCES) ./test/*

CFLAGS= -o test -Wall -Wextra
LDFLAGS=-lpthread -lgtest --coverage -ld_classic
VALGRIND_FLAGS=--leak-check=full


test: $(FILES)
	mkdir -p build
	$(CC) $(TESTS) -o ./build/test_ $(LDFLAGS)
	./build/test_

gcov_report: test
	lcov --ignore-errors mismatch --capture --directory ./build --output-file ./build/coverage.info --exclude '/usr/*' --exclude '*/test/*'
	mkdir -p ./build/report/
	genhtml ./build/coverage.info --output-directory ./build/report/

memcheck: test
	valgrind $(VALGRIND_FLAGS) -- ./build/test_

format:
	clang-format -i $(FILES)

clang-check:
	clang-format -n $(FILES)

clean:
	rm -rf build/*