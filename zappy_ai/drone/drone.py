from my_socket.socket import MySocket
from copy import copy
import re
import os
import random
import utils.Constant as myDefine
import brain.shared_cells as instinct
from drone.IDrone import IDrone
from utils.enum import Mutation
from brain.INeuron import INeuron
from trantor_handler.handler_broadcast import BroadCast
import numpy as np
import random
import string

Ressources = {
  "food"     : 10,
  "linemate" : 0,
  "deraumere": 0,
  "sibur"    : 0,
  "mendiane" : 0,
  "phiras"   : 0,
  "thystame" : 0,
}
Protocol_Handler = {
    "Forward": "",
    "Right": "",
    "Left": "",
    "Look": "__Update_Fov__",
    "Inventory": "__Update_Inv__",
    "Broadcast": "",
    "Connect_nbr": "__Update_Nb_Egg__",
    "Fork": "",
    "Eject": "",
    "Take": "__Add_Elem__",
    "Set": "__Sub_Elem__",
    "Incantation": "__Update_Level__",
}
locking_fct = ["Look", "Inventory", "Connect_nbr", "Eject", "Take", "Set", "Incantation"]

class Drone(IDrone):
    def __init__(self) -> None:
        super().__init__()
        self.instinctFct = instinct.Instinct()
        self.isStarving = False
        self.lead = False
        self.broadcast = BroadCast()
        self.alive = True
        self.prevcall  = ["",""]
        self.teamName = myDefine.TEAMNAME
        self.port = myDefine.PORT
        self.host = myDefine.HOST
        self.level = 1
        self.id = random.randint(0, 999)
        self.freeSlot = 0
        self.mutation: Mutation = Mutation.NONE
        self.brain: INeuron = INeuron()
        self.inventory = Ressources
        self.fov = []
        self.key = ""
        self.socket = MySocket(None, myDefine.TEAMNAME)
        self.baseReady = False
        self.socket.connect(myDefine.HOST,myDefine.PORT )
        self.__Init_BroadcastKey__()
        self.__Reset_Fov__()
    
    def Forward(self) -> None:
        msg = "Forward"
        self.socket.mysend(msg)
        # print(msg)
    
    def Right(self) -> None:
        msg = "Right"
        self.socket.mysend(msg)
        # print(msg)
    
    def Left(self) -> None:
        msg = "Left"
        self.socket.mysend(msg)
        # print(msg)
    
    def Look(self) -> None:
        msg = "Look"
        self.socket.mysend(msg)
        # print(msg)

    def Inventory(self) -> None:
        msg = "Inventory"
        self.socket.mysend(msg)
        # print(msg)

    def Broadcast(self, text : str) -> None:
        msg = "Broadcast " + text
        self.socket.mysend(msg + self.key)
        # print(msg)

    def Connect_nbr(self) -> None:
        msg = "Connect_nbr"
        self.socket.mysend(msg)
        # print(msg)

    def Fork(self) -> None:
        msg = "Fork"
        self.socket.mysend(msg)
        # print(msg)

    def Eject(self) -> None:
        msg = "Eject"
        self.socket.mysend(msg)
        # print(msg)

    def Take(self, text: str) -> None:
        msg = "Take " + text
        self.socket.mysend(msg)
        # print(msg)

    def Set(self, text: str) -> None:
        msg = "Set " + text
        self.socket.mysend(msg)
        # print(msg)

    def Incantation(self) -> None:
        msg = "Incantation"
        self.socket.mysend(msg)
        # print(msg)

    def Think(self) -> None:
        if (not self.instinctFct.isBrainReady):
            self.instinctFct.assign_brain(self)
        self.instinctFct.handle_instinct(self)
        self.brain.use_neuron(self)

    def __Reset_Fov__(self) -> None:
        Entity = {
            "food"     : 0,
            "player"   : 0,
            "linemate" : 0,
            "deraumere": 0,
            "sibur"    : 0,
            "mendiane" : 0,
            "phiras"   : 0,
            "thystame" : 0,
        }
        emptyPlace = [Entity]
        emptySound = []
        Fov = copy([emptyPlace])
        for i in range(0,9):
            emptySound.append(copy([]))
            test = []
            for _ in range((i * 2) + 3):
                test.append(copy(Entity))
            Fov.append(test)
        self.fov = Fov
    
    def __Init_BroadcastKey__(self):
        to_bytes = lambda x : np.array(list(x)).view(np.int32) 
        encr = to_bytes(myDefine.TEAMNAME) | to_bytes(myDefine.CRYPTED)
        to_str = lambda x: "".join(x.view('<U1'))
        self.key = to_str(encr)
        ascii_chars = set(string.printable)
        self.key = ''.join(filter(lambda x: x in ascii_chars, self.key))

    def __Update_Fov__(self, str: str) -> None:
        cleanedString = str[1:-1].strip()
        splitedParams = re.split(', |,', cleanedString)
        col = 0
        row = 0
        range = 0
        self.__Reset_Fov__()

        for param in splitedParams:
            if row >= ((range * 2) + 3):
                row = 0
                col += 1
                range += 1
            elem =  param.split(" ")
            for item in elem:
                if (len(item) > 0):
                    self.fov[col][row][item] += 1
            if col == 0:
                col += 1
                continue
            row += 1

    def __Update_Inv__(self, str: str) -> None:
        cleanedString = str[2:-2]
        splitedParams = re.split(', |,', cleanedString)

        for param in splitedParams:
            elem = param.split(" ")
            if (len(elem) < 2):
                continue
            self.inventory[elem[0]] = int(elem[1])     

    def __Add_Elem__(self, elem:str)-> None:
            self.inventory[elem] += 1

    def __Sub_Elem__(self, elem:str)-> None:
            self.inventory[elem] -= 1

    def __Update_Nb_Egg__(self, str: str) -> None:
        value: int = int(str)
        self.freeSlot = value

    def __Update_Level__(self, input: str) -> None:
        if (input.split()[0] == "Elevation"):
            return
        value: int = int(input)
        self.level = value
        #print("level updated " + str(value))

    def __Update_Id__(self, str: str) -> None:
        value: int = int(str)
        self.id = value

    def __Update_Team_Name__(self, str: str) -> None:
        self.teamName = str

    def __Die__(self) -> None:
        self.socket.myLogOut()
        print("player dead")
        os._exit(1)

    def __Get_Last_Response__(self) -> str:
        res = self.socket.myreceive()
        # print("fetched serv")
        if (len(res) > 0):
            res = str(res)[2:-3]
        else:
            res = ""
        return res

    def __Update_Broadcast__(self,pos:int,  msg:str) -> str:
        if (len(msg) < len(self.key)):
            return ""
        key = msg[len(msg) - len(self.key):]
        ret = msg[:len(msg) - len(self.key)]
        if (key != self.key):
            self.broadcast.enemyBroadcast[pos].append(ret)
            return ""

        self.broadcast.broadcast[pos].append(ret)
        return ""

    def __Launch_Methode__(self, methods:str, args ="ok") -> None:
        fullMethod = methods.split(" ")
        method = fullMethod[0]
        if (len(fullMethod) > 1):
            args = fullMethod[1]
        if (args == "ko"):
            return
        if (methods == "NONE"):
            return
        if (not hasattr(self, method)):
            print(method)
            print("Bad Method call")
            return 
        if (args == "ok"):
            getattr(self, method)()
        else:
            getattr(self, method)(args)

    def __Exec_Calls__(self,res : list[str]) -> None:
        for elem in res:
            splitedMessage = elem.split(" ")

            if (self.prevcall[0] == "Incantation" and self.prevcall[1] == "ko" and elem == "ko"):
                #print(self.id , " say : ", "incantate ko") 
                self.socket.should_remove("Incantation")
                continue

            if (elem.split()[0] == "eject:"):
                continue

            if (elem.split()[0] == "Elevation"):
                #print(self.id , " say : ", "start level up") 
                self.socket.should_remove("Incantation")
                continue

            if (splitedMessage[0] == "Current"):
                self.__Update_Level__(splitedMessage[2])
                self.socket.should_remove("Incantation")
                continue

            if (splitedMessage[0] == "message"):
                self.__Update_Broadcast__(int(splitedMessage[1][:-1]), splitedMessage[2])
                continue

            if (elem == "dead"):
                self.alive = False
                break

            fullCall = self.socket.extract_call().split(" ")
            call = fullCall[0]
            if (len(fullCall) > 1 and elem == "ok"):
                elem = fullCall[1]
            #print(self.id , " say : ", "send --->", call, " | got ---> ",  elem) 
            handler = Protocol_Handler[call.split(" ")[0]]
            self.prevcall = [call, elem]
            if (len(handler)):
                self.__Launch_Methode__(handler, elem)

    def __Flush_Calls__(self):
        while (self.socket.is_elem_in_queu()):
            res = list(filter(lambda x: x != '', self.__Get_Last_Response__().split("\\n")))
            self.__Exec_Calls__(res)

    def Play(self, call:str = "NONE") -> None:
        if (self.socket.get_queu_size() >= 9):
            self.__Flush_Calls__()
        self.__Launch_Methode__(call)
        locking = False
        if (call.split(" ")[0] in locking_fct):
            locking = True
        if (locking == False):
            res = list(filter(lambda x: x != '', self.__Get_Last_Response__().split("\\n")))
            if (len(res) > 0 and res[0] == "dead"):
                self.alive = False
            self.__Exec_Calls__(res)
        if (locking == True):
            self.__Flush_Calls__()
        if (not self.socket.is_Connected()):
            self.alive = False
        if (not self.alive):
            self.__Die__()
        

