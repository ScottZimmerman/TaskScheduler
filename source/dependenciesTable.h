#ifndef DEPENDENCIES_TABLE_H
#define DEPENDENCIES_TABLE_H

#include <fstream>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include "fileManager.h"
#include "fileInterface.h"

const int DEPENDENCY_DATA_MISSING = -1;

struct dependenciesRow {
	int id;
	int id_child;
	int id_parent;	
};

struct dependenciesMetadata {
	int maxID;
};

class DependenciesTable{
	private:
		boost::shared_ptr<FileInterface> dataFile_;
		boost::shared_ptr<FileInterface> metadataFile_;

		std::fstream * file_;
		std::fstream * metadata_file_;
		dependenciesMetadata metadata_;

	public:
		DependenciesTable();
		DependenciesTable(boost::filesystem::path jobPath);
		~DependenciesTable();

		dependenciesRow GetRow(int id);
		void PrintAll();
		dependenciesRow AssignNewID(int & rowStartByte);
		void ModifyRow(dependenciesRow row, int rowStartByte);
		int AddDependency(int childID, int parentID);
		
		std::vector<int> GetParents(int id_job);
		void PrintParents(int id_job);
		
		std::vector<int> GetChildren(int id_job);
		void PrintChildren(int id_job);
	
};

#endif