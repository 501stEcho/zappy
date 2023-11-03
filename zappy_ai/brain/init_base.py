from drone.drone import Drone
import trantor_handler.handler_trantor as th
from utils.enum import *
from utils.Constant import *

class base_init():
    def __init__(self) -> None:
        self.nbTrantor  = 0
        self.isAtbase = False
        self.isLeader = False

    def am_i_the_leader(self,trantor:Drone) -> bool:
        trantor.Play("Look")
        for _ in range(0,8):
            trantor.Play()
            simplifiedBroadcast, _ = trantor.broadcast.extract_paterns([BASESTRING, CALLSTRING])
            if (BASESTRING == simplifiedBroadcast):
                return False
            if (CALLSTRING == simplifiedBroadcast):
                self.isAtbase = True
                trantor.baseReady = True
                return False
        if(trantor.fov[0][0]['player'] > 1):
            self.isAtbase = True
            return False
        for _ in range(0, trantor.socket.sizeLeft):
            self.nbTrantor += 1
            th.create_trantor(trantor.port, trantor.host, trantor.teamName)
        return True

    def sound_pos_handler(self, pos:int, trantor:Drone):
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
        
    def Regroup(self,trantor: Drone):
        self.isNewBorn = False
        _, soundPos = trantor.broadcast.extract_paterns([BASESTRING, HOMESTRING])
        action = self.sound_pos_handler(soundPos, trantor)
        trantor.Play(action)
        trantor.Play("Take food")
        trantor.__Flush_Calls__()
        trantor.broadcast.reset()
        while (not trantor.broadcast.is_elem_in_broadcast()):
            trantor.Play()

    def become_sedentary(self,trantor: Drone):
        idx = 1
        self.isLeader = self.am_i_the_leader(trantor)
        while not self.isAtbase and trantor.alive:
            if (self.isLeader):
                trantor.lead = True
                trantor.Play(BASEPOSCALL)
                idx += 1
                if (idx % 3 == 0):
                    trantor.Play("Take food")
                    trantor.Play("Look")
                if (trantor.fov[0][0]['player'] > self.nbTrantor):
                    for _ in range(0,10):
                        trantor.Play(HOMECALL)
                    self.isAtbase = True
            else:
                self.Regroup(trantor)
        self.handle_native_birth(trantor)

    def string_to_mutation(self,call: str) -> Mutation:
        if (call == "FARMER"):
            return Mutation.FARMER
        if (call == "GERUDO"):
            return Mutation.GERUDO
        if (call == "WINNER"):
            return Mutation.WINNER
        if (call == "SOLDIER"):
            return Mutation.SOLDIER
        if (call == "CALLER"):
            return Mutation.CALLER
        if (call == "MINER"):
            return Mutation.MINER
        if (call == "CROOK"):
            return Mutation.CROOK
        if (call == "KAMIKAZE"):
            return Mutation.KAMIKAZE
        if (call == "SMASTER"):
            return Mutation.S_MASTER
        if (call == "CHINA"):
            return Mutation.CHINA
        if (call == "PARROT"):
            return Mutation.PARROT

    def assign_mutation(self,trantor: Drone):
        trantor.Play(ROLEPLAY + "_" + str(trantor.id))
        while (trantor.mutation.value == 1):
            trantor.Play()
            while (trantor.broadcast.is_elem_in_broadcast()):
                call, _ = trantor.broadcast.extract_call()
                id = -1
                if (len(call.split("_")) > 1):
                    splitedCall = call.split("_")
                    call = splitedCall[0]
                    id = int(splitedCall[1])
                if (call in MutationOrder and id == trantor.id):
                    trantor.mutation = self.string_to_mutation(call)

    def handle_native_birth(self,trantor: Drone):
        if (self.isLeader):    
            trantor.Play("Look")
            trantor.mutation = Mutation.S_MASTER
        else:
            self.assign_mutation(trantor)
