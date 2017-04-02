#!/usr/bin/python
import sys
import os
import json
from query_scheduler import *
from helper import *

if(len(sys.argv) != 4):
	print 'Usage: UK_A.py <host> <port> <input_bundle>'
	exit(1)

host = sys.argv[1]
port = sys.argv[2]
input_bundle = sys.argv[3]

input = getInstructions(input_bundle)
id = input["id"]

#Load outputs of CS_C tasks
cs_c_outputs = []
for cs_c_id in input["CS_C"]:
	cs_c_outputs.append(getOutput(cs_c_id))

#Get all of the final CS_A tasks
cs_a_outputs = []
for cs_c_o in cs_c_outputs:
	d = getOutput(cs_c_o["CS_A"])
	cs_a_outputs.append(d)

#Calculate the sum of all the final p_a values:
final_result = 0
for cs_a_o in cs_a_outputs:
	final_result += cs_a_o["sum"]

#Save the output
output = dict()
output["final"] = final_result
saveOutput(id,output)