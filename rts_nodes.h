#ifndef RTS_NODES
#define RTS_NODES
#include "Node_Class.h"
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

const string WHITESPACE = " \n\r\t\f\v";


void generateList(list<Node> &masterList);
void SetDependentNode(Node parent, Node child, list<Node> &masterList);
void menu(list<Node> &masterList);
string ltrim(const string &s);
string rtrim(const string &s);
string trim(const string &s);

    

#endif