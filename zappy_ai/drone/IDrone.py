from my_socket.socket import MySocket
from utils.enum import Mutation
from brain.INeuron import INeuron
from trantor_handler.handler_broadcast import BroadCast
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
mooving_fct = ["Left", "Right", "Forward"]

class IDrone():
    def __init__(self) -> None:
        self.broadcast = BroadCast()
        self.alive = True
        self.teamName = ""
        self.level = 1
        self.isStarving = False
        self.brain : INeuron= INeuron()
        self.id = 0
        self.freeSlot = 0
        self.mutation: Mutation = 0
        self.inventory = []
        self.fov = []
        self.socket: MySocket
        self.baseReady = False

    def Forward(self) -> None:
        pass
    def Right(self) -> None:
        pass
    def Left(self) -> None:
        pass
    def Look(self) -> None:
        pass
    def Inventory(self) -> None:
        pass
    def Broadcast(self, text : str) -> None:
        pass
    def Connect_nbr(self) -> None:
        pass
    def Fork(self) -> None:
        pass
    def Eject(self) -> None:
        pass
    def Take(self, text: str) -> None:
        pass
    def Set(self, text: str) -> None:
        pass
    def Incantation(self) -> None:
        pass
    def Think(self) -> None:
        pass
    def __Reset_Fov__(self) -> None:
        pass
    def __Update_Fov__(self, str: str) -> None:
        pass
    def __Update_Inv__(self, str: str) -> None:
        pass
    def __Add_Elem__(self, elem:str)-> None:
        pass
    def __Sub_Elem__(self, elem:str)-> None:
        pass
    def __Update_Nb_Egg__(self, str: str) -> None:
        pass
    def __Update_Level__(self, str: str) -> None:
        pass
    def __Update_Id__(self, str: str) -> None:
        pass
    def __Update_Team_Name__(self, str: str) -> None:
        pass
    def __Die__(self) -> None:
        pass
    def __Get_Last_Response__(self) -> str:
        pass
    def __Update_Broadcast__(self,pos:int,  msg:str) -> str:
        pass
    def __Launch_Methode__(self, methods:str, args ="ok") -> None:
        pass
    def __Exec_Calls__(self,res : list[str]) -> None:
        pass
    def __Flush_Calls__(self):
        pass
    def Play(self, call:str = "NONE") -> None:
        pass
        

