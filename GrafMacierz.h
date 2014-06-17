#ifndef GRAFMACIERZSASIEDZTWA_H
#define GRAFMACIERZSASIEDZTWA_H

#include <vector>
#include <iostream>

class Graf_Macierz_Sasiedztwa {
public:
	unsigned int liczba_wierzcholkow;
	unsigned int liczba_krawedzi;
	std::vector<std::vector<unsigned int> > Macierz_Sasiedztwa;
	~Graf_Macierz_Sasiedztwa(){};
	Graf_Macierz_Sasiedztwa(unsigned int,unsigned int);
	Graf_Macierz_Sasiedztwa(const char*);
    void Zapisz_do_pliku(const char*);
	bool Czy_Jest_Krawedz(unsigned int wierzcholek1,unsigned int wierzcholek2)
		{
		return Macierz_Sasiedztwa[wierzcholek1][wierzcholek2];
		}
	friend void operator <<(std::ostream& StrWy,Graf_Macierz_Sasiedztwa& Graf);
};
void operator <<(std::ostream& StrWy,Graf_Macierz_Sasiedztwa& Graf);
#endif
