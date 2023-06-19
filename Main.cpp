#include <iostream>
#include <chrono>

#include "Grapf.h"
#include "Node.h"

using namespace std;


int main(int argc, char** args)
{

    auto start = chrono::high_resolution_clock::now(); // Zaèátek mìøení èasu
    Graf* g = new Graf("Graf_m.txt");
    auto end = chrono::high_resolution_clock::now(); // Konec mìøení èasu
    chrono::duration<double> duration = end - start;
    cout << "Cas nacitani: " << duration.count() << " sekundy" << endl;

    g->getGraph();

    auto start1 = chrono::high_resolution_clock::now();
    g->findBiggestK();
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration1 = end1 - start1;
    cout << "Cas nejvetsi komponenty: " << duration1.count() << " sekundy" << endl;
    cout << endl;

    auto start2 = chrono::high_resolution_clock::now();
    g->calcAvgRad();
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration2 = end2 - start2;
    cout << "Cas prumeru a polomeru: " << duration2.count() << " sekundy" << endl;

    delete g;
    return 0;
}