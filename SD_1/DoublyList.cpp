#include "DoublyList.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// konstruktor - pusta lista
DoublyList::DoublyList() {
    Glowa = nullptr;
    Ogon = nullptr;
}

// destruktor - kasujemy kazdy wezel
DoublyList::~DoublyList() {
    WezelD* Aktualny = Glowa;
    while (Aktualny) {
        WezelD* Tymczasowy = Aktualny->Nastepny;
        delete Aktualny;
        Aktualny = Tymczasowy;
    }
}

// dodaj na koniec
void DoublyList::DodajNaKoniec(int Wartosc) {
    WezelD* NowyWezel = new WezelD{ Wartosc, nullptr, Ogon }; // nastepny=nullptr, bo to nasz nowy ogon, poprzedni=stary ogon

    if (!Glowa) {
        Glowa = Ogon = NowyWezel;
    }
    else {
        Ogon->Nastepny = NowyWezel; // stary ostatni wskazuje na nowy
        Ogon = NowyWezel;           // Ogon przesuwa sie
    }
}

// dodaj na poczatek
void DoublyList::DodajNaPoczatek(int Wartosc) {
    WezelD* NowyWezel = new WezelD{ Wartosc, Glowa, nullptr }; // nastepny=stary Glowa, poprzedni=nullptr, bo to nowa glowa

    if (Glowa) Glowa->Poprzedni = NowyWezel; // stary pierwszy wskazuje poprzedni na nowy
    Glowa = NowyWezel;

    if (!Ogon) Ogon = NowyWezel; // lista byla pusta
}

// dodaj na pozycje
void DoublyList::DodajNaPozycje(int Wartosc, int Pozycja) {
    if (Pozycja <= 0) {
        DodajNaPoczatek(Wartosc);
        return;
    }

    int DlugoscListy = PobierzRozmiar();
    if (Pozycja >= DlugoscListy) {
        DodajNaKoniec(Wartosc);
        return;
    }

    // dochodzimy do wezla na pozycji Pozycja
    WezelD* Aktualny = Glowa;
    for (int i = 0; i < Pozycja; i++)
        Aktualny = Aktualny->Nastepny;

    // wstawiamy przed Aktualny
    WezelD* NowyWezel = new WezelD{ Wartosc, Aktualny, Aktualny->Poprzedni };

    if (Aktualny->Poprzedni) Aktualny->Poprzedni->Nastepny = NowyWezel;
    Aktualny->Poprzedni = NowyWezel;

    if (NowyWezel->Poprzedni == nullptr) Glowa = NowyWezel; // wstawiono na poczatek
}

// usun pierwszy
void DoublyList::UsunZPoczatku() {
    if (!Glowa) return;

    WezelD* Tymczasowy = Glowa;
    Glowa = Glowa->Nastepny;

    if (Glowa) Glowa->Poprzedni = nullptr; // nowy pierwszy nie ma poprzednika
    else Ogon = nullptr;                    // lista stala sie pusta

    delete Tymczasowy;
}

// usun ostatni
void DoublyList::UsunZKonca() {
    if (!Ogon) return;

    WezelD* Tymczasowy = Ogon;
    Ogon = Ogon->Poprzedni;

    if (Ogon) Ogon->Nastepny = nullptr; // nowy ostatni nie ma nastepnika
    else Glowa = nullptr;                // lista stala sie pusta

    delete Tymczasowy;
}

// usun z pozycji
void DoublyList::UsunZPozycji(int Pozycja) {
    if (!Glowa) return;

    if (Pozycja <= 0) {
        UsunZPoczatku();
        return;
    }

    int DlugoscListy = PobierzRozmiar();
    if (Pozycja >= DlugoscListy) Pozycja = DlugoscListy - 1;

    // dochodzimy do wezla na pozycji Pozycja
    WezelD* Aktualny = Glowa;
    for (int i = 0; i < Pozycja; i++)
        Aktualny = Aktualny->Nastepny;

    // przepinamy sasiadow zeby pomineli Aktualny
    if (Aktualny->Poprzedni) Aktualny->Poprzedni->Nastepny = Aktualny->Nastepny;
    else Glowa = Aktualny->Nastepny;

    if (Aktualny->Nastepny) Aktualny->Nastepny->Poprzedni = Aktualny->Poprzedni;
    else Ogon = Aktualny->Poprzedni;

    delete Aktualny;
}

// szukaj - przechodzimy przez cala strukture
int DoublyList::Szukaj(int Wartosc) {
    WezelD* Aktualny = Glowa;
    int Indeks = 0;

    while (Aktualny) {
        if (Aktualny->Wartosc == Wartosc) return Indeks;
        Aktualny = Aktualny->Nastepny;
        Indeks++;
    }
    return -1;
}

// wyswietl wszystkie elementy
void DoublyList::Wyswietl() {
    if (!Glowa) {
        cout << "(pusta lista)\n";
        return;
    }

    WezelD* Aktualny = Glowa;
    while (Aktualny) {
        cout << Aktualny->Wartosc << " ";
        Aktualny = Aktualny->Nastepny;
    }
    cout << "\n";
}

// generuj - czysci liste i wypelnia n losowymi liczbami 0-9999
void DoublyList::Generuj(int IloscDoWygenerowania) {
    while (Glowa) UsunZPoczatku();

    for (int i = 0; i < IloscDoWygenerowania; i++)
        DodajNaKoniec(rand() % 10000);
}

// pobierz rozmiar
int DoublyList::PobierzRozmiar() {
    int Licznik = 0;
    WezelD* Aktualny = Glowa;
    while (Aktualny) {
        Licznik++;
        Aktualny = Aktualny->Nastepny;
    }
    return Licznik;
}
