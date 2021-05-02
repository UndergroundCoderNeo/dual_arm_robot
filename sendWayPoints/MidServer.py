import socket  # 导入 socket 模块
from threading import Thread

ADDRESS = ('127.0.0.1', 7000)  # 绑定地址
 
g_socket_server = None  # 负责监听的socket
 
g_conn_pool = []  # 连接池
def init():
    """
    初始化服务端
    """
    global g_socket_server
    g_socket_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建 socket 对象
    g_socket_server.bind(ADDRESS)
    g_socket_server.listen(5)  # 最大等待数（有很多人理解为最大连接数，其实是错误的）
    print("服务端已启动，等待客户端连接...")
def accept_client():
    """
    接收新连接
    """
    while True:
        client, _ = g_socket_server.accept()  # 阻塞，等待客户端连接
        # 加入连接池
        g_conn_pool.append(client)
        # 给每个客户端创建一个独立的线程进行管理
        thread = Thread(target=message_handle, args=(client,))
        # 设置成守护线程
        thread.setDaemon(True)
        thread.start()
 
 
def message_handle(client):
    """
    消息处理
    """
    client.sendall("连接服务器成功!".encode(encoding='utf8'))
    while True:
        bytes = client.recv(10000)
        print( bytes.decode(encoding='utf8'))

def accept_client():
    """
    接收新连接
    """
    while True:
        client, _ = g_socket_server.accept()  # 阻塞，等待客户端连接
        # 加入连接池
        g_conn_pool.append(client)
        # 给每个客户端创建一个独立的线程进行管理
        thread = Thread(target=message_handle, args=(client,))
        # 设置成守护线程
        thread.setDaemon(True)
        thread.start()
 


def message_handle(client):
    while True:
        msg=client.recv(10000)
        msg=msg.decode()
        global send_robot
        send_robot=send_robot+msg
        if msg.find("<end>")!=-1:
             print("length of sending msg:")
             print(send_robot)
             with open('wayPoints.txt','w') as f:
                 f.write(send_robot)
                 f.close()
            #  robot_ip=("192.168.1.50",2000)
            #  sk=socket.socket()
            #  sk.connect(robot_ip)
            #  sk.send(send_robot.encode('utf'))
        #      while True:
        #           sk.send(send_robot.encode('utf'))
        #           msg=sk.recv(1000)
        #           msg=msg.decode()
        #           if msg.find("Prog")!=-1:
        #                break
        #      send_robot=""
        #      sk.close()

if __name__ == '__main__':
    init()
    # 新开一个线程，用于接收新连接
    thread = Thread(target=accept_client)
    thread.setDaemon(True)
    thread.start()
    send_robot=""
    # 主线程逻辑
    while True:
        cmd = input("""--------------------------
输入1:查看当前在线人数
输入2:给指定客户端发送消息
输入3:关闭服务端
""")
        if cmd == '1':
            print("--------------------------")
            print("当前在线人数：", len(g_conn_pool))
        elif cmd == '2':
            print("--------------------------")
            index, msg = input("请输入“索引,消息”的形式：").split(",")
            g_conn_pool[int(index)].sendall(msg.encode(encoding='utf8'))
        elif cmd == '3':
            exit()
