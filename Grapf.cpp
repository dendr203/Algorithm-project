#include "Grapf.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>

void Graf::addEdge(int from, int to)
{
    //nejprve se na vrchol from zavolá funkce FindOr...
    //pøedáme buï odkaz na nový vrchol, nebo na již stávající
    Node* node1 = findOrCreateNode(from);
    Node* node2 = findOrCreateNode(to);

    //vzájemné pøidání sousedù
    node1->sousedi.push_back(node2);
    node2->sousedi.push_back(node1);
    pocet_edges++;

    node1->setNeighborCapacity(node1->sousedi.size());  
    node2->setNeighborCapacity(node2->sousedi.size());
}

Node* Graf::findNode(int id)
{
    //vyhledání id v mapì nodes
    auto it = nodes.find(id);

    //jestli id v mapì existuje, tak se vrátí odkaz na Node*
    if (it != nodes.end())
    {
        return it->second;
    }
    //jesli id v mapì neexistuje, vrátí se nullptr
    return nullptr;
}

Node* Graf::findOrCreateNode(int id)
{
    //na id vrcholu se zavolá funkce pro zjištìní, jestli již vrchol existuje
    Node* node = findNode(id);

    //pokud id tedy neexistuje, vytvoøí se vrchol s pøíslušným ID a pøidá se do mapy
    if (node == nullptr)
    {
        node = new Node(id);
        nodes[id] = node;
        pocet_vrcholu++;
    }
    return node;
}

Graf::Graf(string nazev_souboru)
{
    ifstream soubor;
    soubor.open(nazev_souboru);

    if (!soubor.is_open())
    {
        cout << "Soubor nelze otevrit!!!" << endl;
        exit(1);
    }

    string line;
    int from, to;


    while (soubor >> from >> to)
    {
        addEdge(from, to);      //pøidání hran
    }

    soubor.close();
}

void Graf::getGraph()
{
    cout << "Pocet vrcholu v grafu: " << pocet_vrcholu << endl;
    cout << "Pocet spoju v grafu: " << pocet_edges << endl;
    cout << endl;
}

void Graf::findBiggestK()
{
    unordered_set<int> visited;                     //mapa pro uložení již projitých vrcholù
    visited.reserve(biggestK);
    int pocet_k = 0;
    Node* node;
    int komponenta = 0;

    for (auto& pair : nodes)                        //prùchod všech vrcholù
    {
        node = pair.second;
        if (visited.count(node->id) == 0)           //prošli jsme již vrchol?
        {
            komponenta = 0;
            dfs(node, visited, komponenta);         //prùchod do hloubky
            if (komponenta > biggestK)              //pokud je komponenta vìtší než pøedešle zjištìná
            {
                bigK = pair.second;                 //bigK bude uchovávat odkaz na vrchol v nejvìtší komponentì
                biggestK = komponenta;              //poèet vrcholù v nejvìtší komponentì
            }
            pocet_k++;                              
        }
    }
    cout << "Pocet komponent grafu: " << pocet_k << endl;
    cout << "Nejvetsi komponenta grafu: " << biggestK << endl;

    cout << "ID zacatku nej K: " << bigK->id << endl;
}

void Graf::dfs(Node* node, unordered_set<int>& visited, int& vzdalenost)
{
    stack<Node*> stack;
    stack.push(node);
    Node* node1;

    while (!stack.empty())
    {
        node1 = stack.top();
        stack.pop();

        if (visited.count(node1->id) != 0)
            continue;

        visited.insert(node1->id);
        vzdalenost++;
        biggest_V = max(biggest_V, node1->id);
        
        if (node1->sousedi.empty())
            continue;

        for (Node* soused : node1->sousedi)
        {
            if (visited.count(soused->id) == 0)
                stack.push(soused);
        }
    }
}




void Graf::calcAvgRad()
{
    queue<Node*> que;                                      
    unordered_map<int, int> distances;                      //mapa pro uchování vzdáleností

    Node* node;

    int excentricita = 0;
    que.push(bigK);
    long int citac = 0;
    ofstream Myfile("vystup.txt");


    while (!que.empty())
    {
        node = que.front();
        que.pop();




        calcDistance(node, distances, excentricita);        //zavolání funkce na jeden vrchol
        node->visited = true;
        Myfile << citac++ << endl;
        prumer = max(prumer, excentricita);                 //ovìøení, zda jsme našli vìtší prùmìr
        polomer = min(polomer, excentricita);               //ovìøení, zda jsme našli menší polomìr
        excentricita = 0;

        for (auto& soused : node->sousedi)                  //pøidání všech sousedù do stacku, ty co jsme již prošli, ne
        {
            if (soused->visited == 0)
            {
               
                que.push(soused);
            }
        }
    }

    cout << "Prumer: " << prumer << endl;
    cout << "Polomer: " << polomer << endl;

}

void Graf::calcDistance(Node* start, unordered_map<int, int>& distances, int& excentricita)
{
    unordered_set<int> visited;
    visited.reserve(biggestK);
    queue<Node*> q;
    Node* node;
    distances[start->id] = 0;                           //Nastavení startovního vrcholu na hodnotu 0


    q.push(start);

    while (!q.empty())
    {
        node = q.front();
        q.pop();

        for (Node* soused : node->sousedi)
        {
            if (visited.count(soused->id) == 0)                         //pokud jsme již vrchol neprošli 
            {
                
                visited.insert(soused->id);
                q.push(soused);
                distances[soused->id] = distances[node->id] + 1;                                  //pøidání hodnoty cesty
                excentricita = max(excentricita, distances[soused->id]);                          //jestli jsme našli vìtší 
            }
        }
        distances[node->id] = 0;
    }
}
