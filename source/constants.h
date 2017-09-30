#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <string.h>

const unsigned int INPUT_BUNDLE_NAME_SIZE = 100; 
const unsigned int INSTANCE_NAME_SIZE = 45; 
namespace Message{
	const int MSG_OK = 0;
	const int MSG_NOT_OK = 1;
}
const int MESSAGE_SIZE = 2048;
const std::string DATA_FOLDER = "data";
#endif