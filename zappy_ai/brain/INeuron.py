from utils.Constant import *
#from drone.IDrone import IDrone
class INeuron():
    def __init__(self) -> None:
        self.dir = 0
        self.inPlace = False

    def turn_back(self, trantor) -> None:
        trantor.Play("Right")
        trantor.Play("Right")

    def take_all_elem(self, trantor, space :int, pos:int, elem:str) -> None:
        for _ in range(0,trantor.fov[space][pos][elem]):
            trantor.Play("Take food")

    def front(self, trantor):
        if (self.dir != 0):
            self.turn_back(trantor)
            trantor.Play("Forward")
            if (self.dir > 0):
                trantor.Play("Right")
            else:
                trantor.Play("Left")
        elif(not self.inPlace):
            self.inPlace = True
            trantor.Play("Forward")
        self.dir = 0

    def right(self, trantor):
        if (self.dir > 0):
            pass
        elif (self.dir < 0):
            self.turn_back(trantor)
            trantor.Play("Forward")
            trantor.Play("Forward")
        else: 
            trantor.Play("Right")
            trantor.Play("Forward")
        self.dir = 1

    def left(self, trantor):
        if (self.dir > 0):
            self.turn_back(trantor)
            trantor.Play("Forward")
            trantor.Play("Forward")
        elif (self.dir < 0):
            pass
        else: 
            trantor.Play("Left")
            trantor.Play("Forward")
        self.dir = -1

    def take_elem_on_front_row(self, trantor, elem:str) -> None:
            trantor.Play("Look")
            trantor.Play("Inventory")
            if (trantor.inventory[elem] > 50):
                self.front(trantor)
                self.inPlace = False
                self.dir = 0
                return
            self.front(trantor)
            self.take_all_elem(trantor, 1, 1, elem) # 1 1 front 
            if (trantor.fov[1][0][elem] > 0):
                self.left(trantor)
                self.take_all_elem(trantor, 1, 0, elem) # 1 0 left 
            if (trantor.fov[1][2][elem] > 0):
                self.right(trantor)
                self.take_all_elem(trantor, 1, 2, elem) # 1 2 right 
            self.front(trantor)
            self.inPlace = False
            self.dir = 0


    def is_rock_on_row(self, trantor, space :int, pos:int) -> bool:
        item = trantor.fov[space][pos]
        for attr, value in item.items():
            if (attr != 'player' and value > 0):
                return True
        return False

    def take_all_rock(self, trantor, space :int, pos:int) -> None:
        item: dict = trantor.fov[space][pos]
        for attr, value in item.items():
            number = value
            while (attr != 'player' and number > 0):
                number -= 1
                if (trantor.inventory[attr] <= 3):
                    trantor.Play("Take "+ attr)
                if (attr == "food" and trantor.inventory["food"] < NEEDEDFOOD):
                    trantor.Play("Take food")

    def take_rock_on_front_row(self, trantor) -> None:
            trantor.Play("Look")
            trantor.Play("Inventory")
            self.front(trantor)
            self.take_all_rock(trantor, 1, 1) # 1 1 front 
    
            if (self.is_rock_on_row(trantor, 1, 0)):
                self.left(trantor)
                self.take_all_rock(trantor, 1, 0) # 1 0 left 

            if (self.is_rock_on_row(trantor, 1, 2)):
                self.right(trantor)
                self.take_all_rock(trantor, 1, 2) # 1 2 right 

            self.front(trantor)
            self.inPlace = False
            self.dir = 0

    def use_neuron(self, trantor):
        pass