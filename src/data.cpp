
#include "Data.hpp"

Data::Data(string class_attr, string pos_val, string neg_val)
{
  this->class_attr = class_attr;
  this->pos_val = pos_val;
  this->neg_val = neg_val;

  size = 0;
}

void Data::build(){
  // get only attrs used in decision tree
  for(string a : table_attrs)
  {
    if(a == class_attr || find(ignores.begin(), ignores.end(), a) != ignores.end())
      continue;
    attrs.push_back(a);
  }

  // find class_attr in table_attrs
  ptrdiff_t pos = distance(table_attrs.begin(),
                  find(table_attrs.begin(), table_attrs.end(), class_attr));
  if(pos >= table_attrs.size())
  {
    // NOT FOUND
    cout << "class attribute not found in table!";
    exit(EXIT_FAILURE);
  }

  // insert values and outcomes into respective maps
  for(int r = 0; r < table.size(); r++)
  {
    vector<string> row = table[r];

    for(int c = 0; c < row.size(); c++)
    {
      string attr = table_attrs[c];
      string value = row[c];
      if(class_attr == attr ||
        (find(ignores.begin(), ignores.end(), attr) != ignores.end()))
        continue;

      values[attr].insert(value);
      unique_values[attr].insert(value);
      outcomes[attr][value].insert(row[pos]);
    }
  }
}

void Data::read_table(string filename)
{
  this->filename = filename;
  ifstream table_file(filename);

  char c;
  string word = "";
  bool first = true;
  vector<string> row;

  while((c = table_file.get()) != EOF)
  {
    if(c == '\n' || c == ',')
    {

      if(first)
      {
        table_attrs.push_back(word);
        if(c == '\n')
        {
          first = false;
        }
      }
      else
      {
        row.push_back(word);
        if(c == '\n') // end row
        {
          table.push_back(row);
          row.clear();
          size++;
        }
      }

      word = "";
    }
    else if(c != '\r' && c != ' ')
    {
      word += c;
    }
  }

  table_file.close();
}

// void Data::read_test_table(string filename)
// {
//
//   this->filename = filename;
// }

void Data::print_table()
{
  for(string a : table_attrs)
  {
    cout << a << ",";
  }
  cout << endl;
  for(vector<string> row : table)
  {
    for(string c : row)
    {
      cout << c << ",";
    }
    cout << endl;
  }
}

void Data::print_attrs()
{
  cout << "table attrs" << endl;
  for(string a : table_attrs)
  {
    cout << a << ",";
  }

  cout << endl << "calc attrs" << endl;
  for(string a : attrs)
  {
    cout << a << ",";
  }
  cout << endl;
}

void Data::generate_table(Data *data, string attr, string value)
{
  vector<vector<string>> new_table;
  int new_size = 0;

  ptrdiff_t a_pos = distance(table_attrs.begin(),
    find(table_attrs.begin(), table_attrs.end(), attr));

  if(a_pos >= table_attrs.size())
  {
    cout << "function: Data::generate_table(), attribute not found" << endl;
    exit(EXIT_FAILURE);
  }

  for(int r = 0; r < table.size(); r ++)
  {
    vector<string> row = table[r];

    if(row[a_pos] == value)
    {
      row.erase(row.begin() + a_pos);
      new_table.push_back(row);
      new_size++;
    }
  }

  data->set_table(new_table);

  vector<string> new_table_attrs = table_attrs;
  new_table_attrs.erase(new_table_attrs.begin() + a_pos);
  data->set_table_attrs(new_table_attrs);

  data->set_size(new_size);
}

float Data::get_set_entropy(string *decider)
{
  // find class_attr in table_attrs
  ptrdiff_t p = distance(table_attrs.begin(),
                  find(table_attrs.begin(), table_attrs.end(), class_attr));
  if(p >= table_attrs.size())
  {
    // NOT FOUND
    cout << "Function: Data::get_set_entropy(), class attribute not found in table!";
    exit(EXIT_FAILURE);
  }

  // get class values at given row
  multiset<string> class_vals;
  for(vector<string> row : table)
  {
    class_vals.insert(row[p]);
  }

  float pos = class_vals.count(pos_val);
  float neg = class_vals.count(neg_val);
  float total_size = class_vals.size();
  float pos_por = pos/total_size;
  float neg_por = neg/total_size;

  // cout << pos << endl << neg << endl << total_size << endl
  //   << pos_por << endl << neg_por << endl;

  if(pos_por == 0 || neg_por == 0)
  {
    *decider = (pos_por) ? pos_val : neg_val;
    return 0;
  }

  return -(pos_por * (log(pos_por)/log(2))) -
    (neg_por * (log(neg_por)/log(2)));
}

float Data::get_entropy(string attribute, string value)
{
  float pos = outcomes[attribute][value].count(pos_val);
  float neg = outcomes[attribute][value].count(neg_val);
  float total_size = outcomes[attribute][value].size();
  float pos_por = pos/total_size;
  float neg_por = neg/total_size;

  // cout << pos << endl << neg << endl << total_size << endl
  //   << pos_por << endl << neg_por << endl;

  if(pos_por == 0 || neg_por == 0)
  {
    // *decider = (pos_por) ? pos_val : neg_val;
    return 0;
  }

  float entropy = -(pos_por * (log(pos_por)/log(2))) -
    (neg_por * (log(neg_por)/log(2)));

  // cout << entropy << endl;

  return entropy;
}

float Data::get_max_gain(float set_entropy)
{

}

float Data::get_max_gain(float set_entropy, string *deciding_attribute)
{
  vector<float> gains;
  float gain = -1;
  for(string attribute : attrs)
  {
    gain = set_entropy;

    // cout << attribute << endl;

    for(string unique_value : unique_values[attribute])
    {
      // cout << unique_value << endl;
      gain -= ((float)outcomes[attribute][unique_value].size()/(float)size) * get_entropy(attribute, unique_value);
    }

    // cout << gain << endl;

    gains.push_back(gain);
  }
  if(gains.size() == 0)
  {
    return gain;
  }
  ptrdiff_t pos = max_element(gains.begin(), gains.end()) - gains.begin();
  *deciding_attribute = attrs[pos];
  return gains[pos];
}

void Data::ignore(string attr)
{
  ignores.push_back(attr);
}

void Data::set_table(vector<vector<string>> table)
{
  this->table = table;
}

void Data::set_table_attrs(vector<string> table_attrs)
{
  this->table_attrs = table_attrs;
}

void Data::set_size(int size)
{
  this->size = size;
}

map<string, set<string>> *Data::get_unique_values()
{
  return &unique_values;
}

set<string> *Data::get_unique_values(string attr)
{
  return &unique_values[attr];
}

vector<string> *Data::get_ignores()
{
  return &ignores;
}

string Data::get_class_attr()
{
  return class_attr;
}

string Data::get_pos_val()
{
  return pos_val;
}

string Data::get_neg_val()
{
  return neg_val;
}

vector<vector<string>> *Data::get_table()
{
  return &table;
}

vector<vector<string>> Data::get_test_table()
{
  vector<vector<string>> test_table;
  for(vector<string> row : table)
  {
    vector<string> test_row;
    for(int c = 0; c < row.size(); c ++)
    {
      if(table_attrs[c] == class_attr ||
        (find(ignores.begin(), ignores.end(), table_attrs[c])) != ignores.end())
        continue;
      test_row.push_back(row[c]);
    }
    test_table.push_back(test_row);
    // test_row.clear();
  }
  return test_table;
}

vector<string> Data::get_test_attrs()
{
  vector<string> attrs;
  for(string a : table_attrs)
  {
    if(a == class_attr ||
      (find(ignores.begin(), ignores.end(), a)) != ignores.end())
      continue;
      attrs.push_back(a);
  }
  return attrs;
}

vector<string> Data::get_table_attrs()
{
  return table_attrs;
}
