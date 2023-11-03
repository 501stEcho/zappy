from drone.IDrone import IDrone
from utils.Constant import *
from brain.INeuron import INeuron

class Soldier(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.breadcum = [0,0,0]
        self.isPlaced = False

    def set_up_pos(self, trantor: IDrone):
        trantor.Play("Look")
        while (trantor.fov[1][1]['player'] != 0):
            trantor.Play('Right')
        trantor.Play("Forward")
        self.turn_back(trantor)

    def use_neuron(self, trantor: IDrone):
        if (not self.isPlaced):
            self.set_up_pos(trantor)
            self.isPlaced = True
        trantor.Play("Eject")
