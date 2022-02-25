import socket
import sys
from threading import Thread
import keyboard
import curses
import math

HOST = '' ## Set IP address of host (RPI)
PORT = 1234
ROBOT_COUNT = 2

conns = []
count = 0

def main(scr):
    scr.keypad(True)
    curses.use_default_colors()
    curses.noecho()
    curses.curs_set(0)
    scr.nodelay(1)
    scr.refresh()

    # Get screen width/height
    height,width = scr.getmaxyx()

    padcount = ROBOT_COUNT + 1
    pads = []
    for i in range(padcount):
        pads.append(curses.newwin(height, width//padcount, 0, i * width//padcount))
        pads[i].scrollok(True)
        pads[i].refresh()

    scr.refresh()

    s = socket.socket(ROBOT_COUNT)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    pads[0].addstr('Socket server created\n')
    try:
        s.bind((HOST, PORT))
    except socket.error as err:
        pads[0].addstr(err)
        sys.exit()
    pads[0].addstr('Socket server bind complete\n')
    s.listen(0)
    pads[0].addstr('Socket server now listening\n')

    pads[0].refresh()
    scr.refresh()

    def recv(threadname, conn, pad):
       while True:
          data = conn.recv(1024).decode('utf-8')
          pad.addstr(data)

    def listen_to_clients(threadname):
       global count
       global conns
       while True:
          conn, addr = s.accept()
          conns.append((conn, addr))
          pads[0].addstr('Connection from: ' + addr[0] + ':' + str(addr[1]) + '\n')
          Thread(target=recv, args=('thread ' + str(count), conn, pads[count + 1])).start()
          count += 1

    Thread(target=listen_to_clients, args=("listen_to_clients", )).start()
    while True:
        # place anything to send to esp's here
        message=scr.getch()
        if message != -1:
            pads[0].addstr(chr(message))
            for i in range(count):
                (conn, addr) = conns[i]
                conn.sendto(message.to_bytes((message.bit_length() + 7) // 8, 'big'), (addr[0], addr[1]))

        for i in range(padcount):
            pads[i].refresh()


curses.wrapper(main)
