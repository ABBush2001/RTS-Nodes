# RTS-Nodes

This is a generic Real-Time-Strategy(RTS) game inventory management system. It uses C++ to take in a list of nodes (where each line is in the format "parent child"). It uses a list to hold all existing nodes, and each node uses a hashmap to hold all of its 'child' nodes. It then passes this data into a Python script, which uses Tkinter to convert it to a GUI. In this GUI, users can see a tree representing the nodes and their relationships. Additionally, users have the options to delete nodes, by typing their names into a text field, or to quit out of the application.
