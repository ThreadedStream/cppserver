import signal
import sys
from colorama import Fore, init


def sigintcallback(sig, frame):
    print(f'{Fore.RED}Graceful cancellation...')
    sys.exit(0)


def listen():
    pass    

if __name__ == '__main__':
    init()
    signal.signal(signal.SIGINT, sigintcallback)


