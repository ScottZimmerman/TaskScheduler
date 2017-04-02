#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include <vector>
#include <fstream>
#include <boost/unordered_map.hpp>
#include "event.h"

typedef void (*eventHandler)(void *, boost::shared_ptr<Event> event);

struct NonStatMemCB{
  eventHandler fn;
  void * listener;
};

typedef boost::unordered_map<Event::Type, std::vector<NonStatMemCB> > callbackMap;

class EventQueue
{
private:
  static callbackMap callbacks_;

public:
  EventQueue();
  ~EventQueue();
  
  static void Register(
  	Event::Type,
  	NonStatMemCB
  );
  static void Add(boost::shared_ptr<Event> event);
};


#endif