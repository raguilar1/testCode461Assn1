import sys
import socket
SEND_BUFFER_SIZE = 1

def client(server_ip, server_port):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except Exception as e:
        print 'Couldnt create socket'
    try:
        s.connect((server_ip, server_port))
    except Exception as e:
        print 'Couldnt connect to socket'
    while True:
        message = sys.stdin.read(SEND_BUFFER_SIZE)
        if not message:
            break
        try:
            s.sendall(message)
        except Exception as e:
            print 'Couldnt send to socket'
    s.close()
    pass


def main():
    """Parse command-line arguments and call client function """
    if len(sys.argv) != 3:
        sys.exit("Usage: python client-python.py [Server IP] [Server Port] < [message]")
    server_ip = sys.argv[1]
    server_port = int(sys.argv[2])
    client(server_ip, server_port)

if __name__ == "__main__":
    main()
