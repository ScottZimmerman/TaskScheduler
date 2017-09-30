#include "fileManager.h"
pathMap FileManager::files_;
FileManager::FileManager(){};
FileManager::~FileManager(){};

boost::shared_ptr<FileInterface> FileManager::Get(boost::filesystem::path path
){
	boost::shared_ptr<FileInterface> result;

	if(files_.find(path) == files_.end()){
		boost::shared_ptr<FileInterface> r(new FileInterface(path));
		result = r;
		files_[path]  = result;
	}else{
		result = files_.at(path);
	}

	return(result);
};