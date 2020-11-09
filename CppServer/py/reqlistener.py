import signal
from scapy.all import *
from scapy.utils import hexdump
import sys
from colorama import Fore, init
from http.server import *

methods = ["GET", "POST", "PUT", "PATCH"]

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200, message="wadwa")
        self.send_header('Content-Type', 'text/plain')
        self.end_headers()
    


def sigintcallback(sig, frame):
    print(f'{Fore.RED}Graceful cancellation...')
    sys.exit(0)

def run_server(server_class=HTTPServer, handler_class=BaseHTTPRequestHandler):
    server_address = ('',8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    init()
    signal.signal(signal.SIGINT, sigintcallback)
    print(f'{Fore.GREEN} Starting db handler server on port 8000....')
    run_server(server_class=ThreadingHTTPServer, handler_class=RequestHandler)