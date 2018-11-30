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
  Tree tree("Should I play baseball?");

  tree.build_data("sets/baseball.csv");
  // tree.print_data();
  tree.build_tree();

  // tree.print_data();

	return 0;
}
