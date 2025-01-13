CC = g++
CC_C = gcc
TEST_LIBS = -lcheck -lm
FLAGS = -Wall -Wextra -Werror -std=c++17
FLAGS_C = -Wall -Wextra -Werror -std=c11
P = -pedantic -lm
DB = -g -O0
LNC = -lncurses
SOURCES = $(wildcard brick_game/snake/*.cpp)
OBJECTS = $(patsubst brick_game/snake/ %.cpp, brick_game/snake/%.o, $(SOURCES))
SOURCES_T = $(wildcard brick_game/tetris/*.c)
OBJECTS_T = $(patsubst brick_game/tetris/%.c, brick_game/tetris/%.o, $(SOURCES_T))
OS := $(shell uname)
TESTFLAGS=-lgtest
LCOVFLAGS= --ignore-errors inconsistent --ignore-errors mismatch

ifeq ($(OS), Linux)
	TEST_LIBS = -lcheck -pthread -lrt -lm -lsubunit
else
	TEST_LIBS = $(shell pkg-config --libs --cflags check) -lm
endif


all:  uninstall snake.a snake_cmake_desktop


uninstall: clean
	rm -rf doxy
	rm -rf build

snake_cmake_desktop: 
	mkdir build
	cp gui/desktop/apple.png build
	if [ -f "max_score_snake.txt" ]; then cp max_score_snake.txt build/; fi
	cd build && cmake ../ && make snake_desktop && ./snake_desktop.app/Contents/MacOS/snake_desktop
	cp build/max_score_snake.txt ./
	rm build/max_score_snake.txt 
	

tetris_desk: uninstall
	mkdir build
	if [ -f "max_score.txt" ]; then cp max_score.txt build/; fi
	cd build && cmake ../ && make tetris_desktop && ./tetris_desktop.app/Contents/MacOS/tetris_desktop
	cp build/max_score.txt ./
	rm build/max_score.txt 
	

tetris_cons: uninstall
	mkdir build
	$(CC_C) $(FLAGS_C) $(P) $(DB) brick_game/tetris/*.c  gui/console/main_tetris.c  gui/console/frontend.c -o tetris $(LNC)
	cp tetris build
	cd build
	./tetris

snake_cons: uninstall 
	mkdir build
	$(CC) $(FLAGS) -c brick_game/snake/*.cpp
	$(CC_C) $(FLAGS_C) -c gui/console/frontend.c 
	$(CC) $(FLAGS) -c gui/console/main_snake.cpp
	$(CC) $(FLAGS) -o snake ./*.o $(LNC)
	cp snake build
	rm -rf *.o
	cd build
	./snake

tests: uninstall 
	$(CC) $(FLAGS) brick_game/snake/model.cpp tests/test_snake.cpp -lgtest -o test 
	./test
	

clean:
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.info report *.dSYM .clang-format *.o test snake tetris dist.tar.gz

snake.a: $(OBJECTS)
	/usr/bin/ar rcs snake.a $(OBJECTS)
	ranlib snake.a

tetris.a: $(OBJECTS_T)
	/usr/bin/ar rcs tetris.a $(OBJECTS_T)
	ranlib tetris.a


gcov_flag:
	$(eval FLAGS += --coverage)

gcov_report: gcov_flag tests
	lcov -t "test_snake" -o check.info -c -d ./  --no-external $(LCOVFLAGS)
	genhtml -o report check.info $(LCOVFLAGS)
	open report/index.html

dist: all
	@rm -rf dist.tar.gz
	@tar -cvzf dist.tar.gz build/snake_desktop.app/Contents/MacOS/snake_desktop

dvi:
	doxygen
	open doxy/html/index.html

fix_style:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i brick_game/tetris/* brick_game/snake/*.h brick_game/snake/*.cpp \
	gui/console/*.cpp gui/console/*.h gui/console/*.c \
	gui/desktop/*.cpp gui/desktop/*.h gui/desktop/tetris/*.cpp gui/desktop/tetris/*.h \
	tests/*.cpp brick_game/*.h
style:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n brick_game/tetris/*  brick_game/snake/*.h brick_game/snake/*.cpp \
	gui/console/*.cpp gui/console/*.h gui/console/*.c \
	gui/desktop/*.cpp gui/desktop/*.h gui/desktop/tetris/*.cpp gui/desktop/tetris/*.h \
	tests/*.cpp brick_game/*.h
