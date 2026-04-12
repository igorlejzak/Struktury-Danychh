#ifndef DOUBLYLIST_HPP
#define DOUBLYLIST_HPP

// wezel listy dwukierunkowej - ma wskazniki w obie strony
struct WezelD {
    int Wartosc;      // przechowywana liczba
    WezelD* Nastepny; // wskaznik na nastepny wezel
    WezelD* Poprzedni; // wskaznik na poprzedni wezel
};

// lista dwukierunkowa - kazdy wezel wskazuje na nastepny I poprzedni
// dzieki wskaznikowi Poprzedni usuwanie z konca jest zoptymalizowane
class DoublyList {
    WezelD* Glowa; // wskaznik na pierwszy wezel
    WezelD* Ogon;  // wskaznik na ostatni wezel

public:
    DoublyList();
    ~DoublyList();

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
