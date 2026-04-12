#include "ArrayList.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;


ArrayList::ArrayList() {
    MaksymalnyRozmiar = 10;              // na poczatek tworzymy tablice o rozmiarze 10 elementów
    IloscElementow = 0;                  
    Tablica = new int[MaksymalnyRozmiar]; // rezerwujemy pamiec
}


ArrayList::~ArrayList() {
    delete[] Tablica;       
}

// Metoda powieksz zwieksza nasza tablice dwukrotnie przy braku miejsca
// kopiuje stare elementy do nowej wiekszej tablicy
void ArrayList::Powieksz() {
    MaksymalnyRozmiar *= 2;                  
    int* NowaTablica = new int[MaksymalnyRozmiar]; 

    // kopiujemy stare elementy do nowej tablicy
    for (int i = 0; i < IloscElementow; i++)
        NowaTablica[i] = Tablica[i];

    delete[] Tablica;    // zwalniamy stara tablice
    Tablica = NowaTablica; // podmieniamy wskaznik
}

// dodaj na koniec - wstawiamy od razu na ostatnie wolne miejsce
void ArrayList::DodajNaKoniec(int Wartosc) {
    if (IloscElementow == MaksymalnyRozmiar) Powieksz(); 
    Tablica[IloscElementow] = Wartosc;
    IloscElementow++;
}

// dodaj na poczatek - musimy przesunac wszystkie elementy w prawo
void ArrayList::DodajNaPoczatek(int Wartosc) {
    if (IloscElementow == MaksymalnyRozmiar) Powieksz();

    // przesuwamy kazdy element o jedno miejsce w prawo
    for (int i = IloscElementow; i > 0; i--)
        Tablica[i] = Tablica[i - 1];

    Tablica[0] = Wartosc; // wstawiamy na pozycje 0
    IloscElementow++;
}

// dodaj na pozycje - przesuwamy czesc elementow w prawo
void ArrayList::DodajNaPozycje(int Wartosc, int Pozycja) {
    if (IloscElementow == MaksymalnyRozmiar) Powieksz();

    // zabezpieczenie zeby pozycja nie wyszla poza zakres
    if (Pozycja < 0) Pozycja = 0;
    if (Pozycja > IloscElementow) Pozycja = IloscElementow;

    // przesuwamy elementy od Pozycja w prawo
    for (int i = IloscElementow; i > Pozycja; i--)
        Tablica[i] = Tablica[i - 1];

    Tablica[Pozycja] = Wartosc;
    IloscElementow++;
}

// usun z konca, zmniejszamy licznik
void ArrayList::UsunZKonca() {
    if (IloscElementow > 0) IloscElementow--;
}

// usun z poczatku - przesuwamy wszystkie elementy w lewo
void ArrayList::UsunZPoczatku() {
    if (IloscElementow == 0) return;

    for (int i = 0; i < IloscElementow - 1; i++)
        Tablica[i] = Tablica[i + 1];

    IloscElementow--;
}

// usun z pozycji - przesuwamy czesc elementow w lewo
void ArrayList::UsunZPozycji(int Pozycja) {
    if (IloscElementow == 0) return;

    // zabezpieczenie przed wyjsciem poza zakres
    if (Pozycja < 0) Pozycja = 0;
    if (Pozycja >= IloscElementow) Pozycja = IloscElementow - 1;

    // przesuwamy elementy za Pozycja o jedno miejsce w lewo
    for (int i = Pozycja; i < IloscElementow - 1; i++)
        Tablica[i] = Tablica[i + 1];

    IloscElementow--;
}

// szukaj - przeszukiwanie liniowe od poczatku do konca
// zwraca indeks pierwszego wystapienia lub -1 jesli nie znaleziono
int ArrayList::Szukaj(int Wartosc) {
    for (int i = 0; i < IloscElementow; i++)
        if (Tablica[i] == Wartosc)
            return i;
    return -1;
}

// wyswietl wszystkie elementy
void ArrayList::Wyswietl() {
    if (IloscElementow == 0) {
        cout << "(pusta tablica)\n";
        return;
    }
    for (int i = 0; i < IloscElementow; i++)
        cout << Tablica[i] << " ";
    cout << "\n";
}

// generuj - czysci tablice i wypelnia n losowymi liczbami z zakresu 0-9999
void ArrayList::Generuj(int IloscDoWygenerowania) {
    IloscElementow = 0; // czyscimy tablice resetujac licznik
    for (int i = 0; i < IloscDoWygenerowania; i++)
        DodajNaKoniec(rand() % 10000);
}

// zwraca aktualna liczbe elementow w tablicy
int ArrayList::PobierzRozmiar() {
    return IloscElementow;
}
