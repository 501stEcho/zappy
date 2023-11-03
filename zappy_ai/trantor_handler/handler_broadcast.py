from copy import copy
from typing import  Tuple

class BroadCast():
    def __init__(self) -> None:
        self.broadcast = [[],[],[],[],[],[],[],[],[]]
        self.enemyBroadcast = [[],[],[],[],[],[],[],[],[]]

    def extract_call(self) -> Tuple[str, int]:
        list = self.broadcast
        pos = 0
        for elem in list:
            if (len(elem) > 0):
                res = copy(elem[0])
                list[pos].remove(elem[0])
                return [res, pos]
            pos += 1
        return ["", -1]

    def extract_enemy_call(self) -> Tuple[str, int]:
        list = self.enemyBroadcast
        pos = 0
        for elem in list:
            if (len(elem) > 0):
                res = copy(elem[0])
                list[pos].remove(elem[0])
                return [res, pos]
            pos += 1
        return ["", -1]

    def clean_patern(self, patern: str)->None:
        list = self.broadcast
        for elem in list:
            elem = filter(lambda a: a != patern, elem)
    
    def extract_paterns(self, paterns:list[str]) -> Tuple[str, int]:
        list = self.broadcast
        pos = 0
        for elem in list:
            for patern in paterns:
                if (patern in elem):
                    elem.remove(patern)
                    return [patern, pos]
            pos += 1
        return ["", -1]

    def is_elem_in_broadcast(self):
        list = self.broadcast
        for elem in list:
            if len(elem) > 0:
                return True
        return False
    
    def find_and_remove(self, patern: str) -> bool:
        list = self.broadcast
        for elem in list:
            if (patern in elem):
                elem.remove(patern)
                return True
        return False

    def reset(self):
        self.broadcast = [[],[],[],[],[],[],[],[],[]]