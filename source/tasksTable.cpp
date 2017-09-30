#include "tasksTable.h"
using namespace std;
TasksTable::TasksTable(){};
TasksTable::TasksTable(
	boost::filesystem::path jobPath, 
	DependenciesTable * pDependencies
)
{
	dataFile_ = FileManager::Get(jobPath / "tasks.bin");
	metadataFile_ = FileManager::Get(jobPath / "tasksMetadata.bin");

	file_ = dataFile_->Get();
	metadata_file_ = metadataFile_->Get();

	//Load metadata
	metadata_file_->seekg(0, ios::end);
	size_t metadataFileSize = metadata_file_->tellg();

    if(metadataFileSize == 0){
    	tasksMetadata metadata;
    	metadata.maxID = 0;
	    metadata_file_->seekg(0, ios::beg);
    	metadata_file_->write((char*)&metadata, (int)sizeof(tasksMetadata));
    	metadata_file_->seekg(0, ios::beg);
    }

    metadata_file_->seekg(0, ios::beg);
    metadata_file_->read((char*)&metadata_, (int)sizeof(tasksMetadata));

  	pDependencies_ = pDependencies;
 };

TasksTable::~TasksTable(){
    if(file_->is_open()){
    	file_->close();
	}
	if(metadata_file_->is_open()){
		metadata_file_->seekg(0, ios::beg);
    	metadata_file_->write((char*)&metadata_, (int)sizeof(tasksMetadata));
    	metadata_file_->close();
	}
};

tasksRow TasksTable::GetRow(int id){
	int temp;
	bool success;
	return(GetRow(id, success, temp));
};


tasksRow TasksTable::GetRow(int id, bool & success){
	int temp;
	return(GetRow(id,success, temp));
};

tasksRow TasksTable::GetRow(int id, int & rowStartByte){
	bool success;
	return(GetRow(id,success, rowStartByte));
};

tasksRow TasksTable::GetRow(int id, bool & success,  int & rowStartByte){
	tasksRow currentRow;
	if(file_->is_open()){
		file_->seekg(0, ios::end);
		size_t fileSize = file_->tellg();
		int rowSize = (int)sizeof(tasksRow);
		int nRows = fileSize/rowSize;

		//BinSearch through table's binary file 
		int L = 0;
		int R = nRows - 1;
		int M = floor(((double)L+(double)R)/2.0);
		bool searchFinished = 0;
		success = 0;
		while(searchFinished == 0){
			
			if(L>R){
				searchFinished = 1;
			}else{
				M = floor(((double)L+(double)R)/2.0);
				rowStartByte = rowSize*M; 
				file_->seekg(rowStartByte, ios::beg);
				file_->read((char*)&currentRow, rowSize);
				
				if(currentRow.id < id){
					L = M+1;
				}else if(currentRow.id > id){
					R = M-1;
				}else{
					searchFinished = 1;
					success = 1;
				}
			}
		}

		if(success == 1){
			//

		}else{
			printf("TasksTable::GetRow could not find entry with id = %d\n",id);
		}
	}
	return(currentRow);
};

void TasksTable::PrintAll(){
	printf("=======================REPORT=START====================\n");
	pDependencies_->PrintAll();
	printf("TasksTable::PrintAll\n");
	if(file_->is_open()){
		file_->seekg(0, ios::end);
		size_t fileSize = file_->tellg();
		int rowSize = (int)sizeof(tasksRow);
		int nRows = fileSize/rowSize;

		printf("File size is %d bytes\n", (int)fileSize);
		printf("Row size is %d bytes\n", (int)rowSize);
		printf("%d rows \n", nRows);
		
		if(nRows > 0){
			tasksRow currentRow;
			file_->seekg(0, ios::beg);
			for(int rowIndex = 0; rowIndex < nRows; rowIndex++){
				file_->read((char*)&currentRow, rowSize);
				printf("%d: ",rowIndex);
				std::cout << currentRow << std::endl;
			}
		}
	}	
	printf("=======================REPORT=END======================\n");
};

void TasksTable::SetRowToDefault_Disk(int id){
	int rowStartByte;
	tasksRow row = GetRow(id,rowStartByte);
	SetRowToDefault(row);
	ModifyRow(row,rowStartByte);
}

void TasksTable::SetRowToDefault(tasksRow & row){
	row.entered_queue = TASKS_ROW_NULL;
	row.exited_queue = TASKS_ROW_NULL;
	memset(row.input_bundle_name,0,INPUT_BUNDLE_NAME_SIZE);
	memset(row.last_received_instance,0,INSTANCE_NAME_SIZE);
	row.task_launched_from = TASKS_ROW_NULL;
	row.finished_time = TASKS_ROW_NULL;
	row.cancelled = TASKS_ROW_NULL;
	row.nAttempts = 0;
};

tasksRow TasksTable::AssignNewID(int & rowStartByte){
	tasksRow newRow;

	metadata_.maxID += 1;
	newRow.id = metadata_.maxID;

	//Set default values
	SetRowToDefault(newRow);
	
	if(file_->is_open()){
		file_->seekg(0, ios::end);
		size_t fileSize = file_->tellg();
		rowStartByte = (int)fileSize;
		file_->write((char*)&newRow,(int)sizeof(tasksRow));
	}
	if(metadata_file_->is_open()){
		metadata_file_->seekg(0, ios::beg);
    	metadata_file_->write((char*)&metadata_, (int)sizeof(tasksMetadata));
		metadata_file_->seekg(0, ios::beg);
	}
	
	return(newRow);
};

void TasksTable::ModifyRow(tasksRow row, int rowStartByte){
	//printf("Modifying TasksTable Row (rowStartByte = %d)\n",rowStartByte);
	//std::cout << row << endl;
	if(file_->is_open()){
		file_->seekg(rowStartByte, ios::beg);
		file_->write((char*)&row,(int)sizeof(tasksRow));
	}
};

void TasksTable::Queue(
	int id, 
	std::string input_bundle_name,
	int task_launched_from
){
	int rowStartByte;
	bool getRowSuccessful;
	tasksRow row = GetRow(id, getRowSuccessful, rowStartByte);

	if(getRowSuccessful){
		time(&row.entered_queue);
		std::copy(input_bundle_name.begin(),input_bundle_name.end(),row.input_bundle_name);

		row.task_launched_from = task_launched_from;

		ModifyRow(row,rowStartByte);
	}else{
		printf("Could not get row\n");
	}
};

tasksRow TasksTable::Receive(
	bool & taskFound, 
	std::string instance
){
	tasksRow result;
	taskFound = 0;
	
	bool thisTaskReady;
	bool thisTaskParentsFinished;

	if(file_->is_open()){
		file_->seekg(0, ios::end);
		size_t fileSize = file_->tellg();
		int rowSize = (int)sizeof(tasksRow);
		int nRows = fileSize/rowSize;

		if(nRows > 0){
			tasksRow currentRow;
			file_->seekg(0, ios::beg);
			for(int rowIndex = 0; rowIndex < nRows; rowIndex++){
				if(taskFound == 0){
					file_->seekg(rowSize*rowIndex,ios::beg);
					file_->read((char*)&currentRow, rowSize);
					thisTaskReady = (currentRow.entered_queue != TASKS_ROW_NULL);
					thisTaskReady *= (currentRow.exited_queue == TASKS_ROW_NULL);
					thisTaskReady *= (currentRow.finished_time == TASKS_ROW_NULL);
					thisTaskReady *= (currentRow.cancelled == TASKS_ROW_NULL);
					if(thisTaskReady){
						result = currentRow;
						
						thisTaskParentsFinished = ParentsFinished(currentRow.id);
						
						if(thisTaskParentsFinished){
							taskFound = 1;
							time(&result.exited_queue);
							int rowStartByte;
							GetRow(result.id, rowStartByte);
							std::copy(
								instance.begin(),
								instance.end(),
								result.last_received_instance
							);
							
							ModifyRow(result, rowStartByte);
						}
					}
				}
			}
		}
	}
	return(result);
};

bool TasksTable::ParentsFinished(
	int id
){
	std::vector<int> parents = pDependencies_->GetParents(id);	
	std::vector<int>::iterator iter = parents.begin();
	
	tasksRow parentRow;

	bool parentsFinished = 1;
	bool thisParentFinished;
	while(iter != parents.end()){
		parentRow = GetRow(*iter);

		thisParentFinished = (parentRow.finished_time != TASKS_ROW_NULL);
		thisParentFinished *= (parentRow.cancelled == TASKS_ROW_NULL);

		if(!thisParentFinished){
			parentsFinished = 0;
			break;
		}
		iter++;
	}
	return(parentsFinished);
};

bool TasksTable::Requeue(
	int id
){
	int rowStartByte;
	tasksRow row = GetRow(id, rowStartByte);
	bool result = 0;
	if((row.nAttempts+1) < MAX_NUMBER_ATTEMPTS){
		row.exited_queue = -1;
		row.nAttempts += 1;
		
		ModifyRow(row,rowStartByte);
	}else{
		Cancel(id);
		CancelDescendants(id);
		result = 1;
	}
	return(result);
};

void TasksTable::Finish(
	int id	
){
	int rowStartByte;
	tasksRow row = GetRow(id, rowStartByte);
	time(&row.finished_time);
	ModifyRow(row,rowStartByte);
};

void TasksTable::Cancel(
	int id
){
	int rowStartByte;
	tasksRow row = GetRow(id, rowStartByte);
	time(&row.cancelled);
	ModifyRow(row,rowStartByte);
};

void TasksTable::CancelDescendants(
	int id
){
	std::vector<int> processedDescendants;
	GetDescendants(id, processedDescendants);
	std::vector<int>::iterator pIter = processedDescendants.begin();
	while(pIter != processedDescendants.end()){
		Cancel((*pIter));
		pIter++;
	}
};


std::vector<int> TasksTable::GetChildren(int id){
	return(pDependencies_->GetChildren(id));
};

int TasksTable::GetRoot(int id){
	tasksRow queue_parent = GetRow(id);
	if(queue_parent.task_launched_from != -1){
		while(queue_parent.task_launched_from != -1){
			queue_parent = GetRow(queue_parent.task_launched_from);
		}
	}
	int rootID = queue_parent.id;
	return(rootID);
}


void TasksTable::GetDescendants(int id, std::vector<int> & processedDescendants){
	std::vector<int> descendants;
	std::vector<int> newDescendants = pDependencies_->GetChildren(id);
	std::vector<int> children;
	std::vector<int>::iterator dIter;
	std::vector<int>::iterator cIter;

	bool anyNewDescendants = 1;
	bool inDescendants;
	bool inProcessedDescendants;

	while(newDescendants.size() > 0){
		descendants = newDescendants;
		newDescendants.clear();

		dIter = descendants.begin();
		while(dIter != descendants.end()){
			children = pDependencies_->GetChildren(*dIter);
			
			cIter = children.begin();
			while(cIter != children.end()){
				//Check if already processed
				inDescendants = (std::find(descendants.begin(), descendants.end(), *cIter) == descendants.end());
				inProcessedDescendants = (std::find(processedDescendants.begin(), processedDescendants.end(), *cIter) == processedDescendants.end());

				if ((!inDescendants)*(!inProcessedDescendants)){
					//We've found a new descendant
					newDescendants.push_back(*cIter);
				}

				cIter++;	
			}
			processedDescendants.push_back(*dIter);
			dIter++;
		}
	}
}

void TasksTable::AddDependency(int childID, int parentID){
	pDependencies_->AddDependency(childID, parentID);
};