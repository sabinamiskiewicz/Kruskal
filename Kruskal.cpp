#include <vector>
#include <utility>
#include <list>
#include <tuple>
#include "GrafMacierz.h"
#include "Kruskal.h"

using namespace std;

void Algorytm_Kruskala(Graf_Macierz_Sasiedztwa& graf,vector< pair<unsigned int,unsigned int> >&Drzewo_Rozpinajace)
{
	//zmienne pomocnicze sluzace do wykrywania czy wierzcholki
	//z krawedzi ktora chcemy dodac do zbioru rozwiazan znajduja sie
	//juz w tym zbiorze
bool znaleziono1=false,znaleziono2=false;
	//Lista wszystkich krawedzi znajdujacych sie w grafie.
list<tuple<unsigned int,unsigned int,unsigned int> >Krawedzie;
	//Zbior rozlacznych poddrzew tworzonych podczas szukania
	//drzewa rozpinajacego graf.
vector<vector<unsigned int> > Male_Drzewa;
	//Uzupelnienie listy zawierajacej wszystkie krawedzie w grafie.
for(unsigned int i=0;i<graf.liczba_wierzcholkow;i++)
	for(unsigned int j=0;j<graf.liczba_wierzcholkow;j++)
		{
		znaleziono1=false;
		for(list<tuple<unsigned int,unsigned int,unsigned int> >::iterator it=Krawedzie.begin();
			it!=Krawedzie.end() && znaleziono1==false;it++)
					//Sprawdzenie czy krawedz zostala juz dodana do listy.
		if((*it)==tuple<unsigned int,unsigned int,unsigned int>
			(graf.Macierz_Sasiedztwa[i][j],j,i))
			znaleziono1=true;
			//Jesli krawedzi nie ma w liscie to jest do niej dodawana.
		if(i!=j && graf.Macierz_Sasiedztwa[i][j] && !znaleziono1)
			 Krawedzie.push_back((tuple<unsigned int,unsigned int,unsigned int>
			 	(graf.Macierz_Sasiedztwa[i][j],i,j)));
		}
	//Sort listy zawierajacej krawedzi w kolejnosci rosnacej.
Krawedzie.sort();
	//Petla glowna trwajaca dopoki nie utworzone drzewo rozpinajace graf.
while(Drzewo_Rozpinajace.size()<graf.liczba_wierzcholkow-1)
	{
	znaleziono1=false;
	znaleziono2=false;
	unsigned int i,j,drzewo_1=0,drzewo_2=0;
		//Przeszukiwanie utworzonych poddrzew
	for(i=0;(i<Male_Drzewa.size()) && (!znaleziono1 || !znaleziono2);i++)
		{
		for(j=0;(j<Male_Drzewa[i].size()) && (!znaleziono1 || !znaleziono2);j++)
			{
				//Jesli element ze sprawdzanej krawedzi znajduje sie
				//w jakims z poddrzew, miejsce to jest oznaczane.
			if(get<1>(Krawedzie.front())==Male_Drzewa[i][j])
				{
				znaleziono1=true;
				drzewo_1=i;
				}
			if(get<2>(Krawedzie.front())==Male_Drzewa[i][j])
				{
				znaleziono2=true;
				drzewo_2=i;
				}
			}
		}
		//Jesli znaleziono oba z elementow krawedzi
if(znaleziono1 && znaleziono2)
	{
	//Jesli sa to rozne drzewa
	if(drzewo_1!=drzewo_2)
		{
					//drzewa sa ze soba scalane w jedno
		Male_Drzewa[drzewo_1].push_back(get<2>(Krawedzie.front()));
		while(!Male_Drzewa[drzewo_2].empty())
			{
			Male_Drzewa[drzewo_1].push_back(Male_Drzewa[drzewo_2].back());
			Male_Drzewa[drzewo_2].pop_back();
			}
		}
	}
		//Jesli elementy krawedzi nie znajduja sie w zadnym
		//poddrzewie
if(!znaleziono1 && !znaleziono2)
	{
			//Dodawane jest nowe poddrzewo zawierajace ta krawedz
	Male_Drzewa.push_back(vector<unsigned int>());
	Male_Drzewa.back().push_back(get<2>(Krawedzie.front()));
	Male_Drzewa.back().push_back(get<1>(Krawedzie.front()));
	}
else
	{
			//Jesli znaleziono tylko jeden element, drugi z elementow
			//przylaczany jest do istniejacego poddrzewa.
	if(znaleziono1)
		Male_Drzewa[drzewo_1].push_back(get<2>(Krawedzie.front()));
	else
		Male_Drzewa[drzewo_2].push_back(get<1>(Krawedzie.front()));
	}
		//Jesli obu elementow krawedzi nie ma w tym samym poddrzewie
		//Krawedz dodawana jest do drzewa rozpinajacego.
if(!(znaleziono1 && znaleziono2 && drzewo_1==drzewo_2))
	Drzewo_Rozpinajace.push_back(pair<unsigned int,unsigned int>
		(get<1>(Krawedzie.front()),get<2>(Krawedzie.front())));
		//Przejscie do nastepnej krawedzi.
	Krawedzie.pop_front();
	}
}