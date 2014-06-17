#include "GrafMacierz.h"
#include "time.h"
#include <cstdlib>
#include <vector>
#include <utility>
#include <tuple>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Graf_Macierz_Sasiedztwa::Graf_Macierz_Sasiedztwa(unsigned int l_wierzcholkow,
		unsigned int l_krawedzi) {
liczba_krawedzi = l_krawedzi;
liczba_wierzcholkow = l_wierzcholkow;
unsigned int pomocnicza1 = 0;
unsigned int pomocnicza2 = 0;
unsigned int pomocnicza3 = 0;
unsigned int waga;
	//Jesli graf jest pelny, wykorzystywany jest prostszy algorytm wypelniania grafu.
if (l_krawedzi >= l_wierzcholkow * (l_wierzcholkow - 1) / 2) {
	for (unsigned int i = 0; i < l_wierzcholkow; i++) {
		Macierz_Sasiedztwa.push_back(std::vector<unsigned int>());
		for (unsigned int j = 0; j < l_wierzcholkow; j++)
			Macierz_Sasiedztwa[i].push_back(rand() % 100 + 1);
		}
	} 
else {
		//Stworzenie listy zawierajacej wszystkie mozliwe krawedzi w grafie.
	vector<tuple<unsigned int, unsigned int, unsigned int> > Macierz_krawedzi;
	for (int j = 0; j < l_wierzcholkow; j++)
		for (int i = 0; i < l_wierzcholkow; i++) 
			{
			Macierz_krawedzi.push_back(tuple<unsigned int, unsigned int, unsigned int>());
			get < 0 > (Macierz_krawedzi[j*liczba_wierzcholkow +i]) = rand() % 100 +1;
			get < 1 > (Macierz_krawedzi[j*liczba_wierzcholkow +i]) = j;
			get < 2 > (Macierz_krawedzi[j*liczba_wierzcholkow +i]) = i;
			}
		//Zaalokowanie macierzy sasiedztwa;
		for (unsigned int j = 0; j < l_wierzcholkow; j++) {
			Macierz_Sasiedztwa.push_back(std::vector<unsigned int>());
			for (unsigned int i = 0; i < l_wierzcholkow; i++)
				(Macierz_Sasiedztwa[j]).push_back(0);
		}
std::vector<unsigned int> Lista_Spojnosci;
std::vector<unsigned int> Lista_Wierzcholkow;
		//Zapelnienie listy wierzcholkow do wstawienia
		//do generowanego grafu spojnego
for (unsigned int j = 0; j < liczba_wierzcholkow; j++)
	Lista_Wierzcholkow.push_back(j);
	pomocnicza1 = rand() % Lista_Wierzcholkow.size();
	Lista_Spojnosci.push_back(Lista_Wierzcholkow[pomocnicza1]);
	Lista_Wierzcholkow[pomocnicza1] = Lista_Wierzcholkow.back();
	Lista_Wierzcholkow.pop_back();
		//Petla trwajaca dopoki lista wierzcholkow bêd¹cych poza grafem
		//nie bêdzie pusta. Zapewnienie spójnosci grafu.
	while (!Lista_Wierzcholkow.empty()) 
		{
		pomocnicza1 = rand() % Lista_Wierzcholkow.size();
		pomocnicza2 = rand() % Lista_Spojnosci.size();
		waga = rand() % 100 + 1;
		Macierz_Sasiedztwa[Lista_Spojnosci[pomocnicza2]][Lista_Wierzcholkow[pomocnicza1]] = waga;
		Macierz_Sasiedztwa[Lista_Wierzcholkow[pomocnicza1]][Lista_Spojnosci[pomocnicza2]] = waga;
		Lista_Spojnosci.push_back(Lista_Wierzcholkow[pomocnicza1]);
		Lista_Wierzcholkow[pomocnicza1] = Lista_Wierzcholkow.back();
		Lista_Wierzcholkow.pop_back();
		}
		//Wypenianie grafu dopoki nie osiagnie sie wymaganej gestosci grafu.
	for (unsigned int j = 0; j < l_krawedzi - l_wierzcholkow; j++) {
		do 
			{
			pomocnicza3 = rand() % Macierz_krawedzi.size();
			pomocnicza1 = get<1>(Macierz_krawedzi[pomocnicza3]);
			pomocnicza2 = get<2>(Macierz_krawedzi[pomocnicza3]);
			waga = get<0>(Macierz_krawedzi[pomocnicza3]);
			} 
		while (Czy_Jest_Krawedz(pomocnicza1, pomocnicza2) || pomocnicza1 == pomocnicza2);
			//Wierzcho³ki mog¹ byæ skierowane do siebie ale nie musz¹.
		Macierz_Sasiedztwa[pomocnicza1][pomocnicza2] = waga;
		Macierz_Sasiedztwa[pomocnicza2][pomocnicza1] = waga;
		Macierz_krawedzi[pomocnicza3]=Macierz_krawedzi.back();
		Macierz_krawedzi.pop_back();
		}
	}
}
void Graf_Macierz_Sasiedztwa::Zapisz_do_pliku(const char* nazwa) 
{
ofstream Plik(nazwa);
for (unsigned int i = 0; i < liczba_wierzcholkow; i++) 
	{
	for (unsigned int j = 0; j < liczba_wierzcholkow; j++)
		Plik << Macierz_Sasiedztwa[i][j] << " ";
		Plik << std::endl;
	}
}
Graf_Macierz_Sasiedztwa::Graf_Macierz_Sasiedztwa(const char* nazwa) 
{
ifstream Plik(nazwa);
unsigned int pomocnicza;
string linia;
while (!Plik.eof()) 
	{
	getline(Plik, linia);
	istringstream bufor(linia);
	if (!Plik.eof()) 
		{
		Macierz_Sasiedztwa.push_back(vector<unsigned int>());
		while (!bufor.eof()) 
			{
			bufor >> pomocnicza;
			if (!bufor.eof()) 
				{
				Macierz_Sasiedztwa.back().push_back(pomocnicza);
				if (pomocnicza)
					liczba_krawedzi++;
				}
			}
		}
	}
liczba_wierzcholkow = Macierz_Sasiedztwa.size();
}
void operator <<(std::ostream& StrWy, Graf_Macierz_Sasiedztwa& Graf) 
{
for (unsigned int i = 0; i < Graf.liczba_wierzcholkow; i++) 
	{
	for (unsigned int j = 0; j < Graf.liczba_wierzcholkow; j++)
		StrWy << Graf.Macierz_Sasiedztwa[i][j];
	StrWy << std::endl;
	}
}
