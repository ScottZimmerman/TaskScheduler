# CMake entry point
cmake_minimum_required (VERSION 2.8)

project (Task_Scheduler)

#Boost libraries
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost REQUIRED COMPONENTS system thread timer chrono)
find_package(Threads)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

#Google protocol buffers libraries
find_package(Protobuf REQUIRED)

set(ALL_LIBS
	${PROTOBUF_LIBRARIES}
)

SET(PROTOBUF_LIST 
	msg
)

foreach(PROTOFILE ${PROTOBUF_LIST})
	execute_process(COMMAND protoc -I=../proto --cpp_out=../source ../proto/${PROTOFILE}.proto)
endforeach()

#server
add_executable(
	server source/server_main.cpp
	source/event.h
	source/eventQueue.h
	source/eventQueue.cpp
	source/listener.h
	source/listener.cpp
	source/scheduler.h
	source/scheduler.cpp
	source/dependenciesTable.h
	source/dependenciesTable.cpp
	source/tasksTable.h
	source/tasksTable.cpp
	source/msg.pb.h
	source/msg.pb.cc
	source/constants.h
	source/connection.h
	source/connection.cpp
	source/connectionManager.h
	source/connectionManager.cpp
)
target_link_libraries(server
	${ALL_LIBS}
	${Boost_SYSTEM_LIBRARY}
	${Boost_THREAD_LIBRARY}
	${Boost_TIMER_LIBRARY}
	${Boost_CHRONO_LIBRARY}
	${CMAKE_THREAD_LIBS_INIT}
	pthread
	rt
)

#client
add_executable(
	client source/client_main.cpp
	source/client_output_generator.h
	source/client_output_generator.cpp
	source/command_line_parser.h
	source/command_line_parser.cpp
	source/msg.pb.h
	source/msg.pb.cc
	source/constants.h
)
target_link_libraries(client
	${ALL_LIBS}
)