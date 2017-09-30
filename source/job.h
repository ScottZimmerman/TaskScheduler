#ifndef JOB_H
#define JOB_H
#include <fstream>
#include <iostream>
#include <string.h>
#include <boost/filesystem.hpp>
#include "constants.h"
#include "tasksTable.h"
#include "dependenciesTable.h"

class Job{
	private:
		TasksTable tasks_;
		DependenciesTable dependencies_;
	public:
		Job();
	    Job(std::string name);
	    ~Job();
	    TasksTable * GetTasksTable();
};

#endif