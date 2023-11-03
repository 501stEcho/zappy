from drone.IDrone import IDrone
from utils.Constant import *
from brain.INeuron import INeuron

class Winner(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.isPlaced = False
        self.nbCrossLine = 0
        self.isReady = False
        self.nbReady = 0

    def can_level_up(self, trantor: IDrone) -> bool:
        itemList = trantor.fov[0][0]
        neededItem = RessourcesLevel[trantor.level]
        if (trantor.fov[0][0]['player'] < 7):
            return False
        for attr, value in neededItem.items():
            if (itemList[attr] < neededItem[attr]):
                return False
        return True

    def use_neuron(self, trantor: IDrone):
        trantor.Play("Inventory")
        trantor.Play("Look")

        if (trantor.inventory['food'] < (NEEDEDWINNERFOOD * 2.5)):
            trantor.Play("Take food")
            return

        if (trantor.inventory['food'] >= NEEDEDWINNERFOOD and self.isReady == False):
            trantor.Play(WINNERPLAY)
            self.isReady = True

        if (trantor.broadcast.find_and_remove(WINNERSTRING)):
            self.nbReady += 1

        # if (self.nbReady < 5):
        #     print(trantor.id, ": could have level up but need more homies")
        #     return

        if (self.can_level_up(trantor)):
            trantor.Play("Incantation")
            # self.nbReady = 0    
            # self.isReady = False
