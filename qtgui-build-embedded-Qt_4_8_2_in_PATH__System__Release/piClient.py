#!/usr/bin/python
import sys
from socket import *

HOST = 'minecraft365.chickenkiller.com'
PORT = 4321
s = socket(AF_INET, SOCK_STREAM)
s.connect((HOST, PORT))
s.send('SetWaterLevel' + sys.argv[1] + ':' + sys.argv[2])
s.close()

