#include "connectionManager.h"
ConnectionManager::ConnectionManager():nConnections_(0){};
ConnectionManager::~ConnectionManager(){
	CloseAll();
};

void ConnectionManager::Setup(
    unsigned short minPort, 
    unsigned short numPorts
){
	for(int port = minPort; port < (minPort+numPorts); port++){
		New(port);
	}
};

void ConnectionManager::New(int port){
    if(nConnections_ < ConnectionManager::MAX_CONNECTIONS){
        Connection & c = connections_[nConnections_];
        
        //Register the connection as a listener for scheduler results
        NonStatMemCB connection_cbdata;
        connection_cbdata.fn = Listener::Add_Wrapper;
        connection_cbdata.listener = &connections_[nConnections_];
        EventQueue::Register((Event::Type)((int)Event::SCHEDULER_RESULT_BASE + Connection::GetID(c)),connection_cbdata);

        c.sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (c.sockfd < 0){ 
            Error("ERROR opening socket");
        }
        bzero((char *) &c.serv_addr, sizeof(c.serv_addr));
        c.portno = port;
        bzero(c.buffer,Connection::BUFFER_SIZE);
        c.serv_addr.sin_family = AF_INET;
        c.serv_addr.sin_addr.s_addr = INADDR_ANY;
        c.serv_addr.sin_port = htons(c.portno);
        if (bind(c.sockfd, (struct sockaddr *) &c.serv_addr, sizeof(c.serv_addr)) < 0){
                printf("Port: %d\n",port);
                Error("ERROR on binding");
        }
        c.clilen = sizeof(c.cli_addr);
        listen(c.sockfd, Connection::MAX_WAITING);

        nConnections_++;
    }else{
        Error("ERROR Tried to open more than ConnectionManager::MAX_CONNECTIONS connections");
    }
}

void ConnectionManager::CreateThreads(){
    for(int i = 0; i < nConnections_; i++){
        threads_.create_thread(boost::bind(Accept,boost::ref(connections_[i])));
    }
}

void ConnectionManager::Accept(Connection & con){
    con.Run();
}

void ConnectionManager::CloseAll(){

    for(int i = 0; i < nConnections_; i++){
        close(connections_[i].newsockfd);
    }

}
void ConnectionManager::Error(const char *msg)
{
    perror(msg);
    exit(1);
}
