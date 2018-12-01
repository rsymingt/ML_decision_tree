
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

  Node *build_branches(Data *data);
  void print_tree(Node *root);
  void list_paths(Node *root, string path);

public:
  Tree(string class_attr, string pos_val, string neg_val, string filename);

  void ignore(string ignore);

  void print_table();
  void print_attrs();
  void print_tree();

  void list_paths();

  void build_data(string file_name);
  void print_data();

  void build_tree();

  string decide_row(vector<string> attrs, vector<string> row, Node *root);

  vector<string> test_data(Data *test_data);
};

#endif
