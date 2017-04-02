#include <fstream>
#include "listener.h"
#include "scheduler.h"
#include "event.h"
#include "eventQueue.h"
#include "connectionManager.h"

int main(int argc, char * argv[]){
  if (argc != 3) {
        fprintf(stderr,"usage: %s minPort numPorts\n",argv[0]);
        exit(1);
  }

  //------------------------
  //Server setup
  //------------------------
  ConnectionManager connectionManager;
  connectionManager.Setup(atoi(argv[1]),atoi(argv[2]));

  connectionManager.CreateThreads();

  //------------------------
  //Scheduler setup
  //------------------------
  //Dependencies Table
  DependenciesTable dependencies;
  DependenciesTable * pDependencies = &dependencies;
  
  //Tasks Table
  TasksTable tasks(pDependencies);
  TasksTable * pTasks = &tasks;

  //Register scheduler's callbacks
  Scheduler scheduler(pTasks);
  NonStatMemCB scheduler_cbdata;
  scheduler_cbdata.fn = Listener::Add_Wrapper;
  scheduler_cbdata.listener = &scheduler;

  EventQueue::Register(Event::SERVER_REQUEST, scheduler_cbdata);

  //Run
  connectionManager.threads_.create_thread(boost::bind(Scheduler::Run, boost::ref(scheduler)));
  connectionManager.threads_.create_thread(boost::bind(Scheduler::HandleCmdLineInput, boost::ref(scheduler)));
  while(!Scheduler::Finished()){
    
  };

  //Cleanup
  connectionManager.CloseAll();
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}