#!/usr/bin/python
import sys
import os
import json
from query_scheduler import *
from math import pow
from helper import *
from time import sleep

if(len(sys.argv) != 4):
	print 'Usage: S.py <host> <port> <input_bundle>'
	exit(1)

host = sys.argv[1]
port = sys.argv[2]
input_bundle = sys.argv[3]

input = getInstructions(input_bundle)
id = input["id"]

output = dict()
output["sq"] = pow(int(id),2)
saveOutput(id,output)

sleep(2)