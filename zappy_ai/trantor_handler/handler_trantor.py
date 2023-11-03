from multiprocessing import Process
from drone.drone import Drone
import name_queue as n_q
from brain.init_base import base_init
import utils.Constant as c

baseInit = base_init()
teamName = n_q.TEAMNAME

def handle_trantor(trantor: Drone, port:int, host:str, teamName:str):
    print("_____ DRONE ", trantor.id ," _____")
    baseInit.become_sedentary(trantor)
    print("_____ DRONE ", trantor.id ,"is now a", trantor.mutation, " _____")
    while trantor.alive:
        trantor.Think()

def create_trantor(port:int, host:str, teamName: str):
    c.set_elem(teamName, port, host)
    print("HOST = ", c.HOST, " PORT = ", c.PORT, " TEAMNAME = ", c.TEAMNAME)
    newTrantor = Drone()
    newProcess = Process(target=handle_trantor, args=[newTrantor,port, host, teamName])
    newProcess.start()
