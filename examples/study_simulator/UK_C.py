#!/usr/bin/python
import sys
import os
import json
from query_scheduler import *
from helper import *

if(len(sys.argv) != 4):
	print 'Usage: UK_C.py <host> <port> <input_bundle>'
	exit(1)

host = sys.argv[1]
port = sys.argv[2]
input_bundle = sys.argv[3]

input = getInstructions(input_bundle)
id = input["id"]

#Assign one UK_A task and two CS_C tasks
uk_a_id = queryScheduler(host,port,"assign")
cs_c_ids = queryScheduler(host,port,"assign",["2"])

#Create dependencies of the UK_A task on the CS_C tasks
for cs_c_id in cs_c_ids:
	queryScheduler(host,port,"add_dependency",[cs_c_id, uk_a_id])

#Queue the CS_C tasks 
for cs_c_id in cs_c_ids:
	instructions = makeInstructions(cs_c_id,"CS_C")
	instructions["UK_A"] = uk_a_id
	saveInstructions(cs_c_id,instructions)
	queryScheduler(host,port,"queue",[cs_c_id, instructions["inputBundle"], id])

#Queue the UK_A task
instructions = makeInstructions(uk_a_id,"UK_A")
instructions["CS_C"] = cs_c_ids
saveInstructions(uk_a_id,instructions)
queryScheduler(host,port,"queue",[uk_a_id,instructions["inputBundle"],id])