# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mats/CLionProjects/sokoban

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mats/CLionProjects/sokoban/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sokoban.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sokoban.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sokoban.dir/flags.make

CMakeFiles/sokoban.dir/main.cpp.o: CMakeFiles/sokoban.dir/flags.make
CMakeFiles/sokoban.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mats/CLionProjects/sokoban/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sokoban.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sokoban.dir/main.cpp.o -c /Users/mats/CLionProjects/sokoban/main.cpp

CMakeFiles/sokoban.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sokoban.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mats/CLionProjects/sokoban/main.cpp > CMakeFiles/sokoban.dir/main.cpp.i

CMakeFiles/sokoban.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sokoban.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mats/CLionProjects/sokoban/main.cpp -o CMakeFiles/sokoban.dir/main.cpp.s

CMakeFiles/sokoban.dir/LevelLoader.cpp.o: CMakeFiles/sokoban.dir/flags.make
CMakeFiles/sokoban.dir/LevelLoader.cpp.o: ../LevelLoader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mats/CLionProjects/sokoban/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sokoban.dir/LevelLoader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sokoban.dir/LevelLoader.cpp.o -c /Users/mats/CLionProjects/sokoban/LevelLoader.cpp

CMakeFiles/sokoban.dir/LevelLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sokoban.dir/LevelLoader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mats/CLionProjects/sokoban/LevelLoader.cpp > CMakeFiles/sokoban.dir/LevelLoader.cpp.i

CMakeFiles/sokoban.dir/LevelLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sokoban.dir/LevelLoader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mats/CLionProjects/sokoban/LevelLoader.cpp -o CMakeFiles/sokoban.dir/LevelLoader.cpp.s

# Object files for target sokoban
sokoban_OBJECTS = \
"CMakeFiles/sokoban.dir/main.cpp.o" \
"CMakeFiles/sokoban.dir/LevelLoader.cpp.o"

# External object files for target sokoban
sokoban_EXTERNAL_OBJECTS =

sokoban: CMakeFiles/sokoban.dir/main.cpp.o
sokoban: CMakeFiles/sokoban.dir/LevelLoader.cpp.o
sokoban: CMakeFiles/sokoban.dir/build.make
sokoban: /opt/homebrew/lib/libsfml-system.dylib
sokoban: /opt/homebrew/lib/libsfml-window.dylib
sokoban: /opt/homebrew/lib/libsfml-graphics.dylib
sokoban: /opt/homebrew/lib/libsfml-network.dylib
sokoban: /opt/homebrew/lib/libsfml-audio.dylib
sokoban: CMakeFiles/sokoban.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mats/CLionProjects/sokoban/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sokoban"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sokoban.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sokoban.dir/build: sokoban

.PHONY : CMakeFiles/sokoban.dir/build

CMakeFiles/sokoban.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sokoban.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sokoban.dir/clean

CMakeFiles/sokoban.dir/depend:
	cd /Users/mats/CLionProjects/sokoban/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mats/CLionProjects/sokoban /Users/mats/CLionProjects/sokoban /Users/mats/CLionProjects/sokoban/cmake-build-debug /Users/mats/CLionProjects/sokoban/cmake-build-debug /Users/mats/CLionProjects/sokoban/cmake-build-debug/CMakeFiles/sokoban.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sokoban.dir/depend

