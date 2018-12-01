
#ifndef __data_hpp__
#define __data_hpp__

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

class Data
{
private:
  string class_attr, pos_val, neg_val;
  int size;

  vector<vector<string>> table;
  vector<string> table_attrs;

  // stores the attributes to ignore
  vector<string> ignores;

  // quick info variables
  // doesn't include class_attr and ignores
  vector<string> attrs;
  map<string, set<string>> unique_values; // stores different types of values
  map<string, multiset<string>> values;
  map<string, map<string, multiset<string>>> outcomes;

public:
  string filename;
  // string class_col, identifier;
  // vector<string> attr;
  //
  // map<string, set<string>> unique_value;
  //
  // map<string, multiset<string>> value;
  // map<string, map<string,multiset<string>>> outcome;
  //
  // vector<vector<string>> table;
  //
  // float set_entropy;
  // map<string, map<string, float>> entropy;
  // map<string, float> gain;
  //
  // string pos,neg;
  // int size;

  Data(string class_attr, string pos_val, string neg_val);

  void build();

  void read_table(string filename);
  // void read_test_table(string filename);
  void print_table();
  void print_attrs();
  void generate_table(Data *data, string attr, string value);

  float get_set_entropy(string *decider);
  float get_entropy(string attribute, string value);
  float get_max_gain(float set_entropy);
  float get_max_gain(float set_entropy, string *deciding_attribute);

  void ignore(string attr);
  void set_table(vector<vector<string>> table);

  map<string, set<string>> *get_unique_values();
  set<string> *get_unique_values(string attr);
  vector<string> *get_ignores();

  void set_table_attrs(vector<string> table_attrs);
  void set_size(int size);

  string get_class_attr();
  string get_pos_val();
  string get_neg_val();

  vector<vector<string>> *get_table();
  vector<vector<string>> get_test_table();
  vector<string> get_test_attrs();

  vector<string> get_table_attrs();

};



#endif
