#include "Node_Class.h"
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
using namespace std;

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

            if(regex_search(myline, m, std::regex("^.* ")))
            {
                cout << m[0] << " ";
            }

            if(regex_search(myline, m, regex(" .*")))
            {
                cout << m[0] << endl;
            }
        }
        
    }

    return 0;
}
