import sys
import socket

RECV_BUFFER_SIZE = 2048
QUEUE_LENGTH = 10

def server(server_port):
    while True:
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except Exception as e:
            print 'Couldnt create socket'
        try:
            s.bind(('', server_port))
        except Exception as e:
            print 'Couldnt bind socket'
        try:
            s.listen(QUEUE_LENGTH)
        except Exception as e:
            print 'Couldnt listen socket'
        conn, addr = s.accept()
        while True:
            try:
                data = conn.recv(RECV_BUFFER_SIZE)
            except Exception as e:
                print 'Couldnt read from socket'
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
