#ifndef TASKS_TABLE_H
#define TASKS_TABLE_H

#include <time.h>
#include <fstream>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "dependenciesTable.h"
#include "constants.h"
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include "fileInterface.h"
#include "fileManager.h"

const unsigned int MAX_NUMBER_ATTEMPTS = 5;
const int TASKS_ROW_NULL = -1;

struct tasksRow {
	int id;
	time_t entered_queue;
	time_t exited_queue;
	char input_bundle_name[INPUT_BUNDLE_NAME_SIZE];
	char last_received_instance[INSTANCE_NAME_SIZE];
	int task_launched_from;
	time_t finished_time;
	time_t cancelled;
	int nAttempts;
};
inline std::ostream& operator<<(std::ostream& stream,const tasksRow&tr){
	std::cout << "{" << std::endl;
	std::cout << "\tid: " << tr.id << ","<< std::endl;
	std::cout << "\tentered_queue: " << tr.entered_queue << ","<< std::endl;
	std::cout << "\texited_queue: " << tr.exited_queue << ","<< std::endl;
	std::cout << "\tinput_bundle_name: '" << tr.input_bundle_name << "',"<< std::endl;
	std::cout << "\tlast_received_instance: '" << tr.last_received_instance << "',"<< std::endl;
	std::cout << "\ttask_launched_from: " << tr.task_launched_from << ","<< std::endl;
	std::cout << "\tfinished_time: " << tr.finished_time << ","<< std::endl;
	std::cout << "\tcancelled: " << tr.cancelled << ","<< std::endl;
	std::cout << "\tnAttempts: " << tr.nAttempts << ","<< std::endl;
	std::cout << "}" << std::endl;
}

struct tasksMetadata {
	int maxID;
};

class TasksTable{
	private:
		boost::shared_ptr<FileInterface> dataFile_;
		boost::shared_ptr<FileInterface> metadataFile_;

		std::fstream * file_;
		std::fstream * metadata_file_;
		tasksMetadata metadata_;
		DependenciesTable * pDependencies_;

	public:
		TasksTable();
		TasksTable(
			boost::filesystem::path jobPath, 
			DependenciesTable * pDependencies
		);
		~TasksTable();

		tasksRow GetRow(int id);
		tasksRow GetRow(int id, int & rowStartByte);
		tasksRow GetRow(int id, bool & success);
		tasksRow GetRow(int id, bool & success, int & rowStartByte);
		
		void SetRowToDefault_Disk(int id);
		void SetRowToDefault(tasksRow & row);
		tasksRow AssignNewID(int & rowStartByte);
		void ModifyRow(tasksRow row, int rowStartByte);
		void PrintAll();

		void Queue(
			int id, 
			std::string input_bundle_name,
			int job_launched_from
		);
		
		tasksRow Receive(bool & taskFound, std::string instance);
		bool Requeue(int id);
		void Finish(int id); 
		void Cancel(int id); 
		void CancelDescendants(int id);
		bool ParentsFinished(int id);
		std::vector<int> GetChildren(int id);
		void GetDescendants(int id, std::vector<int> & result);
		void GetTasksInJob(int id, std::vector<int> & result);
		void AddDependency(int childID, int parentID);
		int GetRoot(int id);
		
};
#endif