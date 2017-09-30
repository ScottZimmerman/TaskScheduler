#include "job.h"
Job::Job(){};
Job::Job(std::string name):
	dependencies_(boost::filesystem::path(DATA_FOLDER) / name),
	tasks_(boost::filesystem::path(DATA_FOLDER) / name, &dependencies_)
{
	printf("%s\n",name.c_str());
	
};

Job::~Job(){};
TasksTable * Job::GetTasksTable(){
	return(&tasks_);
};