# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build

# Include any dependencies generated for this target.
include CMakeFiles/cboe_core.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cboe_core.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cboe_core.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cboe_core.dir/flags.make

CMakeFiles/cboe_core.dir/src/Serializer.cpp.o: CMakeFiles/cboe_core.dir/flags.make
CMakeFiles/cboe_core.dir/src/Serializer.cpp.o: /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Serializer.cpp
CMakeFiles/cboe_core.dir/src/Serializer.cpp.o: CMakeFiles/cboe_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cboe_core.dir/src/Serializer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cboe_core.dir/src/Serializer.cpp.o -MF CMakeFiles/cboe_core.dir/src/Serializer.cpp.o.d -o CMakeFiles/cboe_core.dir/src/Serializer.cpp.o -c /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Serializer.cpp

CMakeFiles/cboe_core.dir/src/Serializer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cboe_core.dir/src/Serializer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Serializer.cpp > CMakeFiles/cboe_core.dir/src/Serializer.cpp.i

CMakeFiles/cboe_core.dir/src/Serializer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cboe_core.dir/src/Serializer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Serializer.cpp -o CMakeFiles/cboe_core.dir/src/Serializer.cpp.s

CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o: CMakeFiles/cboe_core.dir/flags.make
CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o: /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Deserializer.cpp
CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o: CMakeFiles/cboe_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o -MF CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o.d -o CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o -c /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Deserializer.cpp

CMakeFiles/cboe_core.dir/src/Deserializer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cboe_core.dir/src/Deserializer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Deserializer.cpp > CMakeFiles/cboe_core.dir/src/Deserializer.cpp.i

CMakeFiles/cboe_core.dir/src/Deserializer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cboe_core.dir/src/Deserializer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Deserializer.cpp -o CMakeFiles/cboe_core.dir/src/Deserializer.cpp.s

CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o: CMakeFiles/cboe_core.dir/flags.make
CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o: /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/FramingEngine.cpp
CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o: CMakeFiles/cboe_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o -MF CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o.d -o CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o -c /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/FramingEngine.cpp

CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/FramingEngine.cpp > CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.i

CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/FramingEngine.cpp -o CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.s

CMakeFiles/cboe_core.dir/src/Buffer.cpp.o: CMakeFiles/cboe_core.dir/flags.make
CMakeFiles/cboe_core.dir/src/Buffer.cpp.o: /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Buffer.cpp
CMakeFiles/cboe_core.dir/src/Buffer.cpp.o: CMakeFiles/cboe_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cboe_core.dir/src/Buffer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cboe_core.dir/src/Buffer.cpp.o -MF CMakeFiles/cboe_core.dir/src/Buffer.cpp.o.d -o CMakeFiles/cboe_core.dir/src/Buffer.cpp.o -c /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Buffer.cpp

CMakeFiles/cboe_core.dir/src/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cboe_core.dir/src/Buffer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Buffer.cpp > CMakeFiles/cboe_core.dir/src/Buffer.cpp.i

CMakeFiles/cboe_core.dir/src/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cboe_core.dir/src/Buffer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Buffer.cpp -o CMakeFiles/cboe_core.dir/src/Buffer.cpp.s

CMakeFiles/cboe_core.dir/src/Allocator.cpp.o: CMakeFiles/cboe_core.dir/flags.make
CMakeFiles/cboe_core.dir/src/Allocator.cpp.o: /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Allocator.cpp
CMakeFiles/cboe_core.dir/src/Allocator.cpp.o: CMakeFiles/cboe_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cboe_core.dir/src/Allocator.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cboe_core.dir/src/Allocator.cpp.o -MF CMakeFiles/cboe_core.dir/src/Allocator.cpp.o.d -o CMakeFiles/cboe_core.dir/src/Allocator.cpp.o -c /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Allocator.cpp

CMakeFiles/cboe_core.dir/src/Allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cboe_core.dir/src/Allocator.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Allocator.cpp > CMakeFiles/cboe_core.dir/src/Allocator.cpp.i

CMakeFiles/cboe_core.dir/src/Allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cboe_core.dir/src/Allocator.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/src/Allocator.cpp -o CMakeFiles/cboe_core.dir/src/Allocator.cpp.s

# Object files for target cboe_core
cboe_core_OBJECTS = \
"CMakeFiles/cboe_core.dir/src/Serializer.cpp.o" \
"CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o" \
"CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o" \
"CMakeFiles/cboe_core.dir/src/Buffer.cpp.o" \
"CMakeFiles/cboe_core.dir/src/Allocator.cpp.o"

# External object files for target cboe_core
cboe_core_EXTERNAL_OBJECTS =

libcboe_core.a: CMakeFiles/cboe_core.dir/src/Serializer.cpp.o
libcboe_core.a: CMakeFiles/cboe_core.dir/src/Deserializer.cpp.o
libcboe_core.a: CMakeFiles/cboe_core.dir/src/FramingEngine.cpp.o
libcboe_core.a: CMakeFiles/cboe_core.dir/src/Buffer.cpp.o
libcboe_core.a: CMakeFiles/cboe_core.dir/src/Allocator.cpp.o
libcboe_core.a: CMakeFiles/cboe_core.dir/build.make
libcboe_core.a: CMakeFiles/cboe_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libcboe_core.a"
	$(CMAKE_COMMAND) -P CMakeFiles/cboe_core.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cboe_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cboe_core.dir/build: libcboe_core.a
.PHONY : CMakeFiles/cboe_core.dir/build

CMakeFiles/cboe_core.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cboe_core.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cboe_core.dir/clean

CMakeFiles/cboe_core.dir/depend:
	cd /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/CMakeFiles/cboe_core.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cboe_core.dir/depend

