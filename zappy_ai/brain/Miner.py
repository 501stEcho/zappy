from drone.IDrone import IDrone
from utils.Constant import *
from brain.INeuron import INeuron

class Miner(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.breadcum = [0,0,0]
        self.isPlaced = False
        self.nbCrossLine = 0

    def set_all_Rock(self, trantor: IDrone):
        trantor.Play("Inventory")
        item = trantor.inventory
        for attr, value in item.items():
            if (attr == "food"):
                continue
            while (trantor.inventory[attr] > 0):
                trantor.Play("Set " + attr)

    def prepare_food(self, trantor : IDrone):
        trantor.Play("Inventory")
        trantor.Play("Look")
        taken = 0
        while (trantor.inventory['food'] < NEEDEDFOOD and trantor.fov[0][0]['food']  - taken > 0):
            trantor.Play("Take Food")
            taken += 1

    def use_neuron(self, trantor: IDrone):
        self.prepare_food(trantor)
        trantor.Play("Forward")
        trantor.Play("Forward")
        trantor.Play("Right")
        while (self.nbCrossLine< 4):
            for _ in range(0, 3):
                self.take_rock_on_front_row(trantor)
            self.turn_back(trantor)
            trantor.Play("Forward")
            trantor.Play("Right")
            for _ in range(0, 2):
                self.take_rock_on_front_row(trantor)
            self.nbCrossLine += 1
        self.nbCrossLine = 0
        trantor.Play("Right")
        trantor.Play("Forward")
        trantor.Play("Forward")
        self.turn_back(trantor)
        self.set_all_Rock(trantor)
