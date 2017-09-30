#ifndef JOBMANAGER_H
#define JOBMANAGER_H
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include "constants.h"
#include "job.h"
#include "tasksTable.h"

typedef boost::unordered_map<std::string, boost::shared_ptr<Job> > jobMap;

class JobManager{
	private:
		static jobMap jobs_;
	public:
	    JobManager();
	    ~JobManager();
	    static TasksTable * GetTasksTable(std::string jobName);
	    static tasksRow Receive(
			bool & taskFound, 
			std::string submitted_instance
		);
	    static void PrintAll();
};

#endif