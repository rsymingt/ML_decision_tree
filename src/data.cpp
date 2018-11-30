
#include "Data.hpp"

Data::Data(string class_col, string identifier)
{
  this->class_col = class_col;
  this->identifier = identifier;

  pos = "Yes";
  neg = "No";
  size = 0;
}

void Data::setEntropy()
{
  //get entropy of the set first

  // retrieve values for class set
  multiset<string> class_set = this->value[this->class_col];

  float pos = class_set.count(this->pos);
  float neg = class_set.count(this->neg);
  float total_size = class_set.size();
  float pos_por = pos/total_size;
  float neg_por = neg/total_size;

  set_entropy = -(pos_por*(log(pos_por)/log(2))) - (neg_por*(log(neg_por)/log(2)));

  for(int i = 0; i < attr.size(); i ++)
  {
    string attr = this->attr[i];
    // cout << attr << endl;

    set<string> values = unique_value[attr];
    for(string v : values)
    {
      pos = outcome[attr][v].count(this->pos);
      neg = outcome[attr][v].count(this->neg);
      total_size = value[attr].count(v);
      pos_por = pos/total_size;
      neg_por = neg/total_size;

      // cout << pos << endl;
      // cout << neg << endl;
      // cout << total_size << endl;
      // cout << pos_por << endl;
      // cout << neg_por << endl;

      if(pos == 0)
      {
        this->entropy[attr][v] = 0;
      }
      else if(neg == 0)
      {
        this->entropy[attr][v] = 0;
      }
      else
      {
        this->entropy[attr][v] = -(pos_por*(log(pos_por)/log(2))) - (neg_por*(log(neg_por)/log(2)));
      }

      // cout << "ENTROPY: " << this->entropy[attr][v] << endl;
    }
  }
}

void Data::setGain()
{
  for(int i = 0; i < this->attr.size(); i ++)
  {
    string attr = this->attr[i];
    float gain = set_entropy;
    set<string> values = unique_value[attr];

    for(string v : values)
    {
      gain -= ((float)value[attr].count(v)/(float)size)*entropy[attr][v];
    }

    this->gain[attr] = gain;
  }
}

float Data::getGain(string attr)
{

  return gain[attr];
}
