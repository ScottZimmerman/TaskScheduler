#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H
#include <boost/lexical_cast.hpp>
#include <fstream>
#include "msg.pb.h"

class CommandLineParser{
private:

    const static int RequestTypeIndex;
public:
    CommandLineParser();
    ~CommandLineParser();
    static schedulerMessages::Msg CreateMessage(int argc, char * argv[]);
};

#endif