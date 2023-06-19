#pragma once
#include <vector>

using namespace std;

class Node
{
public:
    int id;                         // ID vrcholu
    vector<Node*> sousedi;          // Seznam soused�
    bool projity_soused = false;    // pomocn� prom�n� typu bool
    bool visited = false;
    bool dist_visited = false;
     /**
     * @brief Konstruktor pro inicializaci vrcholu s dan�m ID.
     * @param Id ID vrcholu
     */
    Node(int Id) : id(Id) {}

    /**
    * @brief Z�sk� sousedy vrcholu.
    */
    void get_neighbors();

    /** 
    * @brief Fuknce pro nastaven� kapacity sousedsk�ho vektoru
    * , p�i dal��m zavol�n� se nastav� nov� kapacita
    */
    void setNeighborCapacity(size_t capacity) { sousedi.reserve(capacity); }
};

