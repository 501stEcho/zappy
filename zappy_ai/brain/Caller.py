from drone.IDrone import IDrone
from utils.Constant import *
from brain.INeuron import INeuron

class Caller(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.breadcum = [0,0,0]
        self.isPlaced = False

    def use_neuron(self, trantor: IDrone):
        trantor.Play(CALLCALL)
        trantor.Play("Fork")
