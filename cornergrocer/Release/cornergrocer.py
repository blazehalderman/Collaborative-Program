import os
import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

# read a file
def readFile():
    itemDict = dict()
    with open("./cornergrocerinput.txt") as f:
        line = f.readline()
        while line:
            itemName = line.strip()
            if ((itemName in itemDict) and len(itemDict) != 0):
                itemDict[itemName] += 1
                line = f.readline()
            else:
                itemDict[itemName] = 1
                line = f.readline()
        f.close()
    return itemDict

# create list of tuples from file
def printItemsFrequency():
    itemDict = readFile()
    print('\n')
    print("========================================")
    print("=                                      =")
    print("= GROCERY LIST: FREQUENCY OF ALL ITEMS =")
    print("=                                      =")
    print("========================================")
    print("=                                      =")
    print("=       ITEM          FREQUENCY        =")
    print("=                                      =")
    for item in itemDict:
        print("=       {:17}{:14}=".format(str(item), str(itemDict[item])))
    print("=                                      =")
    print("========================================")


# validates a specific item for frequency
def validateItemFrequency(item):
    itemDict = readFile()
    if item in itemDict.keys():
        return 1
    else:
        print()
        print("ERROR: no such item exists in grocery list")
        print("Please only enter items on the provided list of groceries")
        print()
        os.system("pause");
        return 0

# Gets frequency amount for a specific item
def getItemFrequency(item):
    itemDict = readFile()
    return (itemDict[item])

# creates dat file for histogram
def createDatFile():
    itemDict = readFile()
    with open("./frequency.dat", "w") as d:
        for item in itemDict:    
            d.write(str(item) + " " + str(itemDict[item]) + '\n')
        d.close()