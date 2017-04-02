#!/usr/bin/python
import sys
import os
import json
from query_scheduler import *
from helper import *

if(len(sys.argv) != 4):
	print 'Usage: CS_A.py <host> <port> <input_bundle>'
	exit(1)

host = sys.argv[1]
port = sys.argv[2]
input_bundle = sys.argv[3]

input = getInstructions(input_bundle)
id = input["id"]

#Load outputs of P_C tasks
p_c_outputs = []
for p_c_id in input["P_C"]:
	p_c_outputs.append(getOutput(p_c_id))

#Get all of the final P_A tasks
p_a_outputs = []
for p_c_o in p_c_outputs:
	final = 0
	d = p_c_o
	while("P_A" in d.keys()):
		p_a = d["P_A"]
		d = getOutput(d["P_A"])
	p_a_outputs.append(d)

#Calculate the sum of all the final p_a values:
sum_p_a = 0
for p_a_o in p_a_outputs:
	sum_p_a += p_a_o["avg"]

#Save the output
output = dict()
output["sum"] = sum_p_a
saveOutput(id,output)