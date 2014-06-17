#include <iostream>
#include <ctime>
#include <utility>
#include "GrafMacierz.h"
#include "Kruskal.h"
#include <fstream>

using namespace std;

int main() {
srand(time(NULL));
std::vector<pair<unsigned int, unsigned int> > Drzewo_Rozpinajace;
Graf_Macierz_Sasiedztwa graf(10,20);
Algorytm_Kruskala(graf, Drzewo_Rozpinajace);
return 0;
}
