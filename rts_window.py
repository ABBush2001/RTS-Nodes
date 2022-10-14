from dataclasses import replace
import string
import tkinter as tk
import re

def fileReadIn():
    f = open("list.txt", "r")

    links = []

    for line in f:
        if 'ml' in line:
            firstString = line.replace('ml:', '')
            masterList = firstString.split(' ')
            masterList.remove('')
            masterList.remove('\n')
        elif re.search('.*:.*', line) != None:
            parentAndChild = re.split(':', line)
            childStr = parentAndChild[1]
            childStr = childStr.replace('\n', '')
            newChilStr = childStr.split(' ')
            newChilStr.remove('')
            newChilStr.remove('')
            parentAndChild[1] = newChilStr
            links.append(parentAndChild)

    f.close()  

    return masterList, links  



#read in the masterlist from the file as a list, and links as dictionary, then and generate the tree
masterList, links = fileReadIn()

print(links)

#open the gui window
window = tk.Tk()
window.geometry('800x800')

#make labels for each of the elements in the masterlist
for i in links:
    nodeparent = tk.Label(text='parent: ' + str(i[0]), background='black')  
    if not i[1]:
        node = tk.Label(text='children: None', background='black')
    else:
        chstr = 'children: '
        for j in i[1]:
            chstr = chstr + j + " "
        node = tk.Label(text=chstr, background='black')
    nodeparent.pack()
    node.pack()
window.mainloop()