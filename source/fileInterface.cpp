#include "fileInterface.h"
using namespace std;
FileInterface::FileInterface(){};
FileInterface::FileInterface(boost::filesystem::path filePath){
	filePath_ = filePath;
	file_.open(filePath.c_str(), fstream::in | fstream::out | fstream::binary);
    if(!file_.is_open()){
    	file_.open(filePath.c_str(), fstream::out | fstream::binary);
    	file_.close();
    	file_.open(filePath.c_str(), fstream::in | fstream::out | fstream::binary);
    }
};
FileInterface::~FileInterface(){};
std::fstream * FileInterface::Get(){
	return(&file_);
};
boost::filesystem::path FileInterface::GetPath(){
	return(filePath_);
}