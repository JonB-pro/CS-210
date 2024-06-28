import re
import string


#Prints out a menu with four options
def PrintMenu():
    print("Please enter a number to choose an option below:")
    print("1. Print List of Quantities of Items Purchased")
    print("2. Print Quantity of a Specific Item Purchased")
    print("3. Print a Histogram of Items Purchased")
    print("4. Exit")

# Prints list with quantities from file
def PrintItemizedList():

    # Returns dictionary of data from file
    fileName = input("Enter file name of list: ")
    itemizedList = CreateListFromFile(fileName)
    print()

    print("---List of Items and Quantity Sold---")
    for item in itemizedList:
        name = str(item)
        quant = str(itemizedList[item])
        print("-------------------------------------")
        print("|{}:{}|".format(name.center(18), quant.center(16)))
    print("-------------------------------------")
    print()

# Opens, reads, and creates dictionary from file
def CreateListFromFile(fileName):

    quantDict = {}
    fileOpen = open(fileName)
    content = fileOpen.read()
    fileOpen.close()
    list = content.splitlines()

    for item in list:
        quantDict[item] = list.count(item)

    return quantDict

# Returns quantity of item entered if in list
def ListQuantity(item):

    # Opens, reads, and creates a list from a file
    fileName = input("Enter name of File to Check: ")
    print()
    fileOpen = open(fileName)
    content = fileOpen.read()
    fileOpen.close()
    list = content.splitlines()
    
    # Capitalizes in case of human error
    item = item.capitalize() 

    if item in list:
        totalQuant = list.count(item)
        return totalQuant
    
    # Checks for pluralization
    items = item + "s"
    if items in list:
        totalQuant = list.count(items)
        return totalQuant
    
    # Causes request for resubmit in main code
    else:
        return 0 

# Writes from a file into a new data file
def WriteToFile(fileToWrite):    

    fileName = input("Enter name of file to pull data from: ")
    newList = CreateListFromFile(fileName)
    fiToWr = open(fileToWrite, "w")

    for item in newList:
        name = str(item)
        quant = newList[item]
        fiToWr.write("{} {} \n".format(name.center(18), quant))

    fiToWr.close()

    return 0
