# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build"

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/source/client_main.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/source/client_main.cpp.o: ../source/client_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/client.dir/source/client_main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/client.dir/source/client_main.cpp.o -c "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/client_main.cpp"

CMakeFiles/client.dir/source/client_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/source/client_main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/client_main.cpp" > CMakeFiles/client.dir/source/client_main.cpp.i

CMakeFiles/client.dir/source/client_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/source/client_main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/client_main.cpp" -o CMakeFiles/client.dir/source/client_main.cpp.s

CMakeFiles/client.dir/source/client_main.cpp.o.requires:
.PHONY : CMakeFiles/client.dir/source/client_main.cpp.o.requires

CMakeFiles/client.dir/source/client_main.cpp.o.provides: CMakeFiles/client.dir/source/client_main.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/source/client_main.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/source/client_main.cpp.o.provides

CMakeFiles/client.dir/source/client_main.cpp.o.provides.build: CMakeFiles/client.dir/source/client_main.cpp.o

CMakeFiles/client.dir/source/client_output_generator.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/source/client_output_generator.cpp.o: ../source/client_output_generator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/client.dir/source/client_output_generator.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/client.dir/source/client_output_generator.cpp.o -c "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/client_output_generator.cpp"

CMakeFiles/client.dir/source/client_output_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/source/client_output_generator.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/client_output_generator.cpp" > CMakeFiles/client.dir/source/client_output_generator.cpp.i

CMakeFiles/client.dir/source/client_output_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/source/client_output_generator.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/client_output_generator.cpp" -o CMakeFiles/client.dir/source/client_output_generator.cpp.s

CMakeFiles/client.dir/source/client_output_generator.cpp.o.requires:
.PHONY : CMakeFiles/client.dir/source/client_output_generator.cpp.o.requires

CMakeFiles/client.dir/source/client_output_generator.cpp.o.provides: CMakeFiles/client.dir/source/client_output_generator.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/source/client_output_generator.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/source/client_output_generator.cpp.o.provides

CMakeFiles/client.dir/source/client_output_generator.cpp.o.provides.build: CMakeFiles/client.dir/source/client_output_generator.cpp.o

CMakeFiles/client.dir/source/command_line_parser.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/source/command_line_parser.cpp.o: ../source/command_line_parser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build/CMakeFiles" $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/client.dir/source/command_line_parser.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/client.dir/source/command_line_parser.cpp.o -c "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/command_line_parser.cpp"

CMakeFiles/client.dir/source/command_line_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/source/command_line_parser.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/command_line_parser.cpp" > CMakeFiles/client.dir/source/command_line_parser.cpp.i

CMakeFiles/client.dir/source/command_line_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/source/command_line_parser.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/command_line_parser.cpp" -o CMakeFiles/client.dir/source/command_line_parser.cpp.s

CMakeFiles/client.dir/source/command_line_parser.cpp.o.requires:
.PHONY : CMakeFiles/client.dir/source/command_line_parser.cpp.o.requires

CMakeFiles/client.dir/source/command_line_parser.cpp.o.provides: CMakeFiles/client.dir/source/command_line_parser.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/source/command_line_parser.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/source/command_line_parser.cpp.o.provides

CMakeFiles/client.dir/source/command_line_parser.cpp.o.provides.build: CMakeFiles/client.dir/source/command_line_parser.cpp.o

CMakeFiles/client.dir/source/msg.pb.cc.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/source/msg.pb.cc.o: ../source/msg.pb.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build/CMakeFiles" $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/client.dir/source/msg.pb.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/client.dir/source/msg.pb.cc.o -c "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/msg.pb.cc"

CMakeFiles/client.dir/source/msg.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/source/msg.pb.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/msg.pb.cc" > CMakeFiles/client.dir/source/msg.pb.cc.i

CMakeFiles/client.dir/source/msg.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/source/msg.pb.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/source/msg.pb.cc" -o CMakeFiles/client.dir/source/msg.pb.cc.s

CMakeFiles/client.dir/source/msg.pb.cc.o.requires:
.PHONY : CMakeFiles/client.dir/source/msg.pb.cc.o.requires

CMakeFiles/client.dir/source/msg.pb.cc.o.provides: CMakeFiles/client.dir/source/msg.pb.cc.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/source/msg.pb.cc.o.provides.build
.PHONY : CMakeFiles/client.dir/source/msg.pb.cc.o.provides

CMakeFiles/client.dir/source/msg.pb.cc.o.provides.build: CMakeFiles/client.dir/source/msg.pb.cc.o

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/source/client_main.cpp.o" \
"CMakeFiles/client.dir/source/client_output_generator.cpp.o" \
"CMakeFiles/client.dir/source/command_line_parser.cpp.o" \
"CMakeFiles/client.dir/source/msg.pb.cc.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/source/client_main.cpp.o
client: CMakeFiles/client.dir/source/client_output_generator.cpp.o
client: CMakeFiles/client.dir/source/command_line_parser.cpp.o
client: CMakeFiles/client.dir/source/msg.pb.cc.o
client: CMakeFiles/client.dir/build.make
client: /usr/local/lib/libprotobuf.so
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/requires: CMakeFiles/client.dir/source/client_main.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/source/client_output_generator.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/source/command_line_parser.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/source/msg.pb.cc.o.requires
.PHONY : CMakeFiles/client.dir/requires

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling" "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling" "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build" "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build" "/home/a/Desktop/Release Scheduler/51_Input_Parsing_and_Scheduling/build/CMakeFiles/client.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend
