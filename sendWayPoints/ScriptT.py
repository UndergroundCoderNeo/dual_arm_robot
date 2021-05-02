import time
import socket


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
def check_status():
	counter=0
	while(counter<1):
		msg=sk.recv(1000)
		msg=msg.decode()
		print(msg)
		counter=counter+msg.count("Script finish")
		#print(counter)
	#print("motion done")	

def main():
	init_socket()	
	cmd="<start>LP/ movej_pose([-162,620,1200,78,51,90],40,20,-1);movej_pose([-900,700,1250,90,0,167],40,20,-1);movej([-0,-0,-0,-90,0,-0,0],30,2000,-1); /RP/movej_pose([313,620,1200,90,40,-95],40,20,-1);movej_pose([900,700,1250,90,0,167],40,20,-1);movej([0,-0,0,90,-0,-0,0],30,2000,-1);<end>"
	print(cmd)
	sk.send(cmd.encode())
	check_status()
				

if __name__=='__main__':
	main()
