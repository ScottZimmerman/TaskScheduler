#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <fstream>
#include <iostream>
#include "event.h"
#include "tasksTable.h"
#include "listener.h"

class Scheduler : public Listener{
	private:
		TasksTable * pTasksTable_;
		static bool finished;
	public:
	    Scheduler(TasksTable * pTasksTable);
	    ~Scheduler();
	    
	    static bool Finished();

	    //Listening
 		void HandleEvent(boost::shared_ptr<Event> event, boost::shared_ptr<Event> & response, bool & anyResponse);
 		boost::shared_ptr<schedulerMessages::Msg> Parse(boost::shared_ptr<schedulerMessages::Msg> msg);

 		//Scheduler functions
 		tasksRow AssignNewID(int & rowStartByte);
		void Queue(
			int id, 
			std::string input_bundle_name,
			int job_launched_from
		);
		tasksRow Receive(bool & taskFound, std::string submitted_instance);
		bool Requeue(int id);
		void Finish(int id);
		void Cancel(int id);
    	void AddDependency(int childID, int parentID);

		void AssignNewID_Multiple(int num_to_assign, std::vector<int> & result);

    	void Log(boost::shared_ptr<Server_Request_Event>);
    	static void Run(Scheduler & scheduler);
    	static void HandleCmdLineInput(Scheduler & scheduler);
};

#endif