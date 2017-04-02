#!/usr/bin/python
import sys
import os
import json
from query_scheduler import *
from helper import *

if(len(sys.argv) != 4):
	print 'Usage: P_C.py <host> <port> <input_bundle>'
	exit(1)

host = sys.argv[1]
port = sys.argv[2]
input_bundle = sys.argv[3]

input = getInstructions(input_bundle)
id = input["id"]

# Assign one P_A task and two S tasks
p_a_id = queryScheduler(host,port,"assign")
s_ids = queryScheduler(host,port,"assign",["2"])

# Create dependencies
#	The P_A task depends on each of the S tasks
for s_id in s_ids:
	queryScheduler(host,port,"add_dependency",[s_id, p_a_id])

# 	The CS_A task queued by this task's parent (CS_C) needs to depend on the new P_A task
queryScheduler(host,port,"add_dependency",[p_a_id, input["CS_A"]])

#Queue the S tasks 
for s_id in s_ids:
	instructions = makeInstructions(s_id,"S")
	saveInstructions(s_id,instructions)
	queryScheduler(host,port,"queue",[s_id, instructions["inputBundle"], id])

#Queue the P_A task
instructions = makeInstructions(p_a_id,"P_A")
instructions["prev_N"] = 0
instructions["S"] = s_ids
instructions["CS_A"] = input["CS_A"]
saveInstructions(p_a_id,instructions)
queryScheduler(host,port,"queue",[p_a_id,instructions["inputBundle"],id])

#Output the newly created IDs
output = dict()
output["P_A"] = p_a_id
output["S"] = s_ids
saveOutput(id,output)