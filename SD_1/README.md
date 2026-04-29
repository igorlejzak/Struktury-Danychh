# Data Structures — Performance Analysis

A university project implementing three fundamental data structures from scratch
in C++ (no STL), with a benchmarking system that measures and compares
operation times across different input sizes.

Built together with [Damian](https://github.com/damian5066) as part of the
Data Structures course at Wrocław University of Technology.

## Data structures implemented

**Dynamic Array (ArrayList)**
- doubles capacity when full
- supports add/remove at front, back, and arbitrary position

**Singly Linked List**
- head and tail pointers for O(1) add at back
- supports add/remove at front, back, and arbitrary position

**Doubly Linked List**
- bidirectional traversal with next/prev pointers
- supports add/remove at front, back, and arbitrary position

## Benchmark system

Each operation is measured 20 times per structure per input size
and averaged to reduce noise. Input sizes tested:
5,000 / 8,000 / 10,000 / 16,000 / 20,000 / 40,000 / 60,000 / 100,000 elements.

Results are saved to `wyniki.csv` for further analysis.

## How to run
```bash
g++ -O2 -o main main.cpp ArrayList.cpp SinglyList.cpp DoublyList.cpp
./main
```

## Operations measured
- Add at front / back / random position
- Remove from front / back / random position
- Search by value
