import matplotlib.pyplot as plt
import numpy as np
import os

class Plot:
    def __init__(self, title="", xlabel="x", ylabel="y"):
        self.__title = title
        self.__xlabel = xlabel
        self.__ylabel = ylabel
        self.__lineDict = {}
    
    def setTitle(self,entry):
        self.__title = entry
        
    def getTitle(self):
        return self.__title

    def addLine(self, label, abscissas, ordinates):
        self.__lineDict.update({label:(np.array(abscissas), np.array(ordinates))})
        
    def removeLine(self,label):
        self.__lineDict.pop(label,None)
        
    def plotAll(self, save_path="", save_name="plot.png",save=True):
        plt.figure()
        for label, coordinates in self.__lineDict.items():
            plt.plot(coordinates[0],coordinates[1],label=label)
        plt.xlabel(self.__xlabel)
        plt.ylabel(self.__ylabel)
        plt.title(self.__title)
        plt.legend()
        if save:
            filepath = save_name if not save_path else os.path.join(save_path, save_name)
            plt.savefig(filepath)
        plt.show()
    
    def plotSelected(self, labels, save_path="", save_name="plot-selected.png",save=True):
        plt.figure()
        for label in labels: 
            if not label in self.__lineDict.keys():
                continue
            plt.plot(self.__lineDict[label][0],self.__lineDict[label][1],label=label)
        plt.xlabel(self.__xlabel)
        plt.ylabel(self.__ylabel)
        plt.title(self.__title)
        plt.legend()
        if save:
            filepath = save_name if not save_path else os.path.join(save_path, save_name)
            plt.savefig(filepath)
        plt.show()
    