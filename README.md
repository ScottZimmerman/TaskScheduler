# TaskScheduler
Coordinate parallel computation of jobs broken up into  tasks that have complex dependency structures that may change during the job.

Compilation:
From empty "build" folder, run: 

cmake ..
make

Running examples:
1) Before running an example, run clean.sh, which will remove the input/output and binary (table) files. 
2) From "build" directory, start the server listening on ports 51717-51719 with:
./server 51717 3
3) Run the "run.sh" script from the example's subdirectory