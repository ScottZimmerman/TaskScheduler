#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <boost/shared_ptr.hpp>
#include "msg.pb.h"

struct Event{

	enum Type{
		NONE=-1,
		SERVER_REQUEST=0,
		SCHEDULER_RESULT_BASE=1,
		SCHEDULER_RESULT_MAX=1001
	};

	Type type;
	unsigned short nodeID;

	Event():type(Event::NONE){};
  	Event(Event::Type eventType):type(eventType){};

};

inline std::ostream& operator<<(std::ostream& stream,const Event & event){
  	stream << "{" << std::endl;
	stream << "\ttype: " << event.type << std::endl;
    stream << "}" << std::endl;
};

struct Server_Request_Event : public Event{
	unsigned int connectionID;
	boost::shared_ptr<schedulerMessages::Msg> msg;
	Server_Request_Event(){};//Remove
	Server_Request_Event(Event::Type eventType):Event(eventType){};
};

#endif