from drone.IDrone import IDrone
from utils.Constant import *
from brain.INeuron import INeuron
import random
class Parrot(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.breadcum = [0,0,0]
        self.isPlaced = False

    def random_dir(self):
        dirs = ["Forward", "Left", "Right"]
        dirIdx = random.randint(0, 2)
        return dirs[dirIdx]

    def use_neuron(self, trantor: IDrone):
        chosenDir = self.random_dir()
        call = trantor.broadcast.extract_enemy_call()
        trantor.Play(chosenDir)
        trantor.Play("Broadcast " + call)