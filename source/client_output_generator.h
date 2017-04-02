#ifndef CLIENT_OUTPUT_GENERATOR_H
#define CLIENT_OUTPUT_GENERATOR_H
#include <fstream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "msg.pb.h"

class ClientOutputGenerator{
private:
public:
    ClientOutputGenerator();
    ~ClientOutputGenerator();
    static void PrintStdOut(boost::shared_ptr<schedulerMessages::Msg>);
};

#endif