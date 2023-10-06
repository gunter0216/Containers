.PHONY: all clean test check
CC = g++
FLAGS = -std=c++17  #-Werror -Wall -Wextra 
TESTFLAGS = -lgtest -lstdc++ -pthread
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

default: all
 
all: clean test_list test_array test_map test_multiset test_queue test_set test_stack test_vector

test_list:
	$(CC) $(FLAGS) --coverage -o test_list tests/test_list.cpp headers/s21_list.h $(TESTFLAGS)
	./test_list
	rm -rf test_list

test_queue:
	$(CC) $(FLAGS) --coverage -o test_queue tests/test_queue.cpp headers/s21_queue.h $(TESTFLAGS)
	./test_queue
	rm -rf test_queue

test_stack:
	$(CC) $(FLAGS) --coverage -o test_stack tests/test_stack.cpp headers/s21_stack.h $(TESTFLAGS)
	./test_stack
	rm -rf test_stack

test_map:
	$(CC) $(FLAGS) --coverage -o test_map tests/test_map.cpp headers/s21_map.h $(TESTFLAGS)
	./test_map
	rm -rf test_map

test_set:
	$(CC) $(FLAGS) --coverage -o test_set tests/test_set.cpp headers/s21_set.h $(TESTFLAGS)
	./test_set
	rm -rf test_set

test_multiset:
	$(CC) $(FLAGS) --coverage -o test_multiset tests/test_multiset.cpp headers/s21_multiset.h $(TESTFLAGS)
	./test_multiset
	rm -rf test_multiset

test_array: 
	$(CC) $(FLAGS) --coverage -o test_array tests/array_test.cpp headers/s21_array.h $(TESTFLAGS)
	./test_array
	rm -rf test_array

test_vector: 
	$(CC) $(FLAGS) --coverage -o test_vector tests/vector_test.cpp headers/s21_vector.h $(TESTFLAGS)
	./test_vector
	rm -rf test_vector

cpplint:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=cpp *.cpp headers/*.h tests/*.cpp

cppcheck: 
	cppcheck --enable=all --language=c++ --suppress=missingIncludeSystem --suppress=unusedFunction *.cpp

check:
	$(CC) $(FLAGS) -o test tests/vector_test.cpp $(TESTFLAGS)
ifeq ($(OS), Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	valgrind -s --leak-check=full ./test
endif

clean:
	rm -rf test *.a *.o *.out *.gc* *.info report testresult CPPLINT.cfg test_list test_map test_multiset test_set test_queue
	rm -rf test_vector test_array test_stack
 
rebuild: clean all
