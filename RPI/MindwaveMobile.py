import socket
import sys
import curses
from threading import Thread

from DataPointReader import DataPointReader

HOST = '' ## Set IP address of host (e.g. RPI)
PORT = 1234
ROBOT_COUNT = 2
conns = []  
count = 0

def main(scr):
    scr.keypad(True)
    curses.use_default_colors()
    curses.noecho()
    curses.curs_set(0)
    # curses.cbreak()
    scr.nodelay(1)
    scr.refresh()
    
    ## Get screen width/height
    height,width = scr.getmaxyx()

    ## To keep the information of both robots ordered in the terminal 
    padcount = ROBOT_COUNT + 1
    pads = []
    for i in range(padcount):
        pads.append(curses.newwin(height, width//padcount, 0, i * width//padcount))
        pads[i].scrollok(True)
        pads[i].refresh()

    scr.refresh()

    ## Create a socket seerver, bind the socket and start listening to the data on the socket
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

    def listen_to_mindwave(threadname):
        dataPointReader = DataPointReader()
        dataPointReader.begin() ## Begin the Mindwave Mobile V1 connection and start reading data points
        blinkcount = [] ## Keeps track of the datapoints needed to determine the amount of blinks
        eyeclose = 0 ## Detect whether the eyes closed
        eyeopen = 0 ## Detect whether the eyes opened after closing
        blink = 0 ## Count the number of blinks
        ready = 0 ## Recognize whether the signal strength is good enough to start the data reading

        while(True):
                dp = dataPointReader.nextDataPoint()
                ############## ATTENTION ##############
                ## Determine when the attention of the user is high enough for the robot to start driving
                if(dp != None and dp[0] == 'p' and int(dp[1]) == 0):
                    ready = 1

                if(ready == 1):
                    if(dp != None and dp[0] == 'a'):
                        if(int(dp[1]) >= 50):
                            pads[0].addstr(b'1')
                            for i in range(count):
                                (conn, addr) = conns[i]
                                conn.sendto(b'1', (addr[0], addr[1]))
                        else:
                            pads[0].addstr(b'0')
                            for i in range(count):
                                (conn, addr) = conns[i]
                                conn.sendto(b'0', (addr[0], addr[1]))

                    ############## BLINKING ##############
                    ## Determine when the user blinks and how often the user blinks
                    if(dp != None and dp[0] == 'b'):
                        blinkcount.append(int(dp[1]))
                        if(int(dp[1]) > 300 and eyeclose == 0):
                            eyeclose = 1
                        if(eyeclose == 1 and int(dp[1]) < -120):
                            eyeopen = 1
                        if(eyeclose == 1 and eyeopen == 1):
                            blink += 1
                            eyeclose = 0
                            eyeopen = 0
                        if(blink == 0):
                            blinkcount.clear()
                        if(len(blinkcount) == 500):
                            if(blink == 1):
                                pads[0].addstr(b'2')
                                for i in range(count):
                                    (conn, addr) = conns[i]
                                    conn.sendto(b'2', (addr[0], addr[1]))
                            elif(blink == 2):
                                pads[0].addstr(b'3')
                                for i in range(count):
                                    (conn, addr) = conns[i]
                                    conn.sendto(b'3', (addr[0], addr[1]))
                            else:
                                pads[0].addstr(b'4')
                                for i in range(count):
                                    (conn, addr) = conns[i]
                                    conn.sendto(b'4', (addr[0], addr[1]))
                            blink = 0
                            blinkcount.clear()

    Thread(target=listen_to_clients, args=("listen_to_clients", )).start()
    Thread(target=listen_to_mindwave, args=("listen_to_mindwave", )).start()
    
    while(True):
        for i in range(padcount):
            pads[i].refresh()

curses.wrapper(main)