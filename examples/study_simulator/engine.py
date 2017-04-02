#!/usr/bin/python

import sys
import time
import os
import subprocess
import json
from query_scheduler import *

if(len(sys.argv) != 5):
	print 'Usage: engine.py <host> <port> <engineID> <newJob>'
	exit(1)

print 'Arguments:', str(sys.argv)
host = sys.argv[1]
port = sys.argv[2]
engineID = sys.argv[3]
newJob = sys.argv[4]

def loadInputBundle(input_bundle):
	with open(os.path.join(os.getcwd(),"input",input_bundle),"r") as f:
		input = json.load(f)
		return(input)

def runTaskScript(input_bundle):
	print "running",input_bundle
	input = loadInputBundle(input_bundle)
	callList = ["python",os.path.join(os.getcwd(),input["type"]+".py"),host,port,input_bundle]
	p = subprocess.Popen(callList, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
	p.wait()
	res = p.communicate()	
	if p.returncode != 0:
		print("-----------------------")
		print("RETURN CODE WAS NONZERO")
		print("STDOUT")
		print(res[0])
		print("STDERR")
		print(res[1])
		print("RETURNCODE:")
		print(p.returncode)
		raise Exception("nonzero return code")
		print("-----------------------")
	else:
		print(res[0])
		queryScheduler(host,port,"finish",[input["id"]])

if(newJob == "1"):
	print("Starting new job")
	id = queryScheduler(host,port,"assign")
	instructions = dict()
	instructions["id"] = id
	instructions["type"] = "UK_C"
	instructionsFile = id+".json"
	
	with open(os.path.join(os.getcwd(),"input",instructionsFile),"w") as f:
		f.write(json.dumps(instructions))

	queryScheduler(host,port,"queue",[id, instructionsFile, "-1"])

while(1):
	input_bundle = queryScheduler(host,port,"receive",[engineID])
	print(input_bundle)
	if(len(input_bundle)):
		runTaskScript(input_bundle)
	else:
		time.sleep(1)
	sys.stdout.flush()