CC = g++
CFLAGS=-lstdc++ -std=c++17
TFLAGS=-g -c -Wall -Werror -Wextra -g -lstdc++ -std=c++17 -lgtest -Wuninitialized -pedantic
GTEST=-lgtest -lgtest_main -pthread
ASAN=-fsanitize=address
COVER=-fprofile-arcs -ftest-coverage
COVFLAGS = -fprofile-arcs -ftest-coverage
TARGET=./tests/mazeTest
VGFLAGS=--trace-children=yes --track-fds=all  --leak-check=full --show-leak-kinds=all --track-origins=yes
VAR = $(shell pkg-config --cflags --libs check)

.PHONY: all clean full_clean install uninstall run test install uninstall dist dvi leakscheck stylecheck

all: install run

gcov_report: tests
	geninfo --ignore-errors mismatch . -b . -o ./coverage.info --no-external 
	genhtml coverage.info -o ./coverage
	open coverage/index.html
	@rm -rf *.gcda
	@rm -rf *.gcno

leaks: tests
	leaks -atExit -- ./mazeTest
#	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.cc *.h model/*.cc model/*.h ../view/*.cc ../view/*.h 

install:
	cd ./view && cmake . && $(MAKE) all

run:
	./view/Maze_new.app/Contents/MacOS/Maze_new	

tests: clean
	@ g++ $(CFLAGS) $(COVER) ./tests/mazeTest.cc -o mazeTest $(GTEST)
	./mazeTest

dist:
	tar czf ../dist.tar *

generatedvi:
	curl -L -o $(CURDIR)/docs/doxygen 'https://drive.google.com/uc?export=download&id=1arycp6Hm-ORDZnD5xodBwSoyUyNSao6p'
	cd docs && chmod 777 doxygen
	cd docs && ./doxygen Doxyfile 

dvi: generatedvi
	open docs/html/index.html

stylecheck:
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -style=Google -i tests/*.cc model/*.cc model/*.h view/*.cc view/*.h
	clang-format -style=Google -n tests/*.cc model/*.cc model/*.h view/*.cc view/*.h
	rm -rf .clang-format

clean:
	@rm -rf *.out
	@rm -rf *.dSYM
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.info
	@rm -rf *.a
	@rm -rf *.log
	@rm -rf *.user
	@rm -rf CPPLINT.cfg
	@rm -rf cpplint.py
	@rm -rf report.*
	@rm -rf *.css
	@rm -rf index.html
	@rm -rf *.gcov
	@rm -rf *.gch
	@rm -rf ./view/Maze_new_autogen/
	@rm -rf ./view/CMakeCache.txt
	@rm -rf ./view/Makefile
	@rm -rf ./view/CMakeFiles/
	@rm -rf ./view/Maze_new.app/
	@rm -rf ./view/*.user
	@rm -rf ./view/*.cmake
	@rm -rf ./report
	@rm -rf .clang-format
	@rm -rf build/
	@rm -rf lcov_report
	@rm -rf ./docs/html/
	@rm -rf ./docs/doxygen
	@rm -rf coverage/
	@rm -rf ../dist.tar
	@rm -rf *.o
	@rm -rf mazeTest
	@rm -rf saved_maze.txt
	@rm -rf saved_maze1.txt
	@rm -rf build*



