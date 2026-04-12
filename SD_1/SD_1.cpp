#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ArrayList.hpp"
#include "SinglyList.hpp"
#include "DoublyList.hpp"
#include "Benchmark.hpp"

using namespace std;

// wyswietla menu operacji dla wybranej struktury
void WyswietlMenu(const string& NazwaStruktury) {
    cout << "\n=== " << NazwaStruktury << " ===\n";
    cout << "1. Generuj losowo\n";
    cout << "2. Dodaj na poczatek\n";
    cout << "3. Dodaj na koniec\n";
    cout << "4. Dodaj na losowe miejsce\n";
    cout << "5. Usun z poczatku\n";
    cout << "6. Usun z konca\n";
    cout << "7. Usun z losowego miejsca\n";
    cout << "8. Szukaj\n";
    cout << "9. Wyswietl\n";
    cout << "0. Powrot\n";
    cout << "Wybor: ";
}

// Benchmark - Dla każdej struktury, każdego rozmiaru wykonywane są pomiary po czym wyniki zapisywane są do pliku csv 
void UruchomBenchmark() {
    int Rozmiary[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
    int IleRozmiarow = 8;
    int IlePowtorzen = 20; // kopie do uśredninia pomiarów

    cout << "\nBenchmark start\n";

    for (int r = 0; r < IleRozmiarow; r++) {
        int Rozmiar = Rozmiary[r];
        cout << "Rozmiar: " << Rozmiar << "...\n";

        // generujemy dane z ustalonym ziarnem
        // srand(42 + Rozmiar) - inne ziarno dla kazdego rozmiaru ale zawsze to samo
        // dzieki temu wszystkie 3 struktury dostaja identyczne dane
        srand(42 + Rozmiar);
        int* LosoweDane = new int[Rozmiar];
        for (int i = 0; i < Rozmiar; i++)
            LosoweDane[i] = rand() % 10000;

        // ta sama losowa pozycja dla operacji "losowe miejsce" we wszystkich strukturach
        int LosowaPozyja = rand() % Rozmiar;
        // szukamy elementu ze srodka listy - to daje przypadek sredni dla wyszukiwania
        int SzukanaWartosc = LosoweDane[Rozmiar / 2];

        // ARRAYLIST: dla kazdej operacji tworzymy IlePowtorzen osobnych kopii struktury
        {
            // tworzymy kopie - kazda operacja ma swoj wlasny zestaw
            ArrayList* KopieDodajPoczatek = new ArrayList[IlePowtorzen];
            ArrayList* KopieDodajKoniec = new ArrayList[IlePowtorzen];
            ArrayList* KopieDodajLosowo = new ArrayList[IlePowtorzen];
            ArrayList* KopieUsunPoczatek = new ArrayList[IlePowtorzen];
            ArrayList* KopieUsunKoniec = new ArrayList[IlePowtorzen];
            ArrayList* KopieUsunLosowo = new ArrayList[IlePowtorzen];
            ArrayList* KopieSzukaj = new ArrayList[IlePowtorzen];

            // wypelniamy wszystkie kopie tymi samymi danymi przed wykonaniem pomiaru
            for (int k = 0; k < IlePowtorzen; k++)
                for (int i = 0; i < Rozmiar; i++) {
                    KopieDodajPoczatek[k].DodajNaKoniec(LosoweDane[i]);
                    KopieDodajKoniec[k].DodajNaKoniec(LosoweDane[i]);
                    KopieDodajLosowo[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunPoczatek[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunKoniec[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunLosowo[k].DodajNaKoniec(LosoweDane[i]);
                    KopieSzukaj[k].DodajNaKoniec(LosoweDane[i]);
                }

            // mierzymy czas - kazda kopia uzywana dokladnie raz
            long long SumaDodajPoczatek = 0, SumaDodajKoniec = 0, SumaDodajLosowo = 0;
            long long SumaUsunPoczatek = 0, SumaUsunKoniec = 0, SumaUsunLosowo = 0;
            long long SumaSzukaj = 0;

            for (int k = 0; k < IlePowtorzen; k++) {
                SumaDodajPoczatek += Benchmark::ZmierzCzas([&]() { KopieDodajPoczatek[k].DodajNaPoczatek(LosoweDane[0]); });
                SumaDodajKoniec += Benchmark::ZmierzCzas([&]() { KopieDodajKoniec[k].DodajNaKoniec(LosoweDane[0]); });
                SumaDodajLosowo += Benchmark::ZmierzCzas([&]() { KopieDodajLosowo[k].DodajNaPozycje(LosoweDane[0], LosowaPozyja); });
                SumaUsunPoczatek += Benchmark::ZmierzCzas([&]() { KopieUsunPoczatek[k].UsunZPoczatku(); });
                SumaUsunKoniec += Benchmark::ZmierzCzas([&]() { KopieUsunKoniec[k].UsunZKonca(); });
                SumaUsunLosowo += Benchmark::ZmierzCzas([&]() { KopieUsunLosowo[k].UsunZPozycji(LosowaPozyja); });
                SumaSzukaj += Benchmark::ZmierzCzas([&]() { KopieSzukaj[k].Szukaj(SzukanaWartosc); });
            }

            // zapisujemy srednie czasy do pliku CSV
            Benchmark::Zapisz("ArrayList", "DodajPoczatek", Rozmiar, SumaDodajPoczatek / IlePowtorzen);
            Benchmark::Zapisz("ArrayList", "DodajKoniec", Rozmiar, SumaDodajKoniec / IlePowtorzen);
            Benchmark::Zapisz("ArrayList", "DodajLosowo", Rozmiar, SumaDodajLosowo / IlePowtorzen);
            Benchmark::Zapisz("ArrayList", "UsunPoczatek", Rozmiar, SumaUsunPoczatek / IlePowtorzen);
            Benchmark::Zapisz("ArrayList", "UsunKoniec", Rozmiar, SumaUsunKoniec / IlePowtorzen);
            Benchmark::Zapisz("ArrayList", "UsunLosowo", Rozmiar, SumaUsunLosowo / IlePowtorzen);
            Benchmark::Zapisz("ArrayList", "Szukaj", Rozmiar, SumaSzukaj / IlePowtorzen);

            // zwalniamy miejsca
            delete[] KopieDodajPoczatek; delete[] KopieDodajKoniec; delete[] KopieDodajLosowo;
            delete[] KopieUsunPoczatek;  delete[] KopieUsunKoniec;  delete[] KopieUsunLosowo;
            delete[] KopieSzukaj;
        }

        // SINGLYLIST - logika identyczna do ARRAYLIST
        {
            SinglyList* KopieDodajPoczatek = new SinglyList[IlePowtorzen];
            SinglyList* KopieDodajKoniec = new SinglyList[IlePowtorzen];
            SinglyList* KopieDodajLosowo = new SinglyList[IlePowtorzen];
            SinglyList* KopieUsunPoczatek = new SinglyList[IlePowtorzen];
            SinglyList* KopieUsunKoniec = new SinglyList[IlePowtorzen];
            SinglyList* KopieUsunLosowo = new SinglyList[IlePowtorzen];
            SinglyList* KopieSzukaj = new SinglyList[IlePowtorzen];

            for (int k = 0; k < IlePowtorzen; k++)
                for (int i = 0; i < Rozmiar; i++) {
                    KopieDodajPoczatek[k].DodajNaKoniec(LosoweDane[i]);
                    KopieDodajKoniec[k].DodajNaKoniec(LosoweDane[i]);
                    KopieDodajLosowo[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunPoczatek[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunKoniec[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunLosowo[k].DodajNaKoniec(LosoweDane[i]);
                    KopieSzukaj[k].DodajNaKoniec(LosoweDane[i]);
                }

            long long SumaDodajPoczatek = 0, SumaDodajKoniec = 0, SumaDodajLosowo = 0;
            long long SumaUsunPoczatek = 0, SumaUsunKoniec = 0, SumaUsunLosowo = 0;
            long long SumaSzukaj = 0;

            for (int k = 0; k < IlePowtorzen; k++) {
                SumaDodajPoczatek += Benchmark::ZmierzCzas([&]() { KopieDodajPoczatek[k].DodajNaPoczatek(LosoweDane[0]); });
                SumaDodajKoniec += Benchmark::ZmierzCzas([&]() { KopieDodajKoniec[k].DodajNaKoniec(LosoweDane[0]); });
                SumaDodajLosowo += Benchmark::ZmierzCzas([&]() { KopieDodajLosowo[k].DodajNaPozycje(LosoweDane[0], LosowaPozyja); });
                SumaUsunPoczatek += Benchmark::ZmierzCzas([&]() { KopieUsunPoczatek[k].UsunZPoczatku(); });
                SumaUsunKoniec += Benchmark::ZmierzCzas([&]() { KopieUsunKoniec[k].UsunZKonca(); });
                SumaUsunLosowo += Benchmark::ZmierzCzas([&]() { KopieUsunLosowo[k].UsunZPozycji(LosowaPozyja); });
                SumaSzukaj += Benchmark::ZmierzCzas([&]() { KopieSzukaj[k].Szukaj(SzukanaWartosc); });
            }

            Benchmark::Zapisz("SinglyList", "DodajPoczatek", Rozmiar, SumaDodajPoczatek / IlePowtorzen);
            Benchmark::Zapisz("SinglyList", "DodajKoniec", Rozmiar, SumaDodajKoniec / IlePowtorzen);
            Benchmark::Zapisz("SinglyList", "DodajLosowo", Rozmiar, SumaDodajLosowo / IlePowtorzen);
            Benchmark::Zapisz("SinglyList", "UsunPoczatek", Rozmiar, SumaUsunPoczatek / IlePowtorzen);
            Benchmark::Zapisz("SinglyList", "UsunKoniec", Rozmiar, SumaUsunKoniec / IlePowtorzen);
            Benchmark::Zapisz("SinglyList", "UsunLosowo", Rozmiar, SumaUsunLosowo / IlePowtorzen);
            Benchmark::Zapisz("SinglyList", "Szukaj", Rozmiar, SumaSzukaj / IlePowtorzen);

            delete[] KopieDodajPoczatek; delete[] KopieDodajKoniec; delete[] KopieDodajLosowo;
            delete[] KopieUsunPoczatek;  delete[] KopieUsunKoniec;  delete[] KopieUsunLosowo;
            delete[] KopieSzukaj;
        }

        // DOUBLYLIST - logika również identyczna jak wcześniej
        {
            DoublyList* KopieDodajPoczatek = new DoublyList[IlePowtorzen];
            DoublyList* KopieDodajKoniec = new DoublyList[IlePowtorzen];
            DoublyList* KopieDodajLosowo = new DoublyList[IlePowtorzen];
            DoublyList* KopieUsunPoczatek = new DoublyList[IlePowtorzen];
            DoublyList* KopieUsunKoniec = new DoublyList[IlePowtorzen];
            DoublyList* KopieUsunLosowo = new DoublyList[IlePowtorzen];
            DoublyList* KopieSzukaj = new DoublyList[IlePowtorzen];

            for (int k = 0; k < IlePowtorzen; k++)
                for (int i = 0; i < Rozmiar; i++) {
                    KopieDodajPoczatek[k].DodajNaKoniec(LosoweDane[i]);
                    KopieDodajKoniec[k].DodajNaKoniec(LosoweDane[i]);
                    KopieDodajLosowo[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunPoczatek[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunKoniec[k].DodajNaKoniec(LosoweDane[i]);
                    KopieUsunLosowo[k].DodajNaKoniec(LosoweDane[i]);
                    KopieSzukaj[k].DodajNaKoniec(LosoweDane[i]);
                }

            long long SumaDodajPoczatek = 0, SumaDodajKoniec = 0, SumaDodajLosowo = 0;
            long long SumaUsunPoczatek = 0, SumaUsunKoniec = 0, SumaUsunLosowo = 0;
            long long SumaSzukaj = 0;

            for (int k = 0; k < IlePowtorzen; k++) {
                SumaDodajPoczatek += Benchmark::ZmierzCzas([&]() { KopieDodajPoczatek[k].DodajNaPoczatek(LosoweDane[0]); });
                SumaDodajKoniec += Benchmark::ZmierzCzas([&]() { KopieDodajKoniec[k].DodajNaKoniec(LosoweDane[0]); });
                SumaDodajLosowo += Benchmark::ZmierzCzas([&]() { KopieDodajLosowo[k].DodajNaPozycje(LosoweDane[0], LosowaPozyja); });
                SumaUsunPoczatek += Benchmark::ZmierzCzas([&]() { KopieUsunPoczatek[k].UsunZPoczatku(); });
                SumaUsunKoniec += Benchmark::ZmierzCzas([&]() { KopieUsunKoniec[k].UsunZKonca(); });
                SumaUsunLosowo += Benchmark::ZmierzCzas([&]() { KopieUsunLosowo[k].UsunZPozycji(LosowaPozyja); });
                SumaSzukaj += Benchmark::ZmierzCzas([&]() { KopieSzukaj[k].Szukaj(SzukanaWartosc); });
            }

            Benchmark::Zapisz("DoublyList", "DodajPoczatek", Rozmiar, SumaDodajPoczatek / IlePowtorzen);
            Benchmark::Zapisz("DoublyList", "DodajKoniec", Rozmiar, SumaDodajKoniec / IlePowtorzen);
            Benchmark::Zapisz("DoublyList", "DodajLosowo", Rozmiar, SumaDodajLosowo / IlePowtorzen);
            Benchmark::Zapisz("DoublyList", "UsunPoczatek", Rozmiar, SumaUsunPoczatek / IlePowtorzen);
            Benchmark::Zapisz("DoublyList", "UsunKoniec", Rozmiar, SumaUsunKoniec / IlePowtorzen);
            Benchmark::Zapisz("DoublyList", "UsunLosowo", Rozmiar, SumaUsunLosowo / IlePowtorzen);
            Benchmark::Zapisz("DoublyList", "Szukaj", Rozmiar, SumaSzukaj / IlePowtorzen);

            delete[] KopieDodajPoczatek; delete[] KopieDodajKoniec; delete[] KopieDodajLosowo;
            delete[] KopieUsunPoczatek;  delete[] KopieUsunKoniec;  delete[] KopieUsunLosowo;
            delete[] KopieSzukaj;
        }

        delete[] LosoweDane;
    }

    cout << "Benchmark zakończony! Pomiary zapisane w 'wyniki.csv'\n";
}

int main() {
    srand(time(NULL)); // inicjalizacja generatora 

    // tworzymy puste struktury
    ArrayList Tablica;
    SinglyList ListaJednokierunkowa;
    DoublyList ListaDwukierunkowa;

    int WybranaStruktura, WybranaOperacja; // wybory w menu

    while (true) {
        // wybor struktury
        cout << "\n=== WYBIERZ STRUKTURE ===\n";
        cout << "1. Tablica dynamiczna\n";
        cout << "2. Lista jednokierunkowa\n";
        cout << "3. Lista dwukierunkowa\n";
        cout << "4. Benchmark (pomiar wszystkich struktur)\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> WybranaStruktura;

        if (WybranaStruktura == 0) break;
        if (WybranaStruktura == 4) { UruchomBenchmark(); continue; }

        // operacje na wybranej strukturze
        while (true) {
            if (WybranaStruktura == 1) WyswietlMenu("TABLICA DYNAMICZNA");
            if (WybranaStruktura == 2) WyswietlMenu("LISTA JEDNOKIERUNKOWA");
            if (WybranaStruktura == 3) WyswietlMenu("LISTA DWUKIERUNKOWA");

            cin >> WybranaOperacja;
            if (WybranaOperacja == 0) break;

            int Ilosc, Wartosc, Pozycja, Rozmiar;

            // TABLICA
            if (WybranaStruktura == 1) {
                if (WybranaOperacja == 1) {
                    cout << "Podaj ilosc elementow: ";
                    cin >> Ilosc;
                    Tablica.Generuj(Ilosc);
                    cout << "Wygenerowano " << Ilosc << " elementow.\n";
                }
                else if (WybranaOperacja == 2) {
                    Wartosc = rand() % 10000;
                    Tablica.DodajNaPoczatek(Wartosc);
                    cout << "Dodano " << Wartosc << " na poczatek.\n";
                }
                else if (WybranaOperacja == 3) {
                    Wartosc = rand() % 10000;
                    Tablica.DodajNaKoniec(Wartosc);
                    cout << "Dodano " << Wartosc << " na koniec.\n";
                }
                else if (WybranaOperacja == 4) {
                    Rozmiar = Tablica.PobierzRozmiar();
                    Pozycja = (Rozmiar > 0) ? rand() % (Rozmiar + 1) : 0;
                    Wartosc = rand() % 10000;
                    Tablica.DodajNaPozycje(Wartosc, Pozycja);
                    cout << "Dodano " << Wartosc << " na losowe miejsce " << Pozycja << ".\n";
                }
                else if (WybranaOperacja == 5) { Tablica.UsunZPoczatku(); cout << "Usunieto z poczatku.\n"; }
                else if (WybranaOperacja == 6) { Tablica.UsunZKonca();    cout << "Usunieto z konca.\n"; }
                else if (WybranaOperacja == 7) {
                    Rozmiar = Tablica.PobierzRozmiar();
                    if (Rozmiar > 0) {
                        Pozycja = rand() % Rozmiar;
                        Tablica.UsunZPozycji(Pozycja);
                        cout << "Usunieto z losowego miejsca " << Pozycja << ".\n";
                    }
                    else cout << "Tablica jest pusta.\n";
                }
                else if (WybranaOperacja == 8) {
                    cout << "Podaj szukana wartosc: ";
                    cin >> Wartosc;
                    int Indeks = Tablica.Szukaj(Wartosc);
                    if (Indeks == -1) cout << "Nie znaleziono.\n";
                    else cout << "Znaleziono na indeksie: " << Indeks << "\n";
                }
                else if (WybranaOperacja == 9) Tablica.Wyswietl();
            }

            //LISTA JEDNOKIERUNKOWA
            else if (WybranaStruktura == 2) {
                if (WybranaOperacja == 1) {
                    cout << "Podaj ilosc elementow: ";
                    cin >> Ilosc;
                    ListaJednokierunkowa.Generuj(Ilosc);
                    cout << "Wygenerowano " << Ilosc << " elementow.\n";
                }
                else if (WybranaOperacja == 2) {
                    Wartosc = rand() % 10000;
                    ListaJednokierunkowa.DodajNaPoczatek(Wartosc);
                    cout << "Dodano " << Wartosc << " na poczatek.\n";
                }
                else if (WybranaOperacja == 3) {
                    Wartosc = rand() % 10000;
                    ListaJednokierunkowa.DodajNaKoniec(Wartosc);
                    cout << "Dodano " << Wartosc << " na koniec.\n";
                }
                else if (WybranaOperacja == 4) {
                    Rozmiar = ListaJednokierunkowa.PobierzRozmiar();
                    Pozycja = (Rozmiar > 0) ? rand() % (Rozmiar + 1) : 0;
                    Wartosc = rand() % 10000;
                    ListaJednokierunkowa.DodajNaPozycje(Wartosc, Pozycja);
                    cout << "Dodano " << Wartosc << " na losowe miejsce " << Pozycja << ".\n";
                }
                else if (WybranaOperacja == 5) { ListaJednokierunkowa.UsunZPoczatku(); cout << "Usunieto z poczatku.\n"; }
                else if (WybranaOperacja == 6) { ListaJednokierunkowa.UsunZKonca();    cout << "Usunieto z konca.\n"; }
                else if (WybranaOperacja == 7) {
                    Rozmiar = ListaJednokierunkowa.PobierzRozmiar();
                    if (Rozmiar > 0) {
                        Pozycja = rand() % Rozmiar;
                        ListaJednokierunkowa.UsunZPozycji(Pozycja);
                        cout << "Usunieto z losowego miejsca " << Pozycja << ".\n";
                    }
                    else cout << "Lista jest pusta.\n";
                }
                else if (WybranaOperacja == 8) {
                    cout << "Podaj szukana wartosc: ";
                    cin >> Wartosc;
                    int Indeks = ListaJednokierunkowa.Szukaj(Wartosc);
                    if (Indeks == -1) cout << "Nie znaleziono.\n";
                    else cout << "Znaleziono na indeksie: " << Indeks << "\n";
                }
                else if (WybranaOperacja == 9) ListaJednokierunkowa.Wyswietl();
            }

            //LISTA DWUKIERUNKOWA
            else if (WybranaStruktura == 3) {
                if (WybranaOperacja == 1) {
                    cout << "Podaj ilosc elementow: ";
                    cin >> Ilosc;
                    ListaDwukierunkowa.Generuj(Ilosc);
                    cout << "Wygenerowano " << Ilosc << " elementow.\n";
                }
                else if (WybranaOperacja == 2) {
                    Wartosc = rand() % 10000;
                    ListaDwukierunkowa.DodajNaPoczatek(Wartosc);
                    cout << "Dodano " << Wartosc << " na poczatek.\n";
                }
                else if (WybranaOperacja == 3) {
                    Wartosc = rand() % 10000;
                    ListaDwukierunkowa.DodajNaKoniec(Wartosc);
                    cout << "Dodano " << Wartosc << " na koniec.\n";
                }
                else if (WybranaOperacja == 4) {
                    Rozmiar = ListaDwukierunkowa.PobierzRozmiar();
                    Pozycja = (Rozmiar > 0) ? rand() % (Rozmiar + 1) : 0;
                    Wartosc = rand() % 10000;
                    ListaDwukierunkowa.DodajNaPozycje(Wartosc, Pozycja);
                    cout << "Dodano " << Wartosc << " na losowe miejsce " << Pozycja << ".\n";
                }
                else if (WybranaOperacja == 5) { ListaDwukierunkowa.UsunZPoczatku(); cout << "Usunieto z poczatku.\n"; }
                else if (WybranaOperacja == 6) { ListaDwukierunkowa.UsunZKonca();    cout << "Usunieto z konca.\n"; }
                else if (WybranaOperacja == 7) {
                    Rozmiar = ListaDwukierunkowa.PobierzRozmiar();
                    if (Rozmiar > 0) {
                        Pozycja = rand() % Rozmiar;
                        ListaDwukierunkowa.UsunZPozycji(Pozycja);
                        cout << "Usunieto z losowego miejsca " << Pozycja << ".\n";
                    }
                    else cout << "Lista jest pusta.\n";
                }
                else if (WybranaOperacja == 8) {
                    cout << "Podaj szukana wartosc: ";
                    cin >> Wartosc;
                    int Indeks = ListaDwukierunkowa.Szukaj(Wartosc);
                    if (Indeks == -1) cout << "Nie znaleziono.\n";
                    else cout << "Znaleziono na indeksie: " << Indeks << "\n";
                }
                else if (WybranaOperacja == 9) ListaDwukierunkowa.Wyswietl();
            }
        }
    }

    return 0;
}
