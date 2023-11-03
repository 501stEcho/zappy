from multiprocessing import Process

class ZappyFast():
    def __init__(self):
        self.queu: list[str,Process]= []

    def add(self, function, args, name):
        self.queu.append((name, Process(target=function, args=args)))
        self.queu[-1][1].start()

    def run(self):
        for thread in self.queu:
            thread[1].start()
    def kill(self, idx:int):
        self.queu[idx][1].join()
        self.queu.remove(self.queu[idx])