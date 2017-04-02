#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fstream>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "stdint.h"
#include "msg.pb.h"
#include "constants.h"
#include "command_line_parser.h"
#include "client_output_generator.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    
    schedulerMessages::Msg my_msg = CommandLineParser::CreateMessage(argc, argv);

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[MESSAGE_SIZE];

    //Open socket
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    //Find host
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    //Set server address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    //Prepare the message
    std::string buf;
    my_msg.SerializeToString(&buf);
    
    //Send the request header
    int message_size = (int)buf.length();
    int message_size_net = htonl(message_size);//deals with endianness

    n = write(sockfd, (const char*)&message_size_net, 4);
    if (n < 0) 
         error("ERROR writing request header");

    //Wait for server to be ready
    read(sockfd, &message_size_net, 4);
    int msgOK = ntohl(message_size_net);
   
    //Write request body to socket
    n = write(sockfd,buf.c_str(),strlen(buf.c_str()));
    if (n < 0) 
         error("ERROR writing request body");
    
    //Read result header from socket
    read(sockfd, &message_size_net, 4);
    message_size = ntohl(message_size_net);
    
    //Send response that result header is received
    msgOK = htonl(Message::MSG_OK);
    n = write(sockfd, (const char*)&msgOK, 4);
    if (n < 0) 
         error("ERROR writing request header");

    //Read result body
    bzero(buffer,MESSAGE_SIZE);
    n = read(sockfd,buffer,message_size);
    if (n < 0){
        error("ERROR reading result body");
    }

    buf = std::string(buffer);
    boost::shared_ptr<schedulerMessages::Msg> result_msg(new schedulerMessages::Msg);

    result_msg->ParseFromString(buf);
    
    ClientOutputGenerator::PrintStdOut(result_msg);
    
    close(sockfd);
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}