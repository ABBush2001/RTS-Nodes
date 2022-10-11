#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <iterator>
#include <map>
#include <stdbool.h>


class Node
{
    std::string name;

    private:
        std::map<std::string, Node> Links;
        

    public:

        bool isUsable = false;

        Node();

        std::string Get_Name();
        void Set_Name(std::string name1);
        Node Get_Node(std::string node_name);
        void Add_Node(std::string node_name);

};

#endif