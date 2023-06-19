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
    int biggestK = 0;                               // po�et vrchol� nejv�t�� komponenty
    int prumer = 0;
    int biggest_V = 0;                              // nejv�t�� vrchol nejv�t�� komponenty
    int polomer = INT_MAX;
    Node* bigK = nullptr;                           // pointer na vrchol nejv�t�� komponenty


    /**
    * @brief Konstruktor grafu, je zde nahr�n� do pam�ti
    */
    Graf(string nazev_souboru);

    /**
    * @brief P�id�n� hrany
    * @param from = odkud hrana jde
    * @param to = kam vede
    */
    void addEdge(int from, int to);

    /**
    * @brief Ov��en�, zda se mus� vrchol vytvo�it
    */
    Node* findOrCreateNode(int id);

    /**
    * @brief Nalezen� vrcholu podle id
    */
    Node* findNode(int id);

    /**
    * @brief Vyp�e vlastnosti grafu
    */
    void getGraph();

    /**
    * @brief Vyhled� nejv�t�� komponentu grafu
    */
    void findBiggestK();

    /**
    * @brief Vyhled�v�n� v grafu do hloubky
    * @param node je vrchol, ze kter�ho prohled�v�me graf
    * @param visited je mapa, kter� si uchov�v� vrcholy, kter� jsme ji� pro�li
    * @param vzd�lenost je vzd�lenost
    */
    void dfs(Node* node, unordered_set<int>& visited, int& vzdalenost);

    /**
    * @brief funkce pro v�po�et pr�m�ru a polom�ru nejv�t�� komponenty
    */
    void calcAvgRad();

    /**
    * @brief funkce pro v�po�et vzd�lenost� pomoc� BFS
    * @param node je vrchol pro kter� budeme vyhled�vat excentricitu
    * @param distances je mapa pro uchov�n� vrchol�, kter� jsme ji� pro�li
    * @param excentricita je exentricita
    */
    void calcDistance(Node* node, unordered_map<int, int>& distances, int& excentricita);

};
