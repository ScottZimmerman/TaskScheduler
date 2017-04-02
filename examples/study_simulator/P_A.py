#!/usr/bin/python
import sys
import os
import json
from query_scheduler import *
from numpy import mean
from helper import *

if(len(sys.argv) != 4):
	print 'Usage: P_A.py <host> <port> <input_bundle>'
	exit(1)

host = sys.argv[1]
port = sys.argv[2]
input_bundle = sys.argv[3]

input = getInstructions(input_bundle)
id = input["id"]

#Load S outputs
s_outputs = []
for s_id in input["S"]:
	s_output = getOutput(s_id)
	s_outputs.append(float(s_output["sq"]))

#Update the average using an online algorithm
if("P_A" in input.keys()):
	p_a_output = getOutput(input["P_A"])
	result = float(p_a_output["avg"])
	n = input["prev_N"]
	for s_value in s_outputs:
		n += 1
		result = result + (s_value - result)/n
		
else:
	result = mean(s_outputs)
	n = len(s_outputs)
#Create output
output = dict()
output["avg"] = result
output["prev_N"] = n

#Test stop condition: 
# keep going (by creating two more S tasks and a P_A task) if result < 200, and add a dependency for the CS_A task that depends upon this P_A to depend upon the new P_A
if(result < 200):
	#THIS IS ALL COPIED FROM P_C.py
	#TO DO: Put in standalone function "createPBlock"
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
	instructions["prev_N"] = n
	instructions["S"] = s_ids
	instructions["P_A"] = id
	saveInstructions(p_a_id,instructions)
	queryScheduler(host,port,"queue",[p_a_id,instructions["inputBundle"],id])


	output["P_A"] = p_a_id
	output["S"] = s_ids

#Write the output
saveOutput(id,output)