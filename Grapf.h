#pragma once
#include <unordered_map>
#include <unordered_set>
#include <climits>

#include "Node.h"


using namespace std;

class Graf
{
public:
    unordered_map<int, Node*> nodes;                // ID, vrchol
    int pocet_vrcholu = 0;
    int pocet_edges = 0;
    int biggestK = 0;                               // poèet vrcholù nejvìtší komponenty
    int prumer = 0;
    int biggest_V = 0;                              // nejvìtší vrchol nejvìtší komponenty
    int polomer = INT_MAX;
    Node* bigK = nullptr;                           // pointer na vrchol nejvìtší komponenty


    /**
    * @brief Konstruktor grafu, je zde nahrání do pamìti
    */
    Graf(string nazev_souboru);

    /**
    * @brief Pøidání hrany
    * @param from = odkud hrana jde
    * @param to = kam vede
    */
    void addEdge(int from, int to);

    /**
    * @brief Ovìøení, zda se musí vrchol vytvoøit
    */
    Node* findOrCreateNode(int id);

    /**
    * @brief Nalezení vrcholu podle id
    */
    Node* findNode(int id);

    /**
    * @brief Vypíše vlastnosti grafu
    */
    void getGraph();

    /**
    * @brief Vyhledá nejvìtší komponentu grafu
    */
    void findBiggestK();

    /**
    * @brief Vyhledávání v grafu do hloubky
    * @param node je vrchol, ze kterého prohledáváme graf
    * @param visited je mapa, která si uchovává vrcholy, které jsme již prošli
    * @param vzdálenost je vzdálenost
    */
    void dfs(Node* node, unordered_set<int>& visited, int& vzdalenost);

    /**
    * @brief funkce pro výpoèet prùmìru a polomìru nejvìtší komponenty
    */
    void calcAvgRad();

    /**
    * @brief funkce pro výpoèet vzdáleností pomocí BFS
    * @param node je vrchol pro který budeme vyhledávat excentricitu
    * @param distances je mapa pro uchování vrcholù, které jsme již prošli
    * @param excentricita je exentricita
    */
    void calcDistance(Node* node, unordered_map<int, int>& distances, int& excentricita);

};
