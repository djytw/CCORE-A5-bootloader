#
#	CCore programmer
#
# copyright (c) 2018 djytw. All rights reserved.
#
import sys
import serial
import argparse
import time
import hashlib
import shutil

def main():
	col=shutil.get_terminal_size().columns

	args=getArgs();
	#connect serial
	print("Checking serial connection...",end='')
	try:
		t=serial.Serial(args.tty,115200,timeout=0,write_timeout=0)
	except Exception as e:
		print("Failed to open "+args.tty+"!")
		return
	print("ok")

	#connect chip
	print("Connecting to chip.",end='');
	for i in range(10):
		print(".",end='')
		sys.stdout.flush()
		for j in range(20):
			t.write(b'p')
			t.flush()
			r=t.read(2000)
			l=len(r)
			if l>0 and r[l-1]==111:
				#seems connected
				t.write(b'i')
				t.flush()
				time.sleep(0.1)
				r=t.read(6)
				if r==b'CCBOOT':
					#connect ok
					print("ok")
					break
			time.sleep(0.05)
		else:
			continue
		break

	else:
		print("timeout")
		print("Failed to connect chip.")
		return;
	#connect ok
	if(args.mode[0]=='w'):
		try:
			f=open(args.file,'rb')
		except Exception as e:
			print("Failed to open file"+args.file+"!")
			return
		data=f.read();
		flen=len(data);
		sha256=hashlib.sha256()
		sha256.update(data);
		sha=sha256.hexdigest().upper();
		print("Open binary ok. File size =",flen,", sha256 =",sha)
		t.write(b'l')
		t.flush()
		tlen='{:x}'.format(flen).encode('utf-8')
		t.write(tlen);
		t.flush()
		if t.read(5) != b'o'+tlen:
			print("Set length error!")
			return;
		t.write(b'w')
		t.flush()
		#wait for erase flash
		time.sleep(0.1)
		print("Start downloading...")
		print("")
		t.write(data)
		outold=t.out_waiting;
		while t.out_waiting!=0:
			if outold!=t.out_waiting:
				dflen=(outold-t.out_waiting)/flen*100;
				for i in range(int(dflen)):
					print("#",end='')
				sys.stdout.flush()
				outold=t.out_waiting
		print("")
		print("write ok");
		#wait for program flash, calc, etc
		time.sleep(0.5)
		if t.read(65)!=b'o'+bytes(sha,encoding="utf-8"):
			print("Check error!")
			return;
		print("check ok! download success!")
		time.sleep(0.5)
		if(args.autoboot==True):
			print("Starting application at 0x00420000...")
			t.write(b'b')
		
	elif(args.mode[0]=='b'):
		print("Starting application at 0x00420000...")
		t.write(b'b')
	else:
		print("Unknown mode - '"+args.mode+"', use ccprog -h to show help.")
	return;

def getArgs():
	parse=argparse.ArgumentParser(prog="ccprog",description='Serial programmer for ccore chips.',usage="ccprog [boot|write] [-f FILE] [-t TTY]")
	parse.add_argument('mode',help="Specify programmer work mode.",metavar="[boot|write]")
	parse.add_argument('-f','--file',help="Specify binary file in write mode.")
	parse.add_argument('-a','--autoboot',help="Auto start application after program.", action='store_true')
	parse.add_argument('-t','--tty',help="Specify serial used to connect the chip.",required=True)
	return parse.parse_args()

if __name__ == "__main__":
	main()