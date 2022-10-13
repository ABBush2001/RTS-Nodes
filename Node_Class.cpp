#include "Node_Class.h"
#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <stdbool.h>
using namespace std;

    Node::Node() { 
    }
    
    string Node::Get_Name() {
        return name;
    }

    void Node::Set_Name(string name1){
        name = name1;
    }

    Node Node::Get_Node(string node_name){
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

    void Node::Add_Node(string node_name) {
        //check if node already exists
        if(Links.find(node_name) != Links.end())
        {
            return;
        }
            
        //make a new node
        Node node1;
        Links.insert(std::map<string, Node>::value_type(node_name, node1));
    }

