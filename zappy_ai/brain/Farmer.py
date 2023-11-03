from drone.IDrone import IDrone
from utils.Constant import *
from brain.INeuron import INeuron

class Farmer(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.breadcum = [0,0,0]
        self.isPlaced = False
        self.nbCrossLine = 0

    def set_all_Food(self, trantor: IDrone):
        trantor.Play("Inventory")
        idx = 0
        while (trantor.inventory['food'] > NEEDEDFOOD):
            idx += 1
            if (idx >= 20):
                idx = 0
                trantor.Play("Inventory")
            trantor.Play("Set food")

    def use_neuron(self, trantor: IDrone):
        trantor.Play("Forward")
        trantor.Play("Forward")
        trantor.Play("Right")
        while (self.nbCrossLine< 4):
            for _ in range(0, 3):
                self.take_elem_on_front_row(trantor, "food")
            self.turn_back(trantor)
            trantor.Play("Forward")
            trantor.Play("Right")
            for _ in range(0, 2):
                self.take_elem_on_front_row(trantor, "food")
            self.nbCrossLine += 1
        self.nbCrossLine = 0
        trantor.Play("Right")
        trantor.Play("Forward")
        trantor.Play("Forward")
        self.turn_back(trantor)
        self.set_all_Food(trantor)
