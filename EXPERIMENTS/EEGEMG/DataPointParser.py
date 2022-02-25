class DataPointParser:
    def __init__(self, payloadB):
        self._payloadB = payloadB ## Payload bytes
        self._payloadI = 0 ## Payload index
    


    ### PARSING OF DATA POINTS ###
    def parseDataPoints(self):
        dps = [] ## Maintain list of all data points
        ## Stop when the index is at the end of the payload bytes buffer
        while (not (self._payloadI == len(self._payloadB))):
            dp = self._parseDataPoint() ## Parsing a single data point
            dps.append(dp) ## Add parsed data point to list of data points
        return dps
    


    ### PARSING OF A SINGLE DATA POINT ###
    def _parseDataPoint(self):
        ## Get the row code and ignore the extended code bytes (0x55)
        b = self._payloadB[self._payloadI] #Get the next byte
        self._payloadI += 1 ## Increment the payloadIndex with 1 when the next byte is used
        while (b == 0x55):
            b = self._payloadB[self._payloadI]
            self._payloadI = self._payloadI + 1
        dataRowCode = b

        ## Get the length of the value bytes (amount of bytes)
        dataRowHasLengthByte = dataRowCode > 0x7f
        if (dataRowHasLengthByte):
            byteNo = self._payloadB[self._payloadI]
            self._payloadI = self._payloadI + 1
        else:
            byteNo = 1

        ## Get the value bytes of the data row
        dataRowB = self._payloadB[self._payloadI : self._payloadI + byteNo]
        self._payloadI += byteNo

        #### WHAT INFORMATION DOES THE DATA POINT CARRY? ####
        if (dataRowCode == 0x02):
            return 'p', dataRowB[0]
        if (dataRowCode == 0x04): ## Get the attention value from the Mindwave Mobile data point
            return 'a', dataRowB[0]
        if (dataRowCode == 0x80): ## Get the (raw) data points from the Mindwave Mobile to later determine whether the user blinked
            self.blinkValue = dataRowB[0] * 256 + dataRowB[1]
            if self.blinkValue >= 32768:
                self.blinkValue -= 65536
            return 'b', self.blinkValue