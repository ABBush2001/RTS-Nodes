#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <iterator>
#include <map>
#include <stdbool.h>


class Node
{
    private:
        std::string name;
        std::map<std::string, Node> Links;
        bool isUsable = false;

    public:

        std::string Get_Name();
        void Set_Name(std::string name1);
        Node Get_Node(std::string node_name);
        Node Set_Node(std::string node_name);

};

#endif