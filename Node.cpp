#include "Node.h"
#include <iostream>

using namespace std;

void Node::get_neighbors()
{
    for (auto& soused : sousedi)
    {
        cout << soused->id;
    }
}