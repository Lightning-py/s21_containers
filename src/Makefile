CC=g++

VECTOR_SOURCES=./vector/vector.h
LIST_SOURCES=./linked_list/linked_list.h

SOURCES=./vector/ ./linked_list/ ./s21_queue/ ./s21_stack/ ./test/ ./shared/

TESTS=./test/test.cpp

CFLAGS= -o test -Wall -Wextra
LDFLAGS=-lpthread -lgtest --coverage
VALGRIND_FLAGS=--leak-check=full


test: $(SOURCES)
	mkdir -p build
	$(CC) $(TESTS) -o ./build/test_ $(LDFLAGS)
	./build/test_

gcov_report: test
	lcov --ignore-errors mismatch --capture --directory ./build --output-file ./build/coverage.info --exclude '/usr/*' --exclude '*/test/*'
	mkdir -p ./build/report/
	genhtml ./build/coverage.info --output-directory ./build/report/

memcheck: test
	valgrind $(VALGRIND_FLAGS) -- ./build/test_