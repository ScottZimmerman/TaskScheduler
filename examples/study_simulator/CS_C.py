#!/usr/bin/python
import sys
import os
import json
from query_scheduler import *
from helper import *

if(len(sys.argv) != 4):
	print 'Usage: CS_C.py <host> <port> <input_bundle>'
	exit(1)

host = sys.argv[1]
port = sys.argv[2]
input_bundle = sys.argv[3]

input = getInstructions(input_bundle)
id = input["id"]

#Assign one CS_A task and two P_C tasks
cs_a_id = queryScheduler(host,port,"assign")
p_c_ids = queryScheduler(host,port,"assign",["2"])

#Create dependencies:
#	The CS_A task depends upon each P_C task
for p_c_id in p_c_ids:
	queryScheduler(host,port,"add_dependency",[p_c_id,cs_a_id])

#	The UK_A task launched by this task's parent (UK_C) needs to depend on the new CS_A	
queryScheduler(host,port,"add_dependency",[cs_a_id,input["UK_A"]])

#Queue the tasks
for p_c_id in p_c_ids:
	instructions = makeInstructions(p_c_id,"P_C")
	instructions["CS_A"] = cs_a_id
	saveInstructions(p_c_id,instructions)
	queryScheduler(host,port,"queue",[p_c_id,instructions["inputBundle"],id])

instructions = makeInstructions(cs_a_id,"CS_A")
instructions["P_C"] = p_c_ids
saveInstructions(cs_a_id,instructions)
queryScheduler(host,port,"queue",[cs_a_id,instructions["inputBundle"],id])

#Output the newly created IDs
output = dict()
output["P_C"] = p_c_ids
output["CS_A"] = cs_a_id
saveOutput(id,output)