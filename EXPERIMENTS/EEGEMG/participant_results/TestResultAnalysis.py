
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
    p1 = [0,0,0,47,69,87,100,100,100,100,100,96,97,100,96,100,100,94,90,83,90,91,93,84,84,90,93,100,87,70,70,64,70,81,81,87,83,87,87,87,100,100,91,77,77,56,57,70,88,100,93,87,78,67,77,81,84,83,74,53,60]
    p2 = [0,0,30,26,20,38,60,67,69,60,63,67,84,83,81,96,97,97,100,75,57,60,54,78,88,94,100,87,100,83,66,81,61,80,83,83,94,93,100,91,70,57,53,38,63,66,64,94,88,100,100,100,100,100,94,83,53,54,47,60,83]
    p3 = [0,0,30,20,20,26,48,75,83,84,75,74,61,67,78,64,78,67,63,57,37,41,43,51,69,69,47,34,40,53,81,87,66,38,30,34,44,57,60,57,51,50,48,51,64,56,56,69,74,78,78,69,57,63,51,30,26,3,1,1,1]
    p4 = [0,0,44,51,60,69,77,69,74,70,69,80,70,60,51,50,54,63,66,64,67,70,74,80,77,78,75,69,69,69,67,64,63,61,60,64,67,60,69,66,66,69,61,63,60,64,67,70,77,78,80,67,54,51,54,56,69,75,74,70,70]
    p5 = [0,0,51,66,78,88,87,88,87,83,80,74,75,83,88,93,100,100,100,100,100,97,96,97,93,96,94,96,96,93,91,91,97,94,100,97,93,93,87,81,83,84,93,88,93,93,90,96,96,100,97,93,91,84,77,70,54,41,40,43,53]
    p6 = [0,0,50,54,61,61,56,69,75,81,91,81,80,83,69,53,48,37,35,44,54,64,69,75,64,56,60,70,69,69,70,66,70,84,83,81,91,97,100,100,97,87,87,84,74,70,77,80,81,80,67,64,67,74,74,80,84,83,88,81,83]

    time = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60]

    # Plotting both the curves simultaneously
    plt.plot(time, p1, color='#2d2d2d', label='p1')
    plt.plot(time, p2, color='#aa0f14', label='p2')
    plt.plot(time, p3, color='#4167b0', label='p3')
    plt.plot(time, p4, color='#58595b', label='p4')
    plt.plot(time, p5, color='#057d56', label='p5')
    plt.plot(time, p6, color='#a6a8ab', label='p6')

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
