#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H
#include <fstream>
#include <boost/filesystem.hpp>

class FileInterface
{
  private:
    boost::filesystem::path filePath_;
    std::fstream file_;

  public:
    FileInterface();
    FileInterface(boost::filesystem::path filePath);
    ~FileInterface();
    std::fstream * Get();
    boost::filesystem::path GetPath();
};


#endif