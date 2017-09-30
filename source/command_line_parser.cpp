#include "command_line_parser.h"
const int CommandLineParser::RequestTypeIndex = 3;
CommandLineParser::CommandLineParser(){

};
CommandLineParser::~CommandLineParser(){

};

schedulerMessages::Msg CommandLineParser::CreateMessage(int argc, char * argv[]){
    //PARSE COMMAND LINE ARGUMENTS
    //Check argument counts
    if (!(argc == 4 || argc == 5 || argc == 6 || argc == 7 || argc == 8)) {
        fprintf(stderr,"Usage:\n");
        fprintf(stderr, "--------argc == 4--------\n");
        fprintf(stderr,"%s <hostname> <port> receive\n",argv[0]);
        
        fprintf(stderr, "--------argc == 5--------\n");
        fprintf(stderr,"%s <hostname> <port> assign <job_name>\n",argv[0]);
        fprintf(stderr,"%s <hostname> <port> receive <submitted_instance_name>\n",argv[0]);

        fprintf(stderr, "--------argc == 6--------\n");
        fprintf(stderr,"%s <hostname> <port> finish <job_name> <task_id>\n",argv[0]);
        fprintf(stderr,"%s <hostname> <port> cancel <job_name> <task_id>\n",argv[0]);
        fprintf(stderr,"%s <hostname> <port> requeue <job_name> <task_id>\n",argv[0]);
        fprintf(stderr,"%s <hostname> <port> assign <job_name> <count>\n",argv[0]);

        fprintf(stderr, "--------argc == 7--------\n");
        fprintf(stderr,"%s <hostname> <port> add_dependency <job_name> <parent_id> <child_id>\n",argv[0]);
        
        fprintf(stderr, "--------argc == 8--------\n");
        fprintf(stderr,"%s <hostname> <port> queue <job_name> <task_id> <input_bundle> <task_queued_from>\n",argv[0]);

       exit(0);
    }

    //Check argument counts line up with function
    if(argc == 8){
        if(strcmp(argv[CommandLineParser::RequestTypeIndex],"queue") != 0){
            fprintf(stderr,"Request type (argument %d) must be 'queue' if running with 8 arguments\n",CommandLineParser::RequestTypeIndex);
            exit(1);
        }
    }else if (argc == 7){
        if(
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"add_dependency") != 0)
        ){
            fprintf(stderr,"Request type (argument %d) must be 'add_dependency' if running with 7 arguments\n",CommandLineParser::RequestTypeIndex);
            exit(1);
        }
    }else if (argc == 6){
        if(
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"finish") != 0) &&
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"cancel") != 0) &&
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"requeue") != 0) &&
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"assign") != 0)
        ){
            fprintf(stderr,"Request type (argument %d) must be 'finish', 'cancel', 'requeue', or 'assign' if running with 6 arguments\n",CommandLineParser::RequestTypeIndex);
            exit(1);
        }
    }else if (argc == 5){
        if(
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"assign") != 0) &&
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"receive") != 0)
        ){
            fprintf(stderr,"Request type (argument %d) must be 'assign' or 'receive' if running with 5 arguments\n",CommandLineParser::RequestTypeIndex);
            exit(1);
        }
    }else if (argc == 4){
        if(
            (strcmp(argv[CommandLineParser::RequestTypeIndex],"receive") != 0)
        ){
            fprintf(stderr,"Request type (argument %d) must be 'receive' if running with 4 arguments\n",CommandLineParser::RequestTypeIndex);
            exit(1);
        }
    }
    
    //CREATE THE MESSAGE
    schedulerMessages::Msg msg;
    schedulerMessages::Request * request = msg.mutable_request();
    if(strcmp(argv[CommandLineParser::RequestTypeIndex],"assign")==0){
        schedulerMessages::Request_assign * request_assign = request->mutable_assign();
        request_assign->set_job(argv[4]);
        
        if(argc == 6){
            int count = boost::lexical_cast<int>(argv[5]);
            if(count > 0){
                request_assign->set_count(count);
            }else{
                fprintf(stderr,"count (arg 6) must be positive\n");
                exit(1);
            }
        }else{
            request_assign->set_count(1);
        }
    
    }else if(strcmp(argv[CommandLineParser::RequestTypeIndex],"queue")==0){
        schedulerMessages::Request_queue * request_queue = request->mutable_queue();    
        request_queue->set_job(argv[4]);
        request_queue->set_id(boost::lexical_cast<int>(argv[5]));
        request_queue->set_input_bundle(argv[6]);
        request_queue->set_task_queued_from(boost::lexical_cast<int>(argv[7]));

    }else if(strcmp(argv[CommandLineParser::RequestTypeIndex],"receive")==0){
        schedulerMessages::Request_receive * request_receive = request->mutable_receive();
        if(argc == 5){
            request_receive->set_instance_name(argv[4]);
        }else{
            request_receive->set_instance_name("NO_INSTANCE");
        }

    }else if(strcmp(argv[CommandLineParser::RequestTypeIndex],"requeue")==0){
        schedulerMessages::Request_requeue * request_requeue = request->mutable_requeue();        
        request_requeue->set_job(argv[4]);
        request_requeue->set_id(boost::lexical_cast<int>(argv[5]));

    }else if(strcmp(argv[CommandLineParser::RequestTypeIndex],"finish")==0){
        schedulerMessages::Request_finish * request_finish = request->mutable_finish();        
        request_finish->set_job(argv[4]);
        request_finish->set_id(boost::lexical_cast<int>(argv[5]));

    }else if(strcmp(argv[CommandLineParser::RequestTypeIndex],"cancel")==0){
        schedulerMessages::Request_cancel * request_cancel = request->mutable_cancel();        
        request_cancel->set_job(argv[4]);
        request_cancel->set_id(boost::lexical_cast<int>(argv[5]));

    }else if(strcmp(argv[CommandLineParser::RequestTypeIndex],"add_dependency")==0){
        schedulerMessages::Request_add_dependency * request_add_dependency = request->mutable_add_dependency();
        request_add_dependency->set_job(argv[4]);
        request_add_dependency->set_parent_id(boost::lexical_cast<int>(argv[5]));
        request_add_dependency->set_child_id(boost::lexical_cast<int>(argv[6]));        
    
    }else{
        fprintf(stderr,"Invalid value for request type (argument %d): '%s'",
            CommandLineParser::RequestTypeIndex,
            argv[CommandLineParser::RequestTypeIndex]
        );
        exit(1);
    }
    return(msg);
};