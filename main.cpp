#include <stdio.h>

#include <iostream>
// #include <algorithm>
// #include <iterator>

#include "Tree.hpp"
#include "Data.hpp"

#include <map>
#include<set>

using namespace std;

// Data * find_data(vector<Data> *data)
// {
//   auto data_iter = find_if(data->begin(), data->end(),
//     [](const Data* attr) -> bool
//     { return attr->attribute == "humidity"; });
//
//   // cout << distance(data.begin(), attr_iter);
//   if(data_iter != data->end())
//   {
//
//   }
//
//   // return &(data[0]);
// }

int main(int argc, char *argv[])
{
  // Tree tree("Should I play baseball?", "Yes", "No", "sets/baseball.csv");
  //
  // tree.ignore("Day");

  Tree tree("income", "<=50K", ">50K", "sets/adult.csv");

  tree.ignore("age");
  tree.ignore("fnlwgt");
  tree.ignore("education-num");
  tree.ignore("capital-gain");
  tree.ignore("capital-loss");
  tree.ignore("hours-per-week");


  // tree.print_table();

  tree.build_tree();

  // tree.print_attrs();

  // tree.print_tree();

  tree.list_paths();

	return 0;
}
