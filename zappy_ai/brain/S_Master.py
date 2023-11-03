from drone.IDrone import IDrone
from utils.enum import *
from utils.Constant import *
from brain.INeuron import INeuron
import trantor_handler.handler_trantor as th
import random
class S_Master(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.breadcum = [0,0,0]
        self.isPlaced = False
        self.mutationOrderId = 0
        self.nbCrossLine = 0

    def get_roles(self) -> str:
        if (self.mutationOrderId < len(MutationOrder)):
            return  MutationOrder[self.mutationOrderId]
        randomnb = random.randint(0, len(RandomMutation) - 1)
        return RandomMutation[randomnb]

    def use_neuron(self, trantor: IDrone):
        trantor.Play()
        trantor.Play("Inventory")
        trantor.Play("Connect_nbr")
        for _ in range(0,min(trantor.freeSlot, 10)):
            th.create_trantor(trantor.port, trantor.host, trantor.teamName)
        trantor.Play("Fork")
        while (trantor.broadcast.is_elem_in_broadcast()):
            call , soundPos = trantor.broadcast.extract_call()
            id = -1
            if (len(call.split("_")) > 1):
                splitedCall = call.split("_")
                call = splitedCall[0]
                id = int(splitedCall[1])
            if (call == ROLESTRING):
                if (soundPos == 0):
                    trantor.Play("Broadcast " + self.get_roles() + "_" + str(id))
                self.mutationOrderId += 1
            if (trantor.inventory['food'] < NEEDEDFOOD + 10):
                trantor.Play("Take food")