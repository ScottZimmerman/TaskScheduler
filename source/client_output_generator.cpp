#include "client_output_generator.h"
ClientOutputGenerator::ClientOutputGenerator(){

};

ClientOutputGenerator::~ClientOutputGenerator(){

};

void ClientOutputGenerator::PrintStdOut(boost::shared_ptr<schedulerMessages::Msg> msg){
	if(msg->has_response()){
		const schedulerMessages::Response & response = msg->response();
		if(response.has_assign()){
			const schedulerMessages::Response_assign & response_assign = response.assign();
			if(response_assign.multiple()){
				printf("ids\n");
				for(int i = 0; i < response_assign.ids_size(); i++){
					printf("%d",response_assign.ids(i));
					if( i != (response_assign.ids_size() - 1)){
						printf(",");
					}
				}
			}else{
				printf("id\n%d",response_assign.id());
			}
			
		}else if(response.has_queue()){
			const schedulerMessages::Response_queue & response_queue = response.queue();
			printf("\n");

		}else if(response.has_receive()){
			const schedulerMessages::Response_receive & response_receive = response.receive();
			if(response_receive.input_bundle().length() > 0){
				printf("input_bundle\n%s",response_receive.input_bundle().c_str());
			}else{
				printf("input_bundle\n");
			}

		}else if(response.has_requeue()){
			const schedulerMessages::Response_requeue & response_requeue = response.requeue();
			printf("requeue_failed\n%d",(int)response_requeue.requeue_failed());

		}else if(response.has_finish()){
			const schedulerMessages::Response_finish & response_finish = response.finish();
			printf("\n");

		}else if(response.has_cancel()){
			const schedulerMessages::Response_cancel & response_cancel = response.cancel();
			printf("\n");

		}else if(response.has_add_dependency()){
			const schedulerMessages::Response_add_dependency & response_add_dependency = response.add_dependency();
			printf("\n");

		}else{
			fprintf(stderr,"ERROR: Message response subtype not recognized\n");
		}
	}else{
		fprintf(stderr,"ERROR: Message does not have response\n");
	}
};