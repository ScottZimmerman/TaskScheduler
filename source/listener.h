#ifndef LISTENER_H
#define LISTENER_H
#include <fstream>
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include "event.h"
#include "assert.h"
#include "eventQueue.h"

class Listener{
private:
	//Ring buffer as a queue
	static const int RING_BUFFER_SIZE = 1024;
	boost::mutex queue_mutex;
    boost::shared_ptr<Event> queue_[Listener::RING_BUFFER_SIZE];
    unsigned int head_;
    unsigned int tail_;

protected:
	std::string name_;

public:
    Listener(std::string name);
    ~Listener();

    static void Add_Wrapper(void * f, boost::shared_ptr<Event> event);
    void Add(boost::shared_ptr<Event> event);
    void Update();
    virtual void HandleEvent(boost::shared_ptr<Event> event, boost::shared_ptr<Event> & response, bool & anyResponse);
};

#endif