
#include "Tree.hpp"

Tree::Tree(string class_attr, string pos_val, string neg_val, string filename)
{
  // root = new Node();
  data = new Data(class_attr, pos_val, neg_val);
  data->read_table(filename);
}

void Tree::ignore(string ignore)
{
  data->ignore(ignore);
}

void Tree::print_attrs()
{
  data->print_attrs();
}

void Tree::print_table()
{
  data->print_table();
}

void Tree::print_tree(Node *root)
{
  if(root == NULL)
  {
    cout << "NULL" << endl;
    return;
  }
  if(root->identify() == DECIDER)
  {
      // do something with moveable_john
      cout << "DECISION: " <<  root->get_key() << endl << endl;
      return;
  }

  Attribute *attribute_node = static_cast<Attribute*>(root);

  string current_attr = attribute_node->get_key();

  set<string> *unique_values = attribute_node->data->get_unique_values(current_attr);

  cout << "attribute: " << current_attr << endl;

  for(string unique_value : *unique_values)
  {
    cout << "value: " << unique_value << endl;
    print_tree(attribute_node->nodes[unique_value]);
  }

  // cout << current_attr << endl;
}

string Tree::decide_row(vector<string> attrs, vector<string> row, Node *root)
{
  if(root == NULL)
  {
    return "NULL";
  }
  if(root->identify() == DECIDER)
  {
    return root->get_key();
  }

  Attribute *attr_node = static_cast<Attribute*>(root);

  string current_attr = attr_node->get_key();

  ptrdiff_t a = distance(attrs.begin(),
    find(attrs.begin(), attrs.end(), current_attr));

  if(a >= attrs.size())
  {
    // didnt find
    return "NOT FOUND";
  }

  string value = row[a];

  return decide_row(attrs, row, attr_node->nodes[value]);
}

void Tree::list_paths(Node *root, string path)
{
  if(root == NULL)
  {
    // cout << "NULL" << endl;
    return;
  }
  if(root->identify() == DECIDER)
  {
      // do something with moveable_john
      cout << path << " = " <<  root->get_key() << endl << endl;
      return;
  }

  Attribute *attribute_node = static_cast<Attribute*>(root);

  string current_attr = attribute_node->get_key();

  set<string> *unique_values = attribute_node->data->get_unique_values(current_attr);

  path += current_attr + "-->";

  for(string unique_value : *unique_values)
  {
    // path += unique_value + "  ";
    list_paths(attribute_node->nodes[unique_value], path + unique_value + "  ");
  }
}

void Tree::list_paths()
{
  list_paths(root, "");
}

void Tree::print_tree()
{
  print_tree(root);
}

Node *Tree::build_branches(Data *data)
{
  // CALCULATE SET ENTROPY
  string decider;
  float entropy = data->get_set_entropy(&decider);
  if(entropy == 0) // all pos or neg
  {
    // cout << "DECISION: " << decider << endl;
    //CREATE AND RETURN A DECIDER NODE
    return new Decider(decider, decider);
  }

  // cout << entropy << endl;

  // CALCULATE MAX GAIN
  string attribute;
  float gain = data->get_max_gain(entropy, &attribute);

  // cout << "attribute: " << attribute << endl;

  if(gain == -1)
  {
    // cout << "DECISION: " << "Not Sure" << endl;
    // run out of attributes NOT SURE WHAT TO DO HERE
    return new Decider("Not Sure", "Not Sure");
  }
  // IF MAX GAIN IS -1 OR NO ATTRIBUTE THEN WERE DONE

  // OTHERWISE USE GAIN ATTRIBUTE IN ROOT AND BUILD NEW DATA FOR EACH VALUE
  // IN ATTRIBUTE THEN SEND RECURSIVELY

  Attribute *root = new Attribute(attribute);
  root->data = data;

  for(string unique_value : (*(data->get_unique_values()))[attribute])
  {
    // cout << "value: " << unique_value << endl;

    Data *new_data = new Data(data->get_class_attr(), data->get_pos_val(),
      data->get_neg_val());

    for(string ignore : *(data->get_ignores()))
      new_data->ignore(ignore);

    data->generate_table(new_data, attribute, unique_value);

    // new_data->print_table();

    new_data->build();

    root->nodes[unique_value] = build_branches(new_data);

    // delete new_data;
  }

  return root;
}

void Tree::build_tree()
{
  data->build();
  root = build_branches(data);
}

void Tree::print_data()
{
}

vector<string> Tree::test_data(Data *test_data)
{
  vector<vector<string>> test_table = test_data->get_test_table();
  vector<string> test_attrs = test_data->get_test_attrs();

  // for(string a : test_attrs)
  //   cout << a << ",";
  // cout << endl;

  vector<string> answer;
  for(vector<string> row : test_table)
  {
    answer.push_back(decide_row(test_attrs, row, root));
  }
  return answer;
}
