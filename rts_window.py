from ast import Delete
from cgitb import text
from dataclasses import replace
from os import link, remove
import string
from tkinter import Canvas, Place
import tkinter as tk
import re

def exitProgram():
    window.quit()

def deleteNode():
    input = deleteField.get(1.0, 'end-1c')

    #iterate through nodes, if found, delete it
    #find nodes for which it is a child, and update their text to say 'not usable'
    for i in window.children:
        if i == input:
            window.children[i].destroy()
            break
    
    for j in links:
        for m in j[1]:
            if input == m:
                var = j[0] + "\n(not usable)"
                window.children[j[0]].configure(text=var)

def fileReadIn():
    f = open("list.txt", "r")

    links = []

    for line in f:
        if 'ml' in line:
            #firstString = line.replace('ml:', '')
            #masterList = firstString.split(' ')
            #masterList.remove('')
            #masterList.remove('\n')
            continue
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

    return links  


#read in the masterlist from the file as a list, and links as dictionary, then and generate the tree
links = fileReadIn()

#open the gui window
window = tk.Tk()
window.geometry('1000x1000')
canvas = Canvas(window, width=1000, height=1000)
canvas.pack()

cur_row = []
pos_x = 300
pos_y = 0

dictPos = {}

#generate the top row
for i in links:
    isChild = False

    #make a node for the parent
    nodeparent = tk.Label(text=str(i[0]), background='black', name=str(i[0]))
    #check to see if node is a child of any other node - if not, place at top of window
    for m in links:
        for k in m[1]:
            if str(k) == str(i[0]):
                isChild = True

    if isChild == False:
        nodeparent.place(x=pos_x, y=pos_y)
        dictPos[str(i[0])] = (pos_x, pos_y)
        pos_x += 100
        cur_row.append(str(i[0]))

#make the rest of the rows
treeFinished = False
pos_y += 100
pos_x = 300
children = []
temp_row = []

while treeFinished == False:
    treeFinished = True

    for i in cur_row:
        for j in links:
            if i == j[0]:
                if len(j[1]) != 0:
                    treeFinished = False

    for i in cur_row:
        for j in links:
            if i == j[0]:
                children = j[1]
                for k in children: 
                    if k in temp_row:
                        continue
                    else:
                        node = tk.Label(text=k, background='black', name=k).place(x=pos_x, y=pos_y)
                        dictPos[str(k)] = (pos_x, pos_y)
                        temp_row.append(k)
                        pos_x += 100

    for i in temp_row:
        for j in temp_row:
            for k in links:
                if j == k[0]:
                    for m in k[1]:
                        if i == m:
                            window.children[i].destroy()
                            temp_row.remove(i)
                            dictPos.pop(i)

    cur_row = temp_row
    temp_row = []
    pos_y += 100
    pos_x = 300

deleteField = tk.Text(width=52, height=2)
deleteButton = tk.Button(text='delete', command=deleteNode).place(y=720, x=400)
deleteField.place(y=720)
quitButton = tk.Button(text='quit', command=exitProgram).place(y=720, x=780)



#create lines between nodes
for i in window.children:
    for j in links:
        if i == j[0]:
            for k in window.children:
                for m in j[1]:
                    if m == k:

                        window.update()

                        val1 = dictPos[i]
                        val2 = dictPos[k]

                        canvas.create_line(val1[0], val1[1], val2[0], val2[1], arrow=tk.LAST)

canvas.create_line(0, 0, 10, 10)

window.mainloop()
