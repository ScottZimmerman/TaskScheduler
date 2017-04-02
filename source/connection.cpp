#include "connection.h"
unsigned int Connection::counter = 0;
Connection::Connection():Listener("Connection"), accepting_(1){
	id_ = Connection::counter;
	Connection::counter++;
};

void Connection::HandleEvent(boost::shared_ptr<Event> event, boost::shared_ptr<Event> & response, bool & anyResponse){
	Send(event);
};

void Connection::Run(){
	int n;
	while(true){
		if(accepting_){
        	Accept();
    	}else{
    		//Call the listener method that handles sending
    		Update();
    	}
    }
    close(sockfd);
};

void Connection::Accept(){
	int n;
    //To Do: Make this async. And then allow multiple sockets per thread.
	newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    
    if (newsockfd < 0) {
          Error("ERROR on accept");
    }
    
    //Read Request Header
    int message_size_net;
    int message_size;
    read(newsockfd, &message_size_net, 4);
    message_size = ntohl(message_size_net);

    //Send response that header is received
    int msgOK = htonl(Message::MSG_OK);
    n = write(newsockfd, (const char*)&msgOK, 4);
    if (n < 0) {
         Error("ERROR writing request header");
    }

    //Read Request Body
    bzero(buffer, Connection::BUFFER_SIZE);
    n = read(newsockfd,buffer,message_size);
    if (n < 0){
        Error("ERROR reading request body");
    }

    std::string buf = std::string(buffer);
    
    boost::shared_ptr<schedulerMessages::Msg> my_msg(new schedulerMessages::Msg);
    my_msg->ParseFromString(buf);
    
    
    //Add the event that a message was received
    boost::shared_ptr<Server_Request_Event> request(new Server_Request_Event);
    request->type = Event::SERVER_REQUEST;
    request->connectionID = id_;
    request->msg = my_msg;
    
    EventQueue::Add(request);
    accepting_ = 0;
};

void Connection::Send(boost::shared_ptr<Event> event){

    boost::shared_ptr<Server_Request_Event> pD = boost::static_pointer_cast<Server_Request_Event>(event);
    
    boost::shared_ptr<schedulerMessages::Msg> my_msg = pD->msg;
    
    int n;
    std::string buf;
    my_msg->SerializeToString(&buf);

    //Send the response header
    int message_size = (int)buf.length();
    int message_size_net = htonl(message_size);//deals with endianness

    n = write(newsockfd, (const char*)&message_size_net, 4);
    if (n < 0) 
         Error("ERROR writing request header");
    
    //Wait for client to be ready
    read(newsockfd, &message_size_net, 4);
    int msgOK = ntohl(message_size_net);

    //Send Result Body
    n = write(newsockfd,buf.c_str(),strlen(buf.c_str()));
    if (n < 0) 
         Error("ERROR writing result body");

    close(newsockfd);
    accepting_ = 1;
};

int Connection::GetID(Connection & c){
	return(c.id_);
}

void Connection::Error(const char *msg)
{
    perror(msg);
    exit(1);
}
