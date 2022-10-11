#include "Node_Class.h"
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
using namespace std;

void SetDependentNode(Node parent, Node child, map<string, Node> masterList) {
        //take in a parent and child node; if child already exists, then grab it from master list and add to list for parent node; else, update parent node and master list
        //if parent already exists, grab it from master list and update its child list

        /*If both the child and the parent already exist*/
        if((masterList.find(parent.Get_Name()) != masterList.end()) && (masterList.find(child.Get_Name()) != masterList.end()))
        {
            return;
        }
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
            parent = masterList.find(parent.Get_Name())->second;
            parent.Add_Node(child.Get_Name());
            parent.isUsable = true;
            masterList.find(parent.Get_Name())->second = parent;
        }
        /*If parent doesn't already exist*/
        else 
        {
            parent.isUsable = true;
            masterList.insert({parent.Get_Name(), parent});
        }
}


int main(int argc, char const *argv[])
{
    map<string, Node> masterList; 

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
                parent.Set_Name(m[0]);
            }

            if(regex_search(myline, m, regex(" .*")))
            {
                child.Set_Name(m[0]);
            }
            
            SetDependentNode(parent, child, masterList);
        }
        
    }
    
    myfile.close();
    
    map<string, Node>::iterator it;
    
    /*iterate through masterList, output each parent with arrows to its children*/
    for (it = masterList.begin(); it != masterList.end(); it++)
    {
        map<string, Node>::iterator i;
        
        for(i = it->second.Links.begin(); i != it->second.Links.end(); i++)
        {
            cout << it->second.Get_Name() << " ---> " << i->second.Get_Name() << endl;
        }
    }

    
    /*Expected Output:
    
    Handgun ---> Bullets
    Bullets ---> Ore
    Bombs ---> Ore
    Turret ---> Bullets
    
    */

    return 0;
}