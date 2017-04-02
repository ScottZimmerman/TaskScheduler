import json
import os
def makeInstructions(id,type):
	instructions = dict()
	instructions["id"] = id
	instructions["type"] = type
	instructions["inputBundle"] = id + ".json"
	return(instructions)

def saveInstructions(id, instructions):
	with open(os.path.join(os.getcwd(),"input",instructions["inputBundle"]),"w") as f:
		f.write(json.dumps(instructions))

def saveOutput(id, output):
	with open(os.path.join(os.getcwd(),"output",id + ".json"),"w") as f:
		f.write(json.dumps(output))

def getInstructions(input_bundle):
	with open(os.path.join(os.getcwd(),"input",input_bundle),"r") as f:
		result = json.load(f)
	return(result)

def getOutput(id):
	with open(os.path.join(os.getcwd(),"output",id + ".json"),"r") as f:
		result = json.load(f)
	return(result)