
#ifndef __node_hpp__
#define __node_hpp__

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "data.hpp"

#define NODE 0
#define DECIDER 1
#define ATTRIBUTE 2

using namespace std;

class Node
{
protected:
  string key;
  // vector<string> values;
  // vector<Node> nodes;
public:
  Node(string key);
  string get_key();
  virtual int identify();
};

class Decider : public Node{
private:
  string outcome;
public:
  Decider(string key, string outcome);
  int identify();
};

class Attribute : public Node{
private:
public:
  map<string, Node*> nodes;
  Data *data;

  Attribute(string key);
  int identify();
};

#endif
