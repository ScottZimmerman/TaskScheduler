#include "jobManager.h"
jobMap JobManager::jobs_;
JobManager::JobManager(){
	boost::filesystem::path dataDir = DATA_FOLDER;
	if (!boost::filesystem::exists(DATA_FOLDER)){
		boost::filesystem::create_directory(DATA_FOLDER);
	}

	boost::filesystem::directory_iterator end_iter;
	for( boost::filesystem::directory_iterator dir_iter(dataDir) ; dir_iter != end_iter ; ++dir_iter){
		std::string job_name = (boost::filesystem::path(*dir_iter)).filename().string();

		boost::shared_ptr<Job> job(new Job(job_name));

		jobs_[job_name] = job;
	}
};
JobManager::~JobManager(){};
TasksTable * JobManager::GetTasksTable(std::string jobName){
	
	if(jobs_.find(jobName) == jobs_.end()){
		//------------------------
		//Job folder setup
		//------------------------
		boost::filesystem::path jobPath = boost::filesystem::path(DATA_FOLDER) / jobName;
		if (!boost::filesystem::exists(jobPath)){
		  boost::filesystem::create_directory(jobPath);
		}

		boost::shared_ptr<Job> job(new Job(jobName));
		jobs_[jobName]  = job;
	}

	TasksTable * pTasksTable = jobs_[jobName]->GetTasksTable();
	return(pTasksTable);
}
tasksRow JobManager::Receive(
	bool & taskFound, 
	std::string submitted_instance
){
	//Loop through jobs
	tasksRow result;
	taskFound = 0;
	BOOST_FOREACH( jobMap::value_type& v, jobs_ ) {
	    TasksTable * pTasksTable = v.second->GetTasksTable();
	    tasksRow tr = pTasksTable->Receive(taskFound,submitted_instance);

	    if(taskFound){
	    	std::cout << "TASK FOUND" << std::endl;  
	    	result = tr;
	    	break;
	    }    
	};
	return(result);
}
void JobManager::PrintAll(){
	BOOST_FOREACH( jobMap::value_type& v, jobs_ ) {
	    printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	    printf("                               JOB:  %s\n", v.first.c_str());
		TasksTable * pTasksTable = v.second->GetTasksTable();
	    pTasksTable->PrintAll();
	};
	
}