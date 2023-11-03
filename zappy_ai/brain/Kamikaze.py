from drone.IDrone import IDrone
from utils.Constant import *
from brain.INeuron import INeuron

class Kamikaze(INeuron):
    def __init__(self) -> None:
        super().__init__()

    def use_neuron(self, trantor: IDrone):
        trantor.Play("Inventory")
        while (trantor.inventory['food'] > 0):
            trantor.Play("Set food")
        trantor.Play("Forward")
        trantor.Play("Forward")
        trantor.Play("Forward")
        trantor.Play("Forward")
        trantor.__Die__()
