
#include "Node.hpp"

Node::Node(string key)
{
  this->key = key;
}

Decider::Decider(string key, string outcome) : Node(key)
{
  this->outcome = outcome;
}

Attribute::Attribute(string key) : Node(key)
{

}

string Node::get_key()
{
  return key;
}

int Node::identify()
{
  return NODE;
}

int Decider::identify()
{
  return DECIDER;
}

int Attribute::identify()
{
  return ATTRIBUTE;
}
