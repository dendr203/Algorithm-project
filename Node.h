#pragma once
#include <vector>

using namespace std;

class Node
{
public:
    int id;                         // ID vrcholu
    vector<Node*> sousedi;          // Seznam sousedù
    bool projity_soused = false;    // pomocná promìná typu bool
    bool visited = false;
    bool dist_visited = false;
     /**
     * @brief Konstruktor pro inicializaci vrcholu s daným ID.
     * @param Id ID vrcholu
     */
    Node(int Id) : id(Id) {}

    /**
    * @brief Získá sousedy vrcholu.
    */
    void get_neighbors();

    /** 
    * @brief Fuknce pro nastavení kapacity sousedského vektoru
    * , pøi dalším zavolání se nastaví nová kapacita
    */
    void setNeighborCapacity(size_t capacity) { sousedi.reserve(capacity); }
};

