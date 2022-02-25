import bluetooth
import sys

class ByteReader:
    def __init__(self):
        self._buffer = []
        self._bufferLoc = 0
        


    ### CONNECT TO THE MINDWAVE MOBILE OVER BLUETOOTH TO START RECEIVING DATA ###
    def mindWaveMobileConnect(self):
        self.socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        mindwaveMobileAddr = '20:68:9D:C2:26:9C' ## Give bluetooth address of Mindwave Mobile so it can connect to that address
        ## Try to connect to the Mindwave Mobile, if it doesn't work exit the program
        while(True):
            try:
                self.socket.connect((mindwaveMobileAddr, 1))
                return
            except bluetooth.btcommon.BluetoothError as error:
                print("Not connected to BCI: " + str(error))
                sys.exit() 



    ### GET ONE BYTE FROM THE MINDWAVE MOBILE ###
    def getByte(self):
        if (len(self._buffer) <= self._bufferLoc + 100): ## Make sure that more bytes can be read from the Mindwave Mobile
            newBs = self._readBytesBCI(100) ## Get the new bytes from the mindwave mobile
            self._buffer += newBs ## Add bytes read from the Mindwave Mobile into the buffer
        nextB = self._buffer[self._bufferLoc] ## Get the next byte in the buffer
        self._bufferLoc += 1 ## Update the buffer position
        return nextB
    


    ### GET THE BYTES FROM THE MINDWAVE MOBILE FOR THE PAYLOAD BYTES ###
    def getBytes(self, bytesCount):
        if (len(self._buffer) <= self._bufferLoc + bytesCount): ## Make sure that more bytes can be read from the Mindwave Mobile
            newBs = self._readBytesBCI(bytesCount)
            self._buffer += newBs ## Add bytes read from the Mindwave Mobile into the buffer
        nextBs = list(self._buffer[self._bufferLoc: self._bufferLoc + bytesCount]) ## Get the next "bytesCount" bytes from the buffer
        self._bufferLoc += bytesCount ## Update the buffer position by "bytesCount"
        return nextBs
        


    ### READ AVAILABLE DATA FROM THE MINDWAVE MOBILE ###
    def _readBytesBCI(self, bytesCount):
        missingBs = bytesCount ## missing bytes
        receivedBs = b'' ## Received bytes
        while(missingBs > 0):
            receivedBs += self.socket.recv(missingBs)
            missingBs = bytesCount - len(receivedBs)
        return receivedBs
    


    ### CLEAR THE BUFFER THAT'S ALREADY DEALTH WITH TO MAKE ROOM FOR THE NEXT PACKET ###
    def clearBuffer(self):
        self._buffer = self._buffer[self._bufferLoc : ]
        self._bufferLoc = 0