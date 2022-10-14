from asyncio.windows_events import NULL
import PySimpleGUI as sg

#class for Nodes
class Nodes:
    def __init__(self, name, links):
        self.name = name
        self.links = self.links

    def Get_Name(self):
        return self.name

    def Set_Name(self, name1):
        self.name = name1

    def Get_Node(self, node_name):
        if node_name in self.links:
            return self.links.find(node_name).second
        else:
            return NULL

    def Add_Node(self, node_name):
        #check if node already exists
        if node_name in self.links:
            return
            
        #make a new node
        node1 = Nodes()
        self.links[node_name] = node1

#read in the masterlist from the file and generate the tree



#open the gui window
sg.Window(title="Hello World", layout=[[]], margins=(100, 50)).read()