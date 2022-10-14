#include "rts_nodes.h"
#include "Node_Class.h"
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

void generateList(list<Node> &masterList) {
    
    ifstream myfile;

    myfile.open("resource.txt");

    if(myfile.is_open())
    {
        string myline;

        while(getline(myfile, myline))
        {
            smatch m;
            Node parent;
            Node child;

            if(regex_search(myline, m, std::regex("^.* ")))
            {
                parent.Set_Name(trim(m[0]));
            }

            if(regex_search(myline, m, regex(" .*")))
            {
                child.Set_Name(trim(m[0]));
            }

            SetDependentNode(parent, child, masterList);

        }
        
    }
    
    myfile.close();
}

void SetDependentNode(Node parent, Node child, list<Node> &masterList) {

    //take in a parent and child node; if child already exists, then grab it from master list and add to list for parent node; else, update parent node and master list
        //if parent already exists, grab it from master list and update its child list

        bool parentFound = false;
        bool childFound = false;

        //check if parent and child already exists in masterlist
        list<Node>::iterator it;

        for(it = masterList.begin(); it != masterList.end(); it++)
        {
            //if parent found
            if(it->Get_Name() == parent.Get_Name())
            {
                //set parent equal to node from list
                parent.Links = it->Links;

                //check if child already exists in the parent's map
                if(parent.Get_Node(child.Get_Name()).Get_Name() == child.Get_Name())
                {
                }
                else
                {
                    parent.Add_Node(child.Get_Name());
                    parent.isUsable = true;
                }

                //re-add parent to the masterList
                it->Links = parent.Links;
                it->isUsable = parent.isUsable;

                parentFound = true;

            }

            //if child found
            if(it->Get_Name() == child.Get_Name())
            {
                childFound = true;
            }
        }

        //if parent not found
        if(parentFound == false)
        {
            //add child to list and then add to masterlist
            parent.Add_Node(child.Get_Name());
            parent.isUsable = true;
            masterList.push_back(parent);
        }

        //if child not found
        if(childFound == false)
        {
            masterList.push_back(child);
        }
}

void menu(list<Node> &masterList) {

    //read masterlist output into a temporary text file to be used by the python gui
    ofstream myfile("list.txt");

    /*iterate through masterList, output each parent with arrows to its children*/

    list<Node>::iterator it;

    for(it = masterList.begin(); it != masterList.end(); it++)
    {

        myfile << it->Get_Name() << endl;

        map<string, Node>::iterator i;

        for(i = it->Links.begin(); i != it->Links.end(); i++)
        {
            myfile << " ---> " << i->first << endl;
        }
    }

    myfile.close();

    string command = "python3 rts_window.py";
    system(command.c_str());

    //delete text file
    remove("list.txt");
}

string ltrim(const string &s) {

    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s) {

    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) {

    return rtrim(ltrim(s));
}