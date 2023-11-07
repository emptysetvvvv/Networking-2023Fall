# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/emptyset/NetworkLab/RDT/SelectiveRepeat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emptyset/NetworkLab/RDT/SelectiveRepeat/build

# Include any dependencies generated for this target.
include CMakeFiles/selective_repeat.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/selective_repeat.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/selective_repeat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/selective_repeat.dir/flags.make

CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o: CMakeFiles/selective_repeat.dir/flags.make
CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o: ../src/SelectiveRep.cpp
CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o: CMakeFiles/selective_repeat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emptyset/NetworkLab/RDT/SelectiveRepeat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o -MF CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o.d -o CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o -c /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRep.cpp

CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRep.cpp > CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.i

CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRep.cpp -o CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.s

CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o: CMakeFiles/selective_repeat.dir/flags.make
CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o: ../src/SelectiveRepRdtReceiver.cpp
CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o: CMakeFiles/selective_repeat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emptyset/NetworkLab/RDT/SelectiveRepeat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o -MF CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o.d -o CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o -c /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRepRdtReceiver.cpp

CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRepRdtReceiver.cpp > CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.i

CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRepRdtReceiver.cpp -o CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.s

CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o: CMakeFiles/selective_repeat.dir/flags.make
CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o: ../src/SelectiveRepRdtSender.cpp
CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o: CMakeFiles/selective_repeat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emptyset/NetworkLab/RDT/SelectiveRepeat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o -MF CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o.d -o CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o -c /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRepRdtSender.cpp

CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRepRdtSender.cpp > CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.i

CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/emptyset/NetworkLab/RDT/SelectiveRepeat/src/SelectiveRepRdtSender.cpp -o CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.s

# Object files for target selective_repeat
selective_repeat_OBJECTS = \
"CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o" \
"CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o" \
"CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o"

# External object files for target selective_repeat
selective_repeat_EXTERNAL_OBJECTS =

../bin/selective_repeat: CMakeFiles/selective_repeat.dir/src/SelectiveRep.cpp.o
../bin/selective_repeat: CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtReceiver.cpp.o
../bin/selective_repeat: CMakeFiles/selective_repeat.dir/src/SelectiveRepRdtSender.cpp.o
../bin/selective_repeat: CMakeFiles/selective_repeat.dir/build.make
../bin/selective_repeat: ../lib/libnetsim.a
../bin/selective_repeat: CMakeFiles/selective_repeat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/emptyset/NetworkLab/RDT/SelectiveRepeat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/selective_repeat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/selective_repeat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/selective_repeat.dir/build: ../bin/selective_repeat
.PHONY : CMakeFiles/selective_repeat.dir/build

CMakeFiles/selective_repeat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/selective_repeat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/selective_repeat.dir/clean

CMakeFiles/selective_repeat.dir/depend:
	cd /home/emptyset/NetworkLab/RDT/SelectiveRepeat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emptyset/NetworkLab/RDT/SelectiveRepeat /home/emptyset/NetworkLab/RDT/SelectiveRepeat /home/emptyset/NetworkLab/RDT/SelectiveRepeat/build /home/emptyset/NetworkLab/RDT/SelectiveRepeat/build /home/emptyset/NetworkLab/RDT/SelectiveRepeat/build/CMakeFiles/selective_repeat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/selective_repeat.dir/depend

