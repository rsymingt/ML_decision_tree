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

  Data *test_data = new Data("income", "<=50K", ">50K");
  test_data->ignore("age");
  test_data->ignore("fnlwgt");
  test_data->ignore("education-num");
  test_data->ignore("capital-gain");
  test_data->ignore("capital-loss");
  test_data->ignore("hours-per-week");
  test_data->read_table("sets/adult-test.csv");

  // vector<vector<string>> test_table = test_data->get_test_table();
  //
  // for(vector<string> row : test_table)
  // {
  //
  //   for(string c : row)
  //   {
  //     cout << c << ",";
  //   }
  //   cout << endl;
  // }

  vector<string> predictions = tree.test_data(test_data);
  vector<vector<string>> *table = test_data->get_table();
  vector<string> attrs = test_data->get_table_attrs();

  ofstream ofile;
  ofile.open("sets/adult-test-tested.csv");

  for(int a = 0; a < attrs.size(); a ++)
  {
    // if(a != attrs.size()-1)
      ofile << attrs[a] << ",";
    // else
      // ofile << attrs[a];
  }

  ofile << "guess\n";

  for(int r = 0; r < (*table).size(); r ++)
  {
    vector<string> row = (*table)[r];

    for(string c : row)
    {
      ofile << c << ",";
    }
    ofile << predictions[r] << "\r\n";
  }

  ofile.close();

  // tree.print_attrs();

  // tree.print_tree();

  // tree.list_paths();

	return 0;
}
