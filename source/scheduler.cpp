#include "scheduler.h"
bool Scheduler::finished = 0;
Scheduler::Scheduler():
	Listener("Scheduler"){
};


Scheduler::~Scheduler(){};
bool Scheduler::Finished(){
	return(finished);
}
void Scheduler::HandleEvent(boost::shared_ptr<Event> event, boost::shared_ptr<Event> & response, bool & anyResponse){

	printf("----------------------------EVENT---------------------------\n");
	//Create pD: Pointer to derived event
	boost::shared_ptr<Server_Request_Event> pD = boost::static_pointer_cast<Server_Request_Event>(event);
	Log(pD);

	//Do something with the tables here depending on the details of the event
    boost::shared_ptr<schedulerMessages::Msg> my_msg = pD->msg;
    boost::shared_ptr<schedulerMessages::Msg> response_msg = Parse(my_msg);
    
	//Return response
	boost::shared_ptr<Server_Request_Event> responseSRE(new Server_Request_Event);
	responseSRE->connectionID = pD->connectionID;
	responseSRE->msg = response_msg;
	responseSRE->type = (Event::Type)((int)Event::SCHEDULER_RESULT_BASE + pD->connectionID);
	Log(responseSRE);
	response = responseSRE;
	anyResponse = 1;
};

boost::shared_ptr<schedulerMessages::Msg> Scheduler::Parse(boost::shared_ptr<schedulerMessages::Msg> msg){
	
	const schedulerMessages::Request & request = msg->request();
	boost::shared_ptr<schedulerMessages::Msg> response_msg(new schedulerMessages::Msg);
	schedulerMessages::Response * response = response_msg->mutable_response();
	
	if(request.has_assign()){
		//Needs to return:
		// id(s)
		const schedulerMessages::Request_assign & request_assign = request.assign();
		schedulerMessages::Response_assign * response_assign = response->mutable_assign();    

		bool multiple = request_assign.count() != 1;
		response_assign->set_multiple(multiple);
		
		if(multiple){
			int rowStartByte;
			tasksRow tr;
			for(int i = 0; i < request_assign.count(); i++){
				tr = AssignNewID(
					rowStartByte,
					request_assign.job()
				);
				response_assign->add_ids(tr.id);
			}
		}else{
			int rowStartByte;
			tasksRow tr = AssignNewID(
				rowStartByte,
				request_assign.job()
			);
			response_assign->set_id(tr.id);	
		}
		
	}else if(request.has_queue()){
		//Needs to return:
		// Nothing.
		const schedulerMessages::Request_queue & request_queue = request.queue();
		schedulerMessages::Response_queue * response_queue = response->mutable_queue();  

		Queue(
			request_queue.job(),
			request_queue.id(), 
			request_queue.input_bundle(),
			request_queue.task_queued_from()
		);
		
	}else if(request.has_receive()){
		//Needs to return:
		// input_bundle_name
		const schedulerMessages::Request_receive & request_receive = request.receive();
		schedulerMessages::Response_receive * response_receive = response->mutable_receive();  
		
		bool taskFound;
		tasksRow tr = Receive(
			taskFound, 
			request_receive.instance_name()
		);

		if(taskFound){ 
			response_receive->set_input_bundle(tr.input_bundle_name);
		}else{
			response_receive->set_input_bundle("");
		}

	}else if(request.has_requeue()){
		//Needs to return:
		// 0 if (@number_attempts+1) < globals variable "N_JOB_ATTEMPTS"
		// 1 otherwise
		const schedulerMessages::Request_requeue & request_requeue = request.requeue();
		schedulerMessages::Response_requeue * response_requeue = response->mutable_requeue();  

		bool requeue_failed = Requeue(
			request_requeue.job(),
			request_requeue.id()
		);
		response_requeue->set_requeue_failed(requeue_failed);

	}else if(request.has_finish()){
		//Needs to return:
		// Nothing.
		const schedulerMessages::Request_finish & request_finish = request.finish();
		schedulerMessages::Response_finish * response_finish = response->mutable_finish();  

		Finish(
			request_finish.job(),
			request_finish.id()
		);
	
	}else if(request.has_cancel()){
		//Needs to return:
		// Nothing.
		const schedulerMessages::Request_cancel & request_cancel = request.cancel();
		schedulerMessages::Response_cancel * response_cancel = response->mutable_cancel();  

		Cancel(
			request_cancel.job(),
			request_cancel.id()
		);
	
	}else if(request.has_add_dependency()){
		//Needs to return:
		// Nothing.
		const schedulerMessages::Request_add_dependency & request_add_dependency = request.add_dependency();
		schedulerMessages::Response_add_dependency * response_add_dependency = response->mutable_add_dependency();  

		AddDependency(
			request_add_dependency.job(),
			request_add_dependency.child_id(), 
			request_add_dependency.parent_id()
		);
	}else{
		//shouldn't happen
	}
	
	return(response_msg);
};

tasksRow Scheduler::AssignNewID(
		int & rowStartByte, //Is rowStartByte still used?
 		std::string job
 	){
	TasksTable * pTasksTable = JobManager::GetTasksTable(job);
	return(pTasksTable->AssignNewID(rowStartByte));
};

void Scheduler::Queue(
	std::string job,
	int id, 
	std::string input_bundle_name,
	int job_launched_from
){
	TasksTable * pTasksTable = JobManager::GetTasksTable(job);
	pTasksTable->Queue(
		id,
		input_bundle_name,
		job_launched_from
	);
};

tasksRow Scheduler::Receive(bool & taskFound, std::string submitted_instance){
	return(JobManager::Receive(taskFound, submitted_instance));
};

bool Scheduler::Requeue(
	std::string job, 
	int id
){
	TasksTable * pTasksTable = JobManager::GetTasksTable(job);
	return(pTasksTable->Requeue(id));
};

void Scheduler::Finish(
	std::string job,
	int id
){
	TasksTable * pTasksTable = JobManager::GetTasksTable(job);
	pTasksTable->Finish(id);
};

void Scheduler::Cancel(
	std::string job,
	int id
){
	TasksTable * pTasksTable = JobManager::GetTasksTable(job);
	pTasksTable->Cancel(id);
};

void Scheduler::AddDependency(
	std::string job,
	int childID, 
	int parentID
){
	TasksTable * pTasksTable = JobManager::GetTasksTable(job);
	pTasksTable->AddDependency(childID, parentID);
}

void Scheduler::AssignNewID_Multiple( //Function not used?
	std::string job,
	int num_to_assign, 
	std::vector<int> & result
){
	int rowStartByte;
	tasksRow tr;
	for(int i = 0; i < num_to_assign; i++){
		tr = AssignNewID(rowStartByte,job);
		result.push_back(tr.id);
	}
};

void Scheduler::Log(boost::shared_ptr<Server_Request_Event> event){
	boost::shared_ptr<schedulerMessages::Msg> msg = event->msg;
	if(msg->has_request()){
		printf("Request: ");
		const schedulerMessages::Request & request = msg->request();
		if(request.has_assign()){
			const schedulerMessages::Request_assign & request_assign = request.assign();
			printf("Assign:\n"
				"\tjob: %s\n"
				"\tcount: %d",
				request_assign.job().c_str(),
				request_assign.count());
			//Fill in multiple
		}else if(request.has_queue()){
			const schedulerMessages::Request_queue & request_queue = request.queue();
			printf(
				"Queue:\n"
				"\tjob: %s\n"
				"\tid: %d\n"
				"\tinput_bundle: %s\n"
				"\ttask_queued_from: %d",
				request_queue.job().c_str(),
				(int)request_queue.id(), 
				request_queue.input_bundle().c_str(),
				(int)request_queue.task_queued_from()
			);
		}else if(request.has_receive()){
			const schedulerMessages::Request_receive & request_receive = request.receive();
			printf(
				"Receive:\n"
				"\tinstance_name: %s",
				request_receive.instance_name().c_str()
			);
		}else if(request.has_requeue()){
			const schedulerMessages::Request_requeue & request_requeue = request.requeue();
			printf(
				"Requeue:\n"
				"\tjob: %s\n"
				"\tid: %d",
				request_requeue.job().c_str(),
				(int)request_requeue.id()
			);
		}else if(request.has_finish()){
			const schedulerMessages::Request_finish & request_finish = request.finish();
			printf(
				"Finish:\n"
				"\tjob: %s\n"
				"\tid: %d",
				request_finish.job().c_str(),
				(int)request_finish.id()
			);
		}else if(request.has_cancel()){
			const schedulerMessages::Request_cancel & request_cancel = request.cancel();
			printf(
				"Cancel:\n"
				"\tjob: %s\n"
				"\tid: %d",
				request_cancel.job().c_str(),
				(int)request_cancel.id()
			);
		}else if(request.has_add_dependency()){
			const schedulerMessages::Request_add_dependency & request_add_dependency = request.add_dependency();
			printf(
				"Add dependency:\n"
				"\tjob: %s\n"
				"\tchild_id: %d\n"
				"\tparent_id: %d",
				request_add_dependency.job().c_str(),
				(int)request_add_dependency.child_id(),
				(int)request_add_dependency.parent_id()
			);
		}else{
			printf("subtype not recognized");
		}
		printf("\n");
	}else if(msg->has_response()){
		printf("Response: ");
		const schedulerMessages::Response & response = msg->response();
		if(response.has_assign()){
			const schedulerMessages::Response_assign & response_assign = response.assign();
			printf(
				"Assign:\n"
			);
			if(response_assign.multiple()){
				printf("ids:\n");
				for(int i = 0; i < response_assign.ids_size(); i++){
					printf("%d",response_assign.ids(i));
					if( i != (response_assign.ids_size() - 1)){
						printf(", ");
					}
				}
			}else{
				printf(
					"\tid: %d",
					(int)response_assign.id()
				);		
			}

		}else if(response.has_queue()){
			const schedulerMessages::Response_queue & response_queue = response.queue();
			printf(
				"Queue"
			);

		}else if(response.has_receive()){
			const schedulerMessages::Response_receive & response_receive = response.receive();
			printf(
				"Receive:\n"
				"\tinput_bundle: %s",
				response_receive.input_bundle().c_str()
			);

		}else if(response.has_requeue()){
			const schedulerMessages::Response_requeue & response_requeue = response.requeue();
			printf(
				"Requeue:\n"
				"\trequeue_failed: %d",
				(int)response_requeue.requeue_failed()
			);

		}else if(response.has_finish()){
			const schedulerMessages::Response_finish & response_finish = response.finish();
			printf(
				"Finish"
			);
		}else if(response.has_cancel()){
			const schedulerMessages::Response_cancel & response_cancel = response.cancel();
			printf(
				"Cancel"
			);
		}else if(response.has_add_dependency()){
			const schedulerMessages::Response_add_dependency & response_add_dependency = response.add_dependency();
			printf(
				"Add Dependency"
			);
		}else{
			printf("subtype not recognized");
		}
		printf("\n");
	}else{
		printf("Neither request nor response\n");
	}

};
void Scheduler::Run(Scheduler & scheduler){
	while(true){
	    scheduler.Update();
	};
}
void Scheduler::HandleCmdLineInput(Scheduler & scheduler){
	std::string input;
	while(true){
	    std::cin >> input;
		if(input == "q"){
			finished = true;	
		}else if(input == "p"){
			//scheduler.pTasksTable_->PrintAll();
			JobManager::PrintAll();
		}else{
			printf("command line input '%s' is not a command. Input 'q' to close\n",input.c_str());
		}
	};
}