import socket
import select
import os
import utils.Constant as myDefine
MSGLEN = 1026

class MySocket:
    def __init__(self, sock=None, teamName: str =myDefine.TEAMNAME ):
        self.teamName = teamName
        self.buff = b""
        self.sizeLeft = 0
        self.mapSize = {'x' : 0, 'y' : -1}
        self.socket_queu: list[str] = []
        self.error = False
        if sock is None:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.sock = sock

    def connect(self, host = myDefine.HOST, port = myDefine.PORT):
        try : 
            self.sock.connect((host, port))
        except:
            print("CONNECTION ERROR")
        self.sock.setblocking(False)

        nbCheckelem = 0
        while (self.mapSize['y'] == -1):
            got = str(self.myreceive(1))[2:-1]
            res = list(filter(lambda x: x != '', got.split("\\n")))
            for elem in res:
                if (nbCheckelem == 0):
                    self.mysend(self.teamName)
                if (nbCheckelem == 1):
                    if (elem == 'ko'):
                        self.error = True
                        return
                    self.sizeLeft = int(elem)
                if (nbCheckelem == 2):
                    splitedElem = elem.split(" ")
                    self.mapSize['x'] = int(splitedElem[0])
                    self.mapSize['y'] = int(splitedElem[1])
                nbCheckelem += 1
        self.extract_call()

    def is_elem_in_queu(self) -> bool:
        self.is_Connected()
        return bool(len(self.socket_queu) and not self.error)

    def get_queu_size(self) -> int:
        self.is_Connected()
        return len(self.socket_queu)

    def mysend(self, msg) -> None:
        self.is_Connected()
        try:
            self.socket_queu.append(msg)
            arr = bytes(msg + "\n", 'ascii')
            self.sock.sendall(arr)
        except:
            self.error = True

    def myLogOut(self) -> None:
        self.sock.close()
        print("socket is disconnected")
        os._exit(1)

    def should_remove(self, elem:str) -> None:
        self.is_Connected()
        if (elem in self.socket_queu):
            self.socket_queu.remove(elem)

    def extract_call(self) -> str:
        self.is_Connected()
        return self.socket_queu.pop(0)

    def is_Connected(self) -> bool:
        try:
            self.sock.getpeername()
            return not self.error
        except (socket.error, OSError):
            self.myLogOut()

    def myreceive(self, timeout = 0.05)-> str:
        self.is_Connected()
        try:
            ret = bytes("", 'utf-8')
            ready_to_read, _, _ = select.select([self.sock], [], [], timeout)
            if self.sock in ready_to_read:
                recv = self.sock.recv(2048)
                if (len(recv) == 0):
                    self.myLogOut()
                self.buff = self.buff + recv
            decoded_buff = self.buff.decode("utf-8")
            while '\n' in decoded_buff:
                newline_index = decoded_buff.index('\n') + 1
                ret += self.buff[:newline_index]
                self.buff = self.buff[newline_index:]
                decoded_buff = self.buff.decode("utf-8")
            return ret
        except :
            self.error = True
            self.myLogOut()

        