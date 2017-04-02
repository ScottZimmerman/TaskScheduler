#include "eventQueue.h"
callbackMap EventQueue::callbacks_;

EventQueue::EventQueue(){};
EventQueue::~EventQueue(){};

void EventQueue::Register(
	Event::Type eventType, 
	NonStatMemCB nsmcb
){

	callbackMap::iterator iter = EventQueue::callbacks_.find (eventType);
	if(iter == EventQueue::callbacks_.end()){
		//Not found, create it.
		std::vector<NonStatMemCB> vnsmcb;
		vnsmcb.push_back(nsmcb);
		EventQueue::callbacks_.insert(std::make_pair<Event::Type, std::vector<NonStatMemCB> >(eventType,vnsmcb));
	}else{
		iter->second.push_back(nsmcb);	
	}
};
  
void EventQueue::Add(boost::shared_ptr<Event> event){
   
	callbackMap::iterator iter = EventQueue::callbacks_.find (event->type);
	if(iter != EventQueue::callbacks_.end()){
		
	    std::vector<NonStatMemCB>::iterator cb_iter = iter->second.begin();
	    while(cb_iter != iter->second.end()){
	    	cb_iter->fn(cb_iter->listener, event);
	    	cb_iter++;
	    }
	}
};