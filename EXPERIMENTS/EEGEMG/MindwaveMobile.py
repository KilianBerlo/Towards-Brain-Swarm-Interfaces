from DataPointReader import DataPointReader
## SAVE DATA TO FILE ###--for debugging
import time
import numpy as np
import sys
import os
np.set_printoptions(threshold=sys.maxsize)


if __name__ == '__main__':
    dataPointReader = DataPointReader()
    dataPointReader.begin()
    blinkcount = []
    eyeclose = 0
    eyeopen = 0
    blink = 0
    ready = 0 ## Recognize whether the signal strenght is good enough to start the data reading

    ## SAVE DATA TO FILE ###--for debugging
    dpsList = []
    blinksList = []
    t_end = time.time() + 60
    while(time.time() < t_end):
    # while(True):
        dp = dataPointReader.nextDataPoint()
        if(dp != None and dp[0] == 'p' and int(dp[1]) == 0):
            ready = 1

        if(ready == 1):
            print("START")
            ############## ATTENTION ##############
            ## Determine when the attention of the user is high enough for the robot to start driving
            # if(dp != None and dp[0] == 'a'):
            #     print("Level: " + str(int(dp[1])) + "\n")

            ############## BLINKING ##############
            ## Determine when the user blinks and how often the user blinks
            if(dp != None and dp[0] == 'b'):
                dpsList.append(str(dp[1])) #--for debugging
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
                    blinksList.append(blink)
                    print("Blinks: " + blink)
                    blink = 0
                    blinkcount.clear()

    print("STOP")
    print(str(blinksList))

    ## SAVE DATA TO FILE ###--for debugging
    f = open("participant.txt", "w")
    f.write(str(dpsList))
    f.close()

    with open("participant.txt", "r") as infile, open("EEG_participant.txt", "w") as outfile:
        datalist = infile.read()
        datalist = datalist.replace("'", "")
        datalist = datalist.replace(" ", "")
        datalist = datalist.replace("[", "")
        datalist = datalist.replace("]", "")
        outfile.write(datalist)
        infile.close()
        outfile.close()
        os.remove("participant.txt")
