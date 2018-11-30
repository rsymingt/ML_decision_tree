
#ifndef __tree_hpp_
#define __tree_hpp_

#include <fstream>

#include "Node.hpp"
#include "Data.hpp"

class Tree
{
private:
  Node *root;
  Data *data;
  Data *class_attr;

  float get_entropy();
  void build_branch();

public:
  Tree(string class_col, string identifier);
  void build_data(string file_name);
  void print_data();
  void build_branches(vector<string> attr);

  void build_tree();
};

#endif
