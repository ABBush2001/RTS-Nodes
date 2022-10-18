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

//called after GUI is closed to update list
void UpdateList(map<string, Node> &masterList) {

    ifstream del_file;
    ifstream un_file;

    del_file.open("delete.txt");
    un_file.open("unusable.txt");

    if(del_file.is_open())
    {
        string myline;

        while(getline(del_file, myline))
        {
            map<string, Node>::iterator i;

            //deleted main node in masterlist, as well as references in links
            for(i = masterList.begin(); i != masterList.end(); i++)
            {
                if(i->first == myline)
                {
                    masterList.erase(myline);
                    cout << "deleted " << myline << endl;
                    break;
                }

                auto it = i->second.Links.find(myline);

                if(it != i->second.Links.end())
                {
                    i->second.Links.erase(myline);
                }
            }
        }
    }

    del_file.close();

    if(un_file.is_open())
    {
        string myline;

        while(getline(un_file, myline))
        {
            map<string, Node>::iterator i;

            for(i = masterList.begin(); i != masterList.end(); i++)
            {
                if(i->second.Get_Name() == myline)
                {
                    i->second.isUsable = false;
                }
            }
        }
    }

    un_file.close();

    //delete the files
    if(remove( "delete.txt" ) != 0)
    {
        cout << "Error deleting the file delete.txt" << endl; 
    }
    if(remove( "unusable.txt" ) != 0)
    {
        cout << "Error deleting the file unusable.txt" << endl; 
    }
}

void generateList(map<string, Node> &masterList) {
    
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

void SetDependentNode(Node parent, Node child, map<string, Node> &masterList) {

    //take in a parent and child node; if child already exists, then grab it from master list and add to list for parent node; else, update parent node and master list
        //if parent already exists, grab it from master list and update its child list

        bool parentFound = false;
        bool childFound = false;

        //check if parent and child already exists in masterlist
        map<string, Node>::iterator it;

        for(it = masterList.begin(); it != masterList.end(); it++)
        {
            //if parent found
            if(it->first == parent.Get_Name())
            {
                //set parent equal to node from list
                parent.Links = it->second.Links;

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
                it->second.Links = parent.Links;
                it->second.isUsable = parent.isUsable;

                parentFound = true;

            }

            //if child found
            if(it->second.Get_Name() == child.Get_Name())
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
            masterList.insert(map<string, Node>::value_type(parent.Get_Name(), parent));
        }

        //if child not found
        if(childFound == false)
        {
            masterList.insert(map<string, Node>::value_type(child.Get_Name(), child));
        }
}

void menu(map<string, Node> &masterList) {

    //read masterlist output into a temporary text file to be used by the python gui
    ofstream myfile("list.txt");

    /*iterate through masterList, output each parent with arrows to its children*/

    map<string, Node>::iterator it;

    myfile << "ml: ";

    for(it = masterList.begin(); it != masterList.end(); it++)
    {

        myfile << it->second.Get_Name() << " ";
    }

    myfile << endl;

    map<string, Node>::iterator i;

    for(it = masterList.begin(); it != masterList.end(); it++)
    {
        myfile << it->second.Get_Name() << ": ";

        for(i = it->second.Links.begin(); i != it->second.Links.end(); i++)
        {
            myfile << i->first << " ";
        }

        myfile << endl;
    }
    

    myfile.close();

    string command = "python3 rts_window.py";
    system(command.c_str());

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