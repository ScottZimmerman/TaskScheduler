#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/filesystem.hpp>
#include "fileInterface.h"

typedef boost::unordered_map<boost::filesystem::path, boost::shared_ptr<FileInterface> > pathMap;

class FileManager{
	private:
		static pathMap files_;
	public:
	    FileManager();
	    ~FileManager();
	    static boost::shared_ptr<FileInterface> Get(boost::filesystem::path path);
};

#endif