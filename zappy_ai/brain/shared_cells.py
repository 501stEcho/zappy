from drone.IDrone import IDrone
from utils.Constant import *
from utils.enum import Mutation

from brain.Soldier import Soldier
from brain.INeuron import INeuron
from brain.Gerudo import Gerudo
from brain.Farmer import Farmer
from brain.S_Master import S_Master
from brain.Winner import Winner
from brain.Miner import Miner
from brain.Crook import Crook
from brain.Kamikaze import Kamikaze
from brain.China import China
from brain.Caller import Caller
from brain.Parrot import Parrot

class Instinct(INeuron):
    def __init__(self) -> None:
        super().__init__()
        self.alive = True
        self.isBrainReady = False
        self.isMutationReady = False
        self.breadcum = [0,0,0] #[left, forward, right]

    def assign_dir(self, trantor: IDrone) -> None:
        trantor.Play("Look")
        while (trantor.fov[1][1]['player'] != 0):
            trantor.Play("Right")
            trantor.Play("Look")

    def assign_brain(self, trantor: IDrone) -> None:
        if (self.isMutationReady == False):
            if (trantor.mutation.value == Mutation.SOLDIER.value):
                trantor.brain = Soldier()
            if (trantor.mutation.value == Mutation.FARMER.value):
                trantor.brain = Farmer()
            if (trantor.mutation.value == Mutation.GERUDO.value):
                trantor.brain = Gerudo()
            if (trantor.mutation.value == Mutation.S_MASTER.value):
                trantor.brain = S_Master()
            if (trantor.mutation.value == Mutation.WINNER.value):
                trantor.brain = Winner()
            if (trantor.mutation.value == Mutation.MINER.value):
                trantor.brain = Miner()
            if (trantor.mutation.value == Mutation.CROOK.value):
                trantor.brain = Crook()
            if (trantor.mutation.value == Mutation.KAMIKAZE.value):
                trantor.brain = Kamikaze()
            if (trantor.mutation.value == Mutation.CHINA.value):
                trantor.brain = China()
            if (trantor.mutation.value == Mutation.CALLER.value):
                trantor.brain = Caller()
            if (trantor.mutation.PARROT == Mutation.PARROT.value):
                trantor.brain = Parrot()
            self.isMutationReady = True

        if (trantor.baseReady):
            self.assign_dir(trantor)
            self.isBrainReady = True

    def sound_pos_handler(self, pos:int, trantor:IDrone):
        if (pos == -1):
            return "NONE"
        if (pos == 0):
            self.isAtbase = True
            return "NONE"
        if (pos == 1):
            return "Forward"
        if (pos == 7):
            return "Right"
        if (pos == 3):
            return "Left"
        if (pos == 5):
            trantor.Play("Right")
            return "Right"
        if (pos == 2):
            trantor.Play("Forward")
            trantor.Play("Left")
            trantor.Play("Forward")
            return "Right"          
        if ( pos == 8):
            trantor.Play("Forward")
            trantor.Play("Right")
            trantor.Play("Forward")
            return "Left"
        if (pos == 4):
            trantor.Play("Left")
            trantor.Play("Forward")
            trantor.Play("Left")
            return "Forward"
        if (pos == 6):
            trantor.Play("Right")
            trantor.Play("Forward")
            trantor.Play("Right")
            return "Forward"

    def searchFood(self, trantor: IDrone) -> None:
        trantor.isStarving = True
        trantor.Play("Look")
        for _ in range(0,trantor.fov[0][0]['food']):
            if (trantor.inventory['food'] > NEEDEDFOOD):
                return
            trantor.Play("Take food")
        trantor.Play("Inventory")
        while trantor.inventory['food'] < NEEDEDFOOD:
            self.take_elem_on_front_row(trantor, "food")
            trantor.Play("Inventory")
            self.breadcum[1] += 1
        self.turn_back(trantor)
        for _ in range(0, self.breadcum[1]):
            trantor.Play("Forward")
        self.turn_back(trantor)
        self.breadcum[1] = 0
        trantor.isStarving = False

    def find_base(self,trantor: IDrone) -> None:
        _, pos = trantor.broadcast.extract_paterns(CALLSTRING)
        while(pos > 0):
            dir = self.sound_pos_handler(pos, trantor)
            trantor.Play(dir)
            _, pos = trantor.broadcast.extract_paterns(CALLSTRING)
            while (pos == -1):
                trantor.Play()
                _, pos = trantor.broadcast.extract_paterns(CALLSTRING)

    def handle_instinct(self,trantor: IDrone) -> None:
        trantor.Play("Inventory")
        _, pos = trantor.broadcast.extract_paterns(CALLSTRING)
        trantor.broadcast.clean_patern(CALLSTRING)

        if (pos > 0):
            self.find_base(trantor)
        if (trantor.broadcast.find_and_remove(PLAYSTRING)):
            trantor.baseReady = True
        if (trantor.inventory['food'] < MINFOOD):
            self.searchFood(trantor)
            trantor.Play("Inventory")
