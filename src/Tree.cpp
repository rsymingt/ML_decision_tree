
#include "Tree.hpp"

Tree::Tree(string class_col)
{
  // root = new Node();
  data = new Data(class_col);
}

float Tree::get_entropy()
{

}

void Tree::build_branch()
{

}

void Tree::build_tree()
{
  data->setEntropy(); // set entropy for all attrs

  for(int i = 0; i < data->attr; i ++)
  {

  }

  // NEXT GET GAIN FOR EACH ATTRIBUTE, CHOOSE ROOT NODE AND TRAVERSE REPEAT
}

void Tree::print_data()
{
  for(string a : data->attr)
  {
    cout << a << " ";
  }
  for(vector<string> row : data->table)
  {
    for(string c : row)
    {
      cout << c << " ";
    }
    cout << endl;
  }
}

void Tree::build_data(string filename)
{
  ifstream data_file("sets/baseball.csv");
  char c;
  string word;
  bool first = true;
  int column = 0;
  vector<string> row;
  while((c = data_file.get()) != EOF)
  {
    switch(c)
    {
      case '\r':
        break;
      case '\n':
        if(word.length() > 0)
        {
          if(first)
          {
            if(word != data->class_col)
              row.push_back(word);
            data->attr = row;
          }
        }

        if(!first)
        {
          row.push_back(word);
          data->table.push_back(row);
          data->size++;
        }

        row.clear();

        word = "";
        first = false;
        column = 0;
        break;
      case ',':
        // cout << word << endl;
        if(word.length() > 0)
        {
          if(first)
          {
            row.push_back(word);
          }
        }

        if(!first)
        {
          row.push_back(word);
        }

        word = "";
        column ++;
        break;
      default:
        word += c;
        break;
    }
  }

  vector<string> class_col_values;

  for(int i = 0; i < data->table.size(); i ++)
  {
    class_col_values.push_back(data->table[i][data->table[i].size()-1]);
    data->value[data->class_col].insert(data->table[i][data->table[i].size()-1]);
  }

  for(int i = 0; i < data->attr.size(); i++)
  {
    for(int r = 0; r < data->table.size(); r ++)
    {
      data->value[data->attr[i]].insert(data->table[r][i]);
      data->unique_value[data->attr[i]].insert(data->table[r][i]);

      if(data->attr[i] != data->class_col) // dont insert outcome of the outcome
        data->outcome[data->attr[i]][data->table[r][i]].insert(class_col_values[r]);
    }
  }
}
