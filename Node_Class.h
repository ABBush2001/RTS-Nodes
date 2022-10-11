#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <iterator>
#include <map>
#include <stdbool.h>
using namespace std;

class Node
{
    string name;

    private:
        
        

    public:

        bool isUsable = false;
        map<string, Node> Links;

        Node();

        std::string Get_Name();
        void Set_Name(string name1);
        Node Get_Node(string node_name);
        void Add_Node(string node_name);

};

#endif