#include "listener.h"
Listener::Listener(std::string name)
:
	name_(name),
	head_(0),
	tail_(0)
{};
Listener::~Listener(){};

void Listener::Add_Wrapper(void * f, boost::shared_ptr<Event> event){
	// explicitly cast to a pointer to Listener
	Listener* mySelf = (Listener*) f;

	// call member
	mySelf->Add(event);

};
void Listener::Add(boost::shared_ptr<Event> event){	
	//printf("Listener::Add for %s: msg = %s\n",name_.c_str(), event.msg.c_str());

	assert((tail_ + 1) % Listener::RING_BUFFER_SIZE != head_);

	boost::lock_guard<boost::mutex> lock(queue_mutex);
	queue_[tail_] = event;

	tail_ = (tail_ + 1) % Listener::RING_BUFFER_SIZE;

};

void Listener::Update(){
	boost::lock_guard<boost::mutex> lock(queue_mutex);
	std::vector<boost::shared_ptr<Event> > responses;
	boost::shared_ptr<Event> response;
	bool anyResponse = 0;
	while (head_ != tail_){
		HandleEvent(queue_[head_], response, anyResponse);
		if(anyResponse == 1){
			responses.push_back(response);
		}
		head_ = (head_ + 1) % Listener::RING_BUFFER_SIZE;
	}

	std::vector<boost::shared_ptr<Event> >::iterator iter = responses.begin();
	while(iter != responses.end()){
		EventQueue::Add(*iter);
		iter++;
	}
}

void Listener::HandleEvent(boost::shared_ptr<Event> event, boost::shared_ptr<Event> & response, bool & anyResponse){
	std::cout << "Listener::HandleEvent" << std::endl;
};