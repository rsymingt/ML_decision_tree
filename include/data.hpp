
#ifndef __data_hpp__
#define __data_hpp__

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>

using namespace std;

class Data
{
private:

  // string attribute;
  // vector<string> values;
  // map<string, int> value_map;
  // vector<float> entropy;
  // int size;

public:
  string class_col;
  vector<string> attr;

  map<string, set<string>> unique_value;

  map<string, multiset<string>> value;
  map<string, map<string,multiset<string>>> outcome;

  vector<vector<string>> table;

  float set_entropy;
  map<string, map<string, float>> entropy;

  string pos,neg;
  int size;

  Data(string class_col);
  void setEntropy();
  string getGain(string attribute);
};

#endif
