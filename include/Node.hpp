
#ifndef __node_hpp__
#define __node_hpp__

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Node
{
private:
  string attribute;
  // vector<string> values;
  // vector<Node> nodes;
public:
  Node(string attribute);
  void link(string value, string attribute)
  {

  }
};

#endif
