
import matplotlib.pyplot as plt
import random
import numpy as np
# import scipy as sc
from scipy.interpolate import make_interp_spline

### BLINKING DATA ###
def blinking():
    with open("EEGEMG/EEG_participant_1.txt", "r") as tf:
        data = tf.read().split(',')

    ### SMOOTHED ###
    # x = np.asarray(data_x)
    # y = np.asarray(data)
    # # Initialise the subplot function using number of rows and columns
    # # figure, axis = plt.subplots(8, 1)
    # xnew = np.linspace(x.min(), x.max(), 500)
    # spl = make_interp_spline(x, y, k=3)
    # y_smooth = spl(xnew)
    # plt.plot(xnew, y_smooth)
    # plt.show()

    ### RAW ###
    np_datapointsList = np.asarray(data).astype(int)
    # normalize all values in array
    # result = (np_datapointsList - np.min(np_datapointsList))/np.ptp(np_datapointsList)
    # dataprint = list(result)
    plt.plot(np_datapointsList, '#2d2d2d', marker='',mfc='pink' ) #plot the data
    # plt.xlim(10250,11600)
    # plt.ylim(-650,650)
    # plt.xticks([]) #set the tick frequency on x-axis
    # plt.yticks([])
    plt.ylabel('Amplitude') #set the label for y axis
    plt.xlabel('Datapoint') #set the label for x-axis
    # plt.title("Plotting a list") #set the title of the graph
    plt.show() #display the graph

    # Combine all the operations and display
    plt.show()

### BLINKING DATA GRAPH ###
def blinking_graph():
    #!/usr/bin/python3
    data = [100, 83.3, 100, 100, 76.19, 95.24]
    plt.bar([1,2,3,4,5,6], data, width=0.3, color='#2d2d2d')
    plt.xlabel('Participant #')
    plt.ylim(70,100)
    plt.ylabel('Accuracy (%)')
    plt.show()

def attention_graph():
    p1 = [0,0,0,24,37,38,50,47,48,47,38,37,40,54,45,53,58,63,70,70,61,51,50,53,39,53,64,94,88,100,100,100,100,100,94,83,100,100,84,74,70,57,50,51,50,46,40,50,44,40,53,60,61,48,37,47,51,54,53,44,50]
    p2 = [0,0,5,16,23,11,32,39,45,45,68,78,69,69,80,83,85,72,60,55,49,42,55,66,73,68,72,72,72,85,85,76,62,62,41,42,55,73,90,85,78,85,88,85,84,80,79,81,78,74,68,78,80,75,82,79,93,100,87,76,56]
    p3 = [0,0,24,41,13,7,28,47,43,37,17,21,23,49,55,44,36,40,50,49,49,50,65,75,80,56,43,54,58,58,63,64,55,54,41,47,58,44,58,50,55,49,57,46,18,10,14,24,37,40,55,44,47,54,54,60,64,63,68,61,63]
    p4 = [0,0,44,51,60,75,83,69,69,69,47,44,43,31,40,54,67,60,69,66,66,69,51,43,40,54,62,67,70,78,80,67,51,43,44,54,49,49,49,53,59,69,84,96,97,100,75,57,54,48,32,40,38,52,78,88,94,53,52,40,47]

    time = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60]

    # Plotting both the curves simultaneously
    plt.plot(time, p1, color='#2d2d2d', label='p1')
    plt.plot(time, p2, color='#aa0f14', label='p2')
    plt.plot(time, p3, color='#4167b0', label='p3')
    plt.plot(time, p4, color='#58595b', label='p4')

    # Naming the x-axis, y-axis and the whole graph
    plt.ylabel("Attention level")
    plt.xlabel("Time (s)")

    # Adding legend, which helps us recognize the curve according to it's color
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 0.1),ncol=6)

    # To load the display window
    plt.show()

# blinking()
# blinking_graph()
attention_graph()
