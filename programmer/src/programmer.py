#
#	CCore programmer
#
# copyright (c) 2018 djytw. All rights reserved.
#
import sys
import serial
import argparse

def main():
	args=getArgs();
	#connect serial
	print("Checking serial connection...",end='')
	try:
		t=serial.Serial(args.tty,115200,timeout=0)
	except Exception as e:
		print("Failed to open "+args.tty+"!")
		return
	print("ok")

	#connect chip
	print("Connecting to chip.",end='');
	for i in range(1,10):
		for j in range(1,10):
			t.write(b'p');
			r=t.read();
			if r==b'o':
	if(args.mode[0]=='w'):
		print("write mode.")
	elif(args.mode[0]=='b'):
		print("Starting application at ")
	else:
		print("Unknown mode - '"+args.mode+"', use ccprog -h to show help.")

def getArgs():
	parse=argparse.ArgumentParser(prog="ccprog",description='Serial programmer for ccore chips.',usage="ccprog [boot|write] [-f FILE] [-t TTY]")
	parse.add_argument('mode',help="Specify programmer work mode.",metavar="[boot|write]")
	parse.add_argument('-f','--file',help="Specify binary file in write mode.")
	parse.add_argument('-t','--tty',help="Specify serial used to connect the chip.",required=True)
	return parse.parse_args()

if __name__ == "__main__":
	main()