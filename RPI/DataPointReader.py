from ByteReader import ByteReader
from DataPointParser import DataPointParser
import collections

class DataPointReader:
    def __init__(self):
        self._byteReader = ByteReader() ## Initialize MindwaveMobileRawReader where all byte operations take place
        self._dpQueue = collections.deque() ## Deque used for quicker append and pop operations which are needed for fast data point reading



    ### CONNECT TO THE MINDWAVE MOBILE OVER BLUETOOTH TO START RECEIVING DATA ###
    def begin(self):
        self._byteReader.mindWaveMobileConnect()
    


    ### READ NEXT DATA POINTS FROM THE MINDWAVE MOBILE ###
    def nextDataPoint(self):
        if (not (len(self._dpQueue) > 0)): ## Check whether there are multiple data points in the queue
            ## Put the next datapoint in the queue
            dp = self._NextPacketDataPoints()
            self._dpQueue.extend(dp)
        return self._dpQueue.pop() ## Get next datapoint from the queue
    


    ### GET DATA POINTS IN THE NEXT PACKET ###
    def _NextPacketDataPoints(self):
        ## Go to the start of the next packet
        while(True):
            b = self._byteReader.getByte()
            if (b == 0xaa):  ## We need two 0xaa bytes since these indicate the start of a packet
                b = self._byteReader.getByte()
                if (b == 0xaa): ## Check whether we have arrived at the start of the packet
                    break

        ## Read the packet
        payloadL = self._byteReader.getByte() ## Get the payload length
        payloadB = self._byteReader.getBytes(payloadL)  ## Get the payload bytes
        checkSum = self._byteReader.getByte()  ## Get the checksum
        payloadSum = sum(payloadB)  ## Get the sum of the payload bytes
        invertedLastEightBitsPayload = ~(payloadSum % 256) + 256 ## Compute 1's complement with the help of the last eight bits of the payload bytes

        if (not (invertedLastEightBitsPayload == checkSum)): ## Check whether checksum is ok
            ## If not, go to the next packet and try again
            return self._NextPacketDataPoints() 
        else:
            dp = DataPointParser(payloadB).parseDataPoints() ## Get the information that the data point carries with it
        self._byteReader.clearBuffer()
        return dp
        
    
    
    
    
