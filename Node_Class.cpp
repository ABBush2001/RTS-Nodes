#include "Node_Class.h"
#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <stdbool.h>

    Node::Node() { 
    }
    
    std::string Node::Get_Name() {
        return name;
    }

    void Node::Set_Name(std::string name1){
        name = name1;
    }

    Node Node::Get_Node(std::string node_name){
        if(Links.find(node_name) == Links.end())
        {
            Node nullNode;
            return nullNode;
        }
        else 
        {
            return Links.find(node_name)->second;
        }
    }

    void Node::Add_Node(std::string node_name) {
        //check if node already exists
        if(Links.find(node_name) != Links.end())
        {
            return;
        }
            
        //make a new node
        Node node1;
        Links.insert({node_name, node1});
    }

    void SetDependentNode(Node parent, Node child, std::map<std::string, Node> masterList)
    {
        //take in a parent and child node; if child already exists, then grab it from master list and add to list for parent node; else, update parent node and master list
        //if parent already exists, grab it from master list and update its child list

        /*Child already exists*/
        if(masterList.find(child.Get_Name()) != masterList.end())
        {
            parent.Add_Node(child.Get_Name());
            parent.isUsable = true;
        }
        /*else if child doesn't already exists*/
        else if(masterList.find(child.Get_Name()) == masterList.end())
        {
            parent.Add_Node(child.Get_Name());
            parent.isUsable = true;
        }

        /*If parent already exists*/
        if(masterList.find(parent.Get_Name()) != masterList.end())
        {
            
        }
    }
