# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/user/Qt/Qt/Tools/CMake/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Users/user/Qt/Qt/Tools/CMake/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin

# Include any dependencies generated for this target.
include CMakeFiles/consolelibrary.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/consolelibrary.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/consolelibrary.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/consolelibrary.dir/flags.make

CMakeFiles/consolelibrary.dir/controller.cpp.o: CMakeFiles/consolelibrary.dir/flags.make
CMakeFiles/consolelibrary.dir/controller.cpp.o: /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/controller.cpp
CMakeFiles/consolelibrary.dir/controller.cpp.o: CMakeFiles/consolelibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/consolelibrary.dir/controller.cpp.o"
	/usr/bin/llvm-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/consolelibrary.dir/controller.cpp.o -MF CMakeFiles/consolelibrary.dir/controller.cpp.o.d -o CMakeFiles/consolelibrary.dir/controller.cpp.o -c /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/controller.cpp

CMakeFiles/consolelibrary.dir/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/consolelibrary.dir/controller.cpp.i"
	/usr/bin/llvm-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/controller.cpp > CMakeFiles/consolelibrary.dir/controller.cpp.i

CMakeFiles/consolelibrary.dir/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/consolelibrary.dir/controller.cpp.s"
	/usr/bin/llvm-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/controller.cpp -o CMakeFiles/consolelibrary.dir/controller.cpp.s

CMakeFiles/consolelibrary.dir/model.cpp.o: CMakeFiles/consolelibrary.dir/flags.make
CMakeFiles/consolelibrary.dir/model.cpp.o: /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/model.cpp
CMakeFiles/consolelibrary.dir/model.cpp.o: CMakeFiles/consolelibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/consolelibrary.dir/model.cpp.o"
	/usr/bin/llvm-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/consolelibrary.dir/model.cpp.o -MF CMakeFiles/consolelibrary.dir/model.cpp.o.d -o CMakeFiles/consolelibrary.dir/model.cpp.o -c /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/model.cpp

CMakeFiles/consolelibrary.dir/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/consolelibrary.dir/model.cpp.i"
	/usr/bin/llvm-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/model.cpp > CMakeFiles/consolelibrary.dir/model.cpp.i

CMakeFiles/consolelibrary.dir/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/consolelibrary.dir/model.cpp.s"
	/usr/bin/llvm-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/model.cpp -o CMakeFiles/consolelibrary.dir/model.cpp.s

# Object files for target consolelibrary
consolelibrary_OBJECTS = \
"CMakeFiles/consolelibrary.dir/controller.cpp.o" \
"CMakeFiles/consolelibrary.dir/model.cpp.o"

# External object files for target consolelibrary
consolelibrary_EXTERNAL_OBJECTS =

libconsolelibrary.dylib: CMakeFiles/consolelibrary.dir/controller.cpp.o
libconsolelibrary.dylib: CMakeFiles/consolelibrary.dir/model.cpp.o
libconsolelibrary.dylib: CMakeFiles/consolelibrary.dir/build.make
libconsolelibrary.dylib: CMakeFiles/consolelibrary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libconsolelibrary.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/consolelibrary.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/consolelibrary.dir/build: libconsolelibrary.dylib
.PHONY : CMakeFiles/consolelibrary.dir/build

CMakeFiles/consolelibrary.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/consolelibrary.dir/cmake_clean.cmake
.PHONY : CMakeFiles/consolelibrary.dir/clean

CMakeFiles/consolelibrary.dir/depend:
	cd /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin /Users/user/Desktop/dev29.11/CPP3_BrickGame_v2.0-1/src/brick_game/snake/bin/CMakeFiles/consolelibrary.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/consolelibrary.dir/depend

