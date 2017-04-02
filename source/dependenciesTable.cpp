#include "dependenciesTable.h"
using namespace std;
DependenciesTable::DependenciesTable(){
	std::string dependenciesbin =  "dependencies.bin";
	std::string dependenciesMetadatabin =  "dependenciesMetadata.bin";
    file_.open(dependenciesbin.c_str(), fstream::in | fstream::out | fstream::binary);
    if(!file_.is_open()){
    	file_.open(dependenciesbin.c_str(), fstream::out | fstream::binary);
    	file_.close();
    	file_.open(dependenciesbin.c_str(), fstream::in | fstream::out | fstream::binary);
    }
	metadata_file_.open(dependenciesMetadatabin.c_str(), fstream::in | fstream::out | fstream::binary);

    if(!metadata_file_.is_open()){
    	metadata_file_.open(dependenciesMetadatabin.c_str(), fstream::out | fstream::binary);
    	metadata_file_.close();
    	metadata_file_.open(dependenciesMetadatabin.c_str(), fstream::in | fstream::out | fstream::binary);
    }

    //Load metadata
	metadata_file_.seekg(0, ios::end);
	size_t metadataFileSize = metadata_file_.tellg();

    if(metadataFileSize == 0){
    	dependenciesMetadata metadata;
    	metadata.maxID = 0;
	    metadata_file_.seekg(0, ios::beg);
    	metadata_file_.write((char*)&metadata, (int)sizeof(dependenciesMetadata));
	    metadata_file_.seekg(0, ios::beg);
    }

    metadata_file_.seekg(0, ios::beg);
    metadata_file_.read((char*)&metadata_, (int)sizeof(dependenciesMetadata));
};

DependenciesTable::~DependenciesTable(){
	printf("Closing deps\n");
    if(file_.is_open()){
    	printf("Closing file_\n");
    	file_.close();
	}
	if(metadata_file_.is_open()){
    	printf("Closing metadata_file_\n");
		metadata_file_.seekg(0, ios::beg);
    	metadata_file_.write((char*)&metadata_, (int)sizeof(dependenciesMetadata));
    	metadata_file_.close();
	}
};

dependenciesRow DependenciesTable::GetRow(int id){
	printf("DependenciesTable::GetRow\n");
	
	dependenciesRow currentRow;
	
	if(file_.is_open()){
		file_.seekg(0, ios::end);
		size_t fileSize = file_.tellg();
		int rowSize = (int)sizeof(dependenciesRow);
		int nRows = fileSize/rowSize;

		printf("File size is %d bytes\n", (int)fileSize);
		printf("Row size is %d bytes\n", (int)rowSize);
		printf("%d rows \n", nRows);
		
		
		//BinSearch through table's binary file 
		int L = 0;
		int R = nRows - 1;
		int M = floor(((double)L+(double)R)/2.0);
		bool searchFinished = 0;
		bool success = 0;
		while(searchFinished == 0){
			
			if(L>R){
				searchFinished = 1;
			}else{
				M = floor(((double)L+(double)R)/2.0);
				
				file_.seekg(rowSize*M, ios::beg);
				file_.read((char*)&currentRow, rowSize);
				
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
			printf("Found: {id:%d, id_child:%d, id_parent:%d}\n",
						currentRow.id,
						currentRow.id_child,
						currentRow.id_parent);

		}else{
			printf("DependenciesTable::GetRow could not find entry with id = %d\n",id);
		}
	}
	return(currentRow);
};

void DependenciesTable::PrintAll(){
	printf("DependenciesTable::PrintAll\n");
	if(file_.is_open()){
		file_.seekg(0, ios::end);
		size_t fileSize = file_.tellg();
		int rowSize = (int)sizeof(dependenciesRow);
		int nRows = fileSize/rowSize;

		printf("File size is %d bytes\n", (int)fileSize);
		printf("Row size is %d bytes\n", (int)rowSize);
		printf("%d rows \n", nRows);
		
		if(nRows > 0){
			dependenciesRow currentRow;
			file_.seekg(0, ios::beg);
			for(int rowIndex = 0; rowIndex < nRows; rowIndex++){
				file_.read((char*)&currentRow, rowSize);

				printf("%d: {id:%d, id_child:%d, id_parent:%d}\n",
					rowIndex,
					currentRow.id,
					currentRow.id_child,
					currentRow.id_parent);
			}
		}
	}		
};

dependenciesRow DependenciesTable::AssignNewID(int & rowStartByte){
	dependenciesRow newRow;

	//Set all values to "missing" indicators
	metadata_.maxID += 1;

	newRow.id = metadata_.maxID;
	newRow.id_child = DEPENDENCY_DATA_MISSING;
	newRow.id_parent = DEPENDENCY_DATA_MISSING;
	
	if(file_.is_open()){
		file_.seekg(0, ios::end);
		size_t fileSize = file_.tellg();
		rowStartByte = (int)fileSize;
		file_.write((char*)&newRow,(int)sizeof(dependenciesRow));
	    file_.seekg(0, ios::beg);
	}
	
	return(newRow);
};

void DependenciesTable::ModifyRow(dependenciesRow row, int rowStartByte){
	if(file_.is_open()){
		printf("modifying row\n");
		printf("%d: {id:%d, id_child:%d, id_parent:%d}\n",
			rowStartByte,
			row.id,
			row.id_child,
			row.id_parent);

		file_.seekg(rowStartByte, ios::beg);
		file_.write((char*)&row,(int)sizeof(dependenciesRow));
	    file_.seekg(0, ios::beg);
	}
};

int DependenciesTable::AddDependency(int childID, int parentID){
	printf("Adding dependency %d, %d\n", childID, parentID);
	//Create data
	int rowStartByte;
	dependenciesRow dr = AssignNewID(rowStartByte);
	dr.id_child = childID;
	dr.id_parent = parentID;
	ModifyRow(dr, rowStartByte);
	return(dr.id);
};

std::vector<int> DependenciesTable::GetParents(int id_child){
	vector<int> parents;
	if(file_.is_open()){
		file_.seekg(0, ios::end);
		size_t fileSize = file_.tellg();
		int rowSize = (int)sizeof(dependenciesRow);
		int nRows = fileSize/rowSize;

		if(nRows > 0){
			dependenciesRow currentRow;
			file_.seekg(0, ios::beg);
			for(int rowIndex = 0; rowIndex < nRows; rowIndex++){
				file_.read((char*)&currentRow, rowSize);

				if (currentRow.id_child == id_child){
					parents.push_back(currentRow.id_parent);
				}
			}
		}
	}
	return(parents);
};

void DependenciesTable::PrintParents(int id_child){
	std::vector<int> parents = GetParents(id_child);
	std::vector<int>::iterator iter = parents.begin();

	printf("Parents for %d:\n",id_child);

	while(iter != parents.end()){
		std::cout << (*iter) << ", " << std:: endl;
		iter++;
	}
};


std::vector<int> DependenciesTable::GetChildren(int id_child){
	vector<int> parents;
	if(file_.is_open()){
		file_.seekg(0, ios::end);
		size_t fileSize = file_.tellg();
		int rowSize = (int)sizeof(dependenciesRow);
		int nRows = fileSize/rowSize;

		if(nRows > 0){
			dependenciesRow currentRow;
			file_.seekg(0, ios::beg);
			for(int rowIndex = 0; rowIndex < nRows; rowIndex++){
				file_.read((char*)&currentRow, rowSize);

				if (currentRow.id_parent == id_child){
					parents.push_back(currentRow.id_child);
				}
			}
		}
	}
	return(parents);
};

void DependenciesTable::PrintChildren(int id_child){
	std::vector<int> children = GetChildren(id_child);
	std::vector<int>::iterator iter = children.begin();

	printf("Children for %d:\n",id_child);

	while(iter != children.end()){
		std::cout << (*iter) << ", " << std:: endl;
		iter++;
	}
};