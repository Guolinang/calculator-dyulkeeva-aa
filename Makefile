GTEST_DIR ?= googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11
CC ?= gcc
VENV_DIR = myenv
PYTEST = $(VENV_DIR)/bin/pytest

$(shell mkdir -p build/gtest)

.PHONY: clean all run-integration-tests run-unit-test run-int run-float

clean:
	@echo "Cleaning..."
	@rm -rf build/*
	@rm -rf $(VENV_DIR)

all: build/app.exe build/app-test.o build/CalculateTest.exe  build/ListTest.exe build/ParseTest.exe build/PriorityTest.exe build/StackTest.exe

venv:
	@echo "Creating virtual environment..."
	@python -m venv $(VENV_DIR)
	@source $(VENV_DIR)/bin/activate; pip install -U pytest

build/app.exe: src/main.c
	@$(CC) $(CFLAGS) src/main.c -o build/app.exe

run-int: build/app.exe
	@build/app.exe

run-float: build/app.exe
	@build/app.exe --float

run-integration-tests: build/app.exe venv tests/integration/test_math.py
	@echo "Running integration tests..."
	@source $(VENV_DIR)/bin/activate; $(PYTEST) tests/integration/test_math.py

build/gtest/gtest-all.o: $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
	@g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

build/gtest/gtest_main.o: $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
	@g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc -o $@

build/gtest/gtest_main.a: build/gtest/gtest-all.o build/gtest/gtest_main.o
	@ar rv $@ $^ -o $@

build/app-test.o: src/main.c
	@gcc -DGTEST -c src/main.c -o build/app-test.o

build/StackTest.exe: build/gtest/gtest_main.a build/app-test.o tests/unit/StackTest.cpp
	@g++ -isystem $(GTEST_DIR)/include -pthread \
		tests/unit/StackTest.cpp \
		build/gtest/gtest_main.a build/app-test.o \
		-o build/StackTest.exe

build/ListTest.exe: build/gtest/gtest_main.a build/app-test.o tests/unit/ListTest.cpp
	@g++ -isystem $(GTEST_DIR)/include -pthread \
		tests/unit/ListTest.cpp \
		build/gtest/gtest_main.a build/app-test.o \
		-o build/ListTest.exe

build/PriorityTest.exe: build/gtest/gtest_main.a build/app-test.o tests/unit/PriorityTest.cpp
	@g++ -isystem $(GTEST_DIR)/include -pthread \
		tests/unit/PriorityTest.cpp \
		build/gtest/gtest_main.a build/app-test.o \
		-o build/PriorityTest.exe

build/CalculateTest.exe: build/gtest/gtest_main.a build/app-test.o tests/unit/CalculateTest.cpp
	@g++ -isystem $(GTEST_DIR)/include -pthread \
		tests/unit/CalculateTest.cpp \
		build/gtest/gtest_main.a build/app-test.o \
		-o build/CalculateTest.exe

build/ParseTest.exe: build/gtest/gtest_main.a build/app-test.o tests/unit/ParseTest.cpp
	@g++ -isystem $(GTEST_DIR)/include -pthread \
		tests/unit/ParseTest.cpp \
		build/gtest/gtest_main.a build/app-test.o \
		-o build/ParseTest.exe

run-unit-test: build/StackTest.exe build/ListTest.exe build/PriorityTest.exe build/CalculateTest.exe build/ParseTest.exe
	@echo "Running stack tests..."
	@./build/StackTest.exe
	@echo "Running list tests..."
	@./build/ListTest.exe
	@echo "Running priority tests..."
	@./build/PriorityTest.exe
	@echo "Running parse tests..."
	@./build/ParseTest.exe
	@echo "Running calculate tests..."
	@./build/CalculateTest.exe

