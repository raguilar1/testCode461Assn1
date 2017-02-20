import sys
import socket
SEND_BUFFER_SIZE = 1

def client(server_ip, server_port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_ip, server_port))
    while True:
        message = sys.stdin.read(SEND_BUFFER_SIZE)
        if not message:
            break
        s.sendall(message)
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
