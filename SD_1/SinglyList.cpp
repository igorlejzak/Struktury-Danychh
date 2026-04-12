#include "SinglyList.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// konstruktor - pusta lista, oba wskazniki ustawione na nullptr
SinglyList::SinglyList() {
    Glowa = nullptr;
    Ogon = nullptr;
}

// destruktor - przechodzimy przez liste i kasujemy kazdy wezel
SinglyList::~SinglyList() {
    Wezel* Aktualny = Glowa;
    while (Aktualny) {
        Wezel* Tymczasowy = Aktualny->Nastepny; // zapamietaj nastepny zanim skasujemy
        delete Aktualny;
        Aktualny = Tymczasowy;
    }
}

// dodaj na koniec, zoptymalizowane dzieki wskaznikowi Ogon
void SinglyList::DodajNaKoniec(int Wartosc) {
    Wezel* NowyWezel = new Wezel{ Wartosc, nullptr }; // next = nullptr bo bedzie ostatni

    if (!Glowa) {
        // lista byla pusta - nowy wezel jest jedynym
        Glowa = Ogon = NowyWezel;
    }
    else {
        Ogon->Nastepny = NowyWezel; // stary ostatni wskazuje na nowy
        Ogon = NowyWezel;           // Ogon przesuwa sie na nowy wezel
    }
}

// dodaj na poczatek 
void SinglyList::DodajNaPoczatek(int Wartosc) {
    Wezel* NowyWezel = new Wezel{ Wartosc, Glowa }; // nastepny nowego = dotychczasowy pierwszy

    Glowa = NowyWezel;                    // Glowa przesuwa sie na nowy wezel
    if (!Ogon) Ogon = NowyWezel;          // jesli lista byla pusta, Ogon tez wskazuje na nowy
}

// dodaj na pozycje 
void SinglyList::DodajNaPozycje(int Wartosc, int Pozycja) {
    if (Pozycja <= 0) {
        DodajNaPoczatek(Wartosc); //jesli pusta to dodajemy na poczatek
        return;
    }

    int DlugoscListy = PobierzRozmiar();
    if (Pozycja >= DlugoscListy) { //jesli wieksza od dlugosci listy dodajemy na koniec
        DodajNaKoniec(Wartosc);
        return;
    }

    // dochodzimy do wezla przed Pozycja
    Wezel* Aktualny = Glowa;
    for (int i = 0; i < Pozycja - 1; i++)
        Aktualny = Aktualny->Nastepny;

    // wstawiamy nowy wezel miedzy Aktualny a Aktualny - Nastepny
    Wezel* NowyWezel = new Wezel{ Wartosc, Aktualny->Nastepny };
    Aktualny->Nastepny = NowyWezel;

    // jesli wstawilismy na koniec, aktualizujemy Ogon
    if (!NowyWezel->Nastepny) Ogon = NowyWezel;
}

// usun pierwszy
void SinglyList::UsunZPoczatku() {
    if (!Glowa) return; // pusta lista - nic nie rob

    Wezel* Tymczasowy = Glowa;  // zapamietaj stary pierwszy
    Glowa = Glowa->Nastepny;    // przesuń Glowe na drugi element

    if (!Glowa) Ogon = nullptr; // lista stala sie pusta, zerujemy rowniez ogon

    delete Tymczasowy;
}

// usun ostatni
void SinglyList::UsunZKonca() {
    if (!Glowa) return;

    if (Glowa == Ogon) {
        // lista ma tylko jeden element
        delete Glowa;
        Glowa = Ogon = nullptr;
        return;
    }

    // musimy dojsc do wezla przed ostatnim
    Wezel* Aktualny = Glowa;
    while (Aktualny->Nastepny != Ogon)
        Aktualny = Aktualny->Nastepny;

    delete Ogon;              // kasujemy ostatni
    Ogon = Aktualny;          // nowy ostatni to Aktualny
    Ogon->Nastepny = nullptr; // upewniamy sie ze next = nullptr
}

// usun z pozycji
void SinglyList::UsunZPozycji(int Pozycja) {
    if (!Glowa) return;

    if (Pozycja <= 0) {
        UsunZPoczatku();  //jesli pozycja <0 to usun pierwszy element
        return;
    }

    int DlugoscListy = PobierzRozmiar();
    if (Pozycja >= DlugoscListy) Pozycja = DlugoscListy - 1; // zabezpieczenie

    // dochodzimy do wezla PRZED usuwanym
    Wezel* Aktualny = Glowa;
    for (int i = 0; i < Pozycja - 1; i++)
        Aktualny = Aktualny->Nastepny;

    Wezel* DoUsuniecia = Aktualny->Nastepny; // wezel do usuniecia
    Aktualny->Nastepny = DoUsuniecia->Nastepny; // "przeskakujemy" przez usuwany

    if (!Aktualny->Nastepny) Ogon = Aktualny; // jesli usunieto ostatni, aktualizuj Ogon

    delete DoUsuniecia;
}

// szukaj - przeszukiwanie od poczatku do konca
int SinglyList::Szukaj(int Wartosc) {
    Wezel* Aktualny = Glowa;
    int Indeks = 0;

    while (Aktualny) {
        if (Aktualny->Wartosc == Wartosc) return Indeks; // znaleziono
        Aktualny = Aktualny->Nastepny;
        Indeks++;
    }
    return -1; // nie znaleziono
}

// wyswietl wszystkie elementy
void SinglyList::Wyswietl() {
    if (!Glowa) {
        cout << "(pusta lista)\n";
        return;
    }

    Wezel* Aktualny = Glowa;
    while (Aktualny) {
        cout << Aktualny->Wartosc << " ";
        Aktualny = Aktualny->Nastepny;
    }
    cout << "\n";
}

// generuj - czysci liste i wypelnia n losowymi liczbami 0-9999
void SinglyList::Generuj(int IloscDoWygenerowania) {
    while (Glowa) UsunZPoczatku(); // usun wszystkie wezly

    for (int i = 0; i < IloscDoWygenerowania; i++)
        DodajNaKoniec(rand() % 10000);
}

// pobierz rozmiar - przechodzimy przez cala liste i zliczamy elementy
int SinglyList::PobierzRozmiar() {
    int Licznik = 0;
    Wezel* Aktualny = Glowa;
    while (Aktualny) {
        Licznik++;
        Aktualny = Aktualny->Nastepny;
    }
    return Licznik;
}
