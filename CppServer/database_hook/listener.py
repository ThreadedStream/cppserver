import socket
import os
from typing import List
import threading
import asyncio

FILENAME = 'F:/cppserver/CppServer/dblog.txt'

# class ObserverBase():
    
#     @abstractmethod
#     def subscribe(self, observer: ObserverBase):
#         pass

#     @abstractmethod
#     def unsubscribe(self, observer: ObserverBase):
#         pass

#     @abstractmethod
#     def notify(self) -> None:
#         pass


# class FileObserver(ObserverBase):

#     _subs: List[FileObserver] = []
#     def subscribe(self, observer: FileObserver):
#         _subs.append(observer)

#     def unsubscribe(self, observer: FileObserver):
#         if observer in _subs:
#             _subs.remove(observer)
        


def func1(arg:int):
    for i in range(arg):
        print("func1 -> : %d", i)

def func2(arg:int):
    for i in range(arg):
        print("func2 -> : %d", i)


def setup_threads():
    t1 = threading.Thread(target=func1, args=(10, ))
    t2 = threading.Thread(target=func2, args=(10,))
    t1.start()
    t2.start()

    t1.join()
    t2.join()


    print("Done!")
    

def listen_for_changes():
    if not os.access(FILENAME, os.W_OK):
        print("failed to open a file")
    else:
        with open(FILENAME, "r+") as stream:
            while(len(stream.read()) > 0):
                print(stream.read()) 
                stream.truncate(0)

def main():
    setup_threads()

main()
            

