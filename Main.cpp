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
    list<Node> masterList; 

    ifstream myfile;

    //fill masterList
    generateList(masterList);

    //open menu window
    menu(masterList);

    return 0;
}