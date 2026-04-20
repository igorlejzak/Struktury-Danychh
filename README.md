# Struktury Danych – Miniprojekty

Repozytorium zawiera implementacje struktur danych wykonane w ramach przedmiotu **Struktury Danych** na studiach inżynierskich. Każdy miniprojekt to osobna implementacja wybranych struktur wraz z pomiarem złożoności czasowej podstawowych operacji.

---

## Miniprojekt 1 – Lista

Implementacja i porównanie trzech struktur danych:

- **Tablica dynamiczna (ArrayList)** – przy braku miejsca rozmiar jest podwajany, przy nadmiarze zmniejszany
- **Lista jednokierunkowa (SinglyList)** – węzły połączone jednym wskaźnikiem `next`, z dostępem przez `head` i `tail`
- **Lista dwukierunkowa (DoublyList)** – węzły połączone wskaźnikami `next` i `prev`, umożliwiające poruszanie się w obu kierunkach

### Zbadane operacje
- Dodawanie elementu na początku, końcu i losowej pozycji
- Usuwanie elementu z początku, końca i losowej pozycji
- Wyszukiwanie elementu

### Uruchomienie
```
g++ -std=c++17 -o program main.cpp
./program
```

Program uruchamia dwupoziomowe menu – najpierw wybór struktury, potem dostępne operacje. Opcja **Benchmark** mierzy czasy wszystkich operacji dla rozmiarów od 5000 do 100000 elementów i zapisuje wyniki do pliku `wyniki.csv`.

---

## Miniprojekt 2 – *(wkrótce)*

---

## Miniprojekt 3 – *(wkrótce)*

---

## Ogólne założenia projektowe

- Wszystkie struktury zaimplementowane samodzielnie, bez użycia STL
- Dane alokowane dynamicznie, tablice relokowane przy dodawaniu i usuwaniu
- Podstawowy element: 4-bajtowa liczba całkowita (`int`)
- Pomiary wykonywane wielokrotnie (20 powtórzeń) i uśredniane
- Wszystkie struktury porównywane na identycznych danych (to samo ziarno `srand`)
- Język: C++
