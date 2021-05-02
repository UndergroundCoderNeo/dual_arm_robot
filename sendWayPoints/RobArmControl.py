import time
import socket
import string

class Position:
	def __init__(self,x,y,z):
		self.x=x
		self.y=y
		self.z=z

class PosePo(Position):
	def __init__(self,x,y,z):
		super().__init__(self,x,y,z,Rx,Ry,RZ)
		self.Rx=Rx
		self.Ry=Ry
		self.Rz=Rz
	
	
def init_socket():
	#send cmd to the dual-arm robot
	debug_local=0
	if debug_local==1:
		target_ip1=("127.0.0.1",7000)
	else :
		target_ip1=("192.168.1.50",2000)
	#create socket target
	global sk
	sk = socket.socket()
	sk.connect(target_ip1)

def remove_np(s):
	return ''.join( c for c in s if c  in string.printable)

def check_status():
	while True:
		msg=sk.recv(1000)
		msg=msg.decode()
		print(msg)
		if msg.find("finish")!=-1:
			try:
				target_ip_tool=("192.168.0.10",7000)
				tsk=socket.socket()
				tsk.connect(target_ip_tool)
				cmd="executeC"	
				tsk.send(cmd.encode())	
			except:
				print("cannot connect pi")
			finally:
				print(cmd)			
				break
	return True		
	
		#print(counter)
	#print("motion done")	

def main():
	#define motion for robot	
	try:
		init_socket()
	except:
		print("fail to connect robot")
	with open("wayPoints.txt",'r') as f:	
		script1=f.read()
		script1=remove_np(script1)
		f.close() 		
	sk.send(script1.encode())
	status=check_status()
	#rotate cup and place
	script2="<start>LP/ movej_pose([-340,640,1040,78,51,90],40,20-1); sync_flag(1);movej_pose([-162,670,1220,131,24,107],40,20,-1); sync_flag(2);movej_pose([-300,620,870,78,51,90],40,20,-1);/RP/ movej_pose([313,620,1017,90,40,-95],40,20,-1);sync_flag(1);sync_flag(2); movej_pose([400,620,870,90,40,-95],40,20,-1);<end>"
	#back home
	script3="<start>LP/ sleep(6000);movej_pose([-162,620,1200,78,51,90],40,20,-1);movej_pose([-900,700,1250,90,0,167],40,20,-1);movej([-0,-0,-0,-90,0,-0,0],30,2000,-1); /RP/sleep(6000);movej_pose([313,620,1200,90,40,-95],40,20,-1);movej_pose([900,700,1250,90,0,167],40,20,-1);movej([0,-0,0,90,-0,-0,0],30,2000,-1);<end>"
	if status:
		sk.send(script2.encode())
		while True:		
			flag=sk.recv(1000)
			flag=flag.decode()
			print(flag)
			if flag.find("finish")!=-1:
				sk.send(script3.encode())
				try:
					target_ip_tool=("192.168.0.10",7000)
					tsk=socket.socket()
					tsk.connect(target_ip_tool)
					cmd="executeO"
					tsk.send(cmd.encode())	
				except:
					print("fail to connect pi")				
				finally:
					break

if __name__=='__main__':
	main()
