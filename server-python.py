import sys
import socket

RECV_BUFFER_SIZE = 2048
QUEUE_LENGTH = 10

def server(server_port):
    #code edited from https://docs.python.org/2/library/socket.html

    #open socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    #bind
    s.bind(('', server_port))

    #listen
    s.listen(QUEUE_LENGTH)
    while True: 
        conn, addr = s.accept()
        while True:
            #reads up to buffer size, returns value equivalent to false if nothing read
            data = conn.recv(RECV_BUFFER_SIZE)
            if not data: break
            sys.stdout.write(data)
        conn.close()    
    pass


def main():
    """Parse command-line argument and call server function """
    if len(sys.argv) != 2:
        sys.exit("Usage: python server-python.py [Server Port]")
    server_port = int(sys.argv[1])
    server(server_port)

if __name__ == "__main__":
    main()
