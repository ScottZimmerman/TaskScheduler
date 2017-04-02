#ifndef DEPENDENCIES_TABLE_H
#define DEPENDENCIES_TABLE_H

#include <fstream>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

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
		std::fstream file_;
		std::fstream metadata_file_;
		dependenciesMetadata metadata_;

	public:
		DependenciesTable();
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