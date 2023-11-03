from drone.IDrone import IDrone
from utils.enum import *
from utils.Constant import *
from brain.INeuron import INeuron
import trantor_handler.handler_trantor as th
class China(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.breadcum = [0,0,0]
        self.isPlaced = False
        self.mutationOrderId = 0
        self.nbCrossLine = 0

    def get_roles(self) -> str:
        return "KAMIKAZE"

    def use_neuron(self, trantor: IDrone):
        for _ in range(0,min(trantor.freeSlot, 10)):
            th.create_trantor(trantor.port, trantor.host, trantor.teamName)
        trantor.Play("Fork")