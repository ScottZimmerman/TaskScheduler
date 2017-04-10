# TaskScheduler
## Overview
This scheduler is intended for use to coordinate "jobs" that are broken up into "tasks", where the tasks have a complex dependency structure that may not be entirely known at the offset. Individual tasks may queue new tasks and assign their dependencies. Intended use involves multiple instances of a "compute engine" program (usually running one or more instances on a number of compute nodes in parallel), where each engine periodically uses the scheduler client to check for new tasks. When a task is ready to run, the scheduler will return the name of an input bundle. It is then the responsibility of the compute engine to look up the input bundle wherever it may be located (e.g. in a local file system, cloud-based object storage, or database). The input bundle should contain all information that the compute engine requires to conduct the task.

The server listens on a range of ports specified in the command line arguments when starting the server. Intended use at this time is to have one port reserved per compute engine. Each "connection" listens on its own thread. The scheduler also runs on its own thread.

The program uses Google Protocol Buffers to send messages between the client and server. When a message is received by the server, a "request" event containing the message is added to the server's event queue. When ready, the scheduler pulls from the event queue and processes the message. When the message is processed, a "response" event (with a response message attached) is added to the event queue. The response event is pulled by the connection that issued the original request, and the attached message is sent to the appropriate client.

The client is intended to be run from the command line as a subprocess of the compute engine. The client parses the command line arguments (See "command_line_parser.cpp") and generates a message to send to the server. When the response message is received, it generates text output that is written to stdout. The engine should read this output and parse the text. See "client_output_generator.cpp" for the output forms for each command type. 

Provided in "scripts" is an example of a compute engine, which periodically runs "receive" commands using the client. If a task is received, the engine will run the script as subprocesses. 

## Client Functions
Depending on the command line arguments, the client can submit one of the following commands to the server. Argument syntax is: \<required argument> (\<optional argument>).

-assign (\<count>):
	-Generate and return one or more task ID numbers, but do not queue the task

-queue \<task_id> \<input_bundle> \<task_queued_from>:
	-Indicates that the task can is ok to run as soon as its dependents are finished. and adds the name (or path) of the instructions bundle. Parsing of the instructions bundle name is the engine's responsibility.

-finish \<task_id>:
	-Indicates that the task completed successfully.

-cancel \<task_id>:
	-Cancel a task and all of its dependents.

-receive (\<submitted_instance_name>):
	-Return the next task that is ready to run (i.e. queued, not cancelled, not started/running, not finished, all dependencies finished). submitted_instance_name is an optional argument that allows for tracking which engine or node ran the task.

-add_dependency \<parent_id> \<child_id>:
	-Either use after assign but prior to queue, or dynamically add dependencies to already queued tasks (see P_A.py in the example).

## Compilation
From empty "build" folder, run: 

cmake ..
make

## Running examples
1) Before running an example, run clean.sh, which will remove the input/output and binary (table) files. 
2) From "build" directory, start the server listening on ports 51717-51719 with:
./server 51717 3
3) Run the "run.sh" script from the example's subdirectory

## Planned future additions
-Async_accept for sockets
-Logging thread
-Status query commands
-Requeue incomplete tasks upon server startup
-Remove_dependency function
-Job-specific binary files
-Scheduler process termination conditions
