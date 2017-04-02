#!/usr/bin/python

import os
import subprocess


def parseOutput(command,text):
	textList = text.split("\n")
	if(command == "assign"):
		if(textList[0] == "id"):
			result = textList[1]
		elif(textList[0] == "ids"):
			result = textList[1].split(",")
		return(result)
	elif(command == "queue"):
		pass
	elif(command == "receive"):
		if(len(textList)==2):
			input_bundle = textList[1]
		else:
			input_bundle = None
		return(input_bundle)
	elif(command == "requeue"):
		requeue_failed = textList[1]
		return(requeue_failed)
	elif(command == "finish"):
		pass
	elif(command == "cancel"):
		pass
	elif(command == "add_dependency"):
		pass
	else:
		print "Unknown command '"+command+"'"

def queryScheduler(host,port,command,args=[]):
	callList = [os.path.join(".",os.getcwd(),"..","..","build","client"),host,port,command]+args
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
		result = parseOutput(command,res[0])
		return(result)