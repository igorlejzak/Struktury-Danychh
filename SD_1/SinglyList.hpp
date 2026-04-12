#ifndef SINGLYLIST_HPP
#define SINGLYLIST_HPP

// wezel listy jednokierunkowej - trzyma wartosc i wskaznik na nastepny wezel
struct Wezel {
    int Wartosc;    // przechowywana liczba
    Wezel* Nastepny; // wskaznik na nastepny wezel (nullptr jesli ostatni)
};

// lista jednokierunkowa - kazdy wezel wskazuje tylko do przodu.
// trzymamy wskaznik na pierwszy (Glowa) i ostatni (Ogon) wezel.
// W naszym przypadku wykorzystujemy ogon, aby zoptymalizowac dodawanie na koniec
class SinglyList {
    Wezel* Glowa; // wskaznik na pierwszy wezel
    Wezel* Ogon;  // wskaznik na ostatni wezel

public:
    SinglyList();
    ~SinglyList();

    void DodajNaKoniec(int Wartosc);
    void DodajNaPoczatek(int Wartosc);
    void DodajNaPozycje(int Wartosc, int Pozycja);

    void UsunZKonca();
    void UsunZPoczatku();
    void UsunZPozycji(int Pozycja);

    int  Szukaj(int Wartosc);
    void Wyswietl();
    void Generuj(int IloscDoWygenerowania);
    int  PobierzRozmiar();
};

#endif
