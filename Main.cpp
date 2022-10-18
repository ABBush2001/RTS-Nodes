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

int main(int argc, char const *argv[])
{
    map<string, Node> masterList; 

    ifstream myfile;

    //fill masterList
    generateList(masterList);

    //open menu window
    menu(masterList);

    //update the masterlist
    UpdateList(masterList);

    map<string, Node>::iterator i;

    for(i = masterList.begin(); i != masterList.end(); i++)
    {
        cout << i->first << endl;

        map<string, Node>::iterator it;

        for(it = i->second.Links.begin(); it != i->second.Links.end(); it++)
        {
            cout << it->first << endl;
        }
    }

    return 0;
}