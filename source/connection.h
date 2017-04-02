#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "listener.h"
#include "event.h"
#include "constants.h"
#include "msg.pb.h"

class Connection : public Listener{
	private:
		static unsigned int counter;
		unsigned int id_;
		bool accepting_; //Remove later when client can handle async.
	public:
		Connection();
		void HandleEvent(boost::shared_ptr<Event> event, boost::shared_ptr<Event> & response, bool & anyResponse);
		void Run();
		void Accept();
		void Send(boost::shared_ptr<Event> event);

		static int GetID(Connection &);
		static void Error(const char *msg);
		static const unsigned int MAX_WAITING = 5;
		static const unsigned short BUFFER_SIZE = 256;

		int sockfd;
		int newsockfd; 
		int portno;
		char buffer[BUFFER_SIZE];
		sockaddr_in serv_addr;
		sockaddr_in cli_addr;
		socklen_t clilen;
};

#endif
