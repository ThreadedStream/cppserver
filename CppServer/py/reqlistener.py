import signal
from scapy.all import *
from scapy.utils import hexdump
import sys
from colorama import Fore, init

methods = ["GET", "POST", "PUT", "PATCH"]

def sigintcallback(sig, frame):
    print(f'{Fore.RED}Graceful cancellation...')
    sys.exit(0)

def callback(packet):
    http_packet = str(packet)
    if http_packet.find('POST'):
        return post_print(packet)

def post_print(packet):
    ret = ""
    ret += "\n".join(packet.sprintf("{Raw:%Raw.load%}\n").split(r"\r\n"))
    return ret

if __name__ == '__main__':
    init()
    signal.signal(signal.SIGINT, sigintcallback)
    sniff(prn=callback, filter="tcp port 443")
