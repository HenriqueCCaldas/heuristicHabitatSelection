# Heuristic Habitat Selection — C++

A combinatorial optimization project for a **minimum habitat (patch) selection problem with adjacency constraints**: given a set of habitat patches (*povoamentos*), each covering a subset of species, select the smallest subset of patches that covers every species, subject to the patches' neighbourhood/adjacency structure.

This is a variant of the classical **set covering problem** applied to ecological reserve site selection, solved via a greedy constructive heuristic combined with tabu-search-based local improvement.

## Structure

```
heuristicHabitatSelection/
├── heuristica_construtiva.pro   # Qt qmake project file (console app, C++11)
├── main.cpp                     # Entry point: reads input, runs the heuristic, prints results
├── povoamento.h / povoamento.cpp
│   ├── povoamento          # A single habitat patch: neighbours + species covered
│   ├── lista_povoamentos   # All patches in the study area + current solution set
│   ├── lista_especies      # Species coverage bookkeeping
│   └── iteracao(), adiciona_lista(), verificacao()  # Constructive + tabu-search local search
├── matriz_especies.txt          # Patch × species incidence matrix (input)
└── matriz_vizinhos.txt          # Patch × patch adjacency matrix (input)
```

## Problem

- **Input:** a patch–species incidence matrix (`matriz_especies.txt`) and a patch adjacency matrix (`matriz_vizinhos.txt`).
- **Goal:** select a minimum-size subset of patches such that every species is covered by at least one selected patch.
- **Method:**
  1. **Greedy constructive heuristic** (`adiciona_lista`) builds an initial feasible solution.
  2. **Tabu-search local search** (`iteracao`, using a tabu list to avoid cycling) iteratively improves the solution until all species-coverage requirements are satisfied.
  3. **Lower bound analysis** is used to assess how close the heuristic solution is to optimal.

## Build

Requires Qt's `qmake` (C++11, console application, no GUI dependency):

```
qmake heuristica_construtiva.pro
make
```

Alternatively, open `heuristica_construtiva.pro` directly in Qt Creator and build from there.

## Run

```
./heuristica_construtiva
```

The program prompts interactively for the number of patches and number of species, then reads `matriz_especies.txt` and `matriz_vizinhos.txt` from the working directory. It prints the incidence/adjacency matrices read in, the iteration log as the tabu search improves the solution, and finally the selected vs. non-selected patches.

## Notes

- Originally developed as coursework at ISEG — Lisbon School of Economics & Management.
- Variable and comment names are in Portuguese (`povoamento` = settlement/patch, `especies` = species, `vizinhanca` = neighbourhood); this README describes the logic in English for accessibility.c in English for accessibility.
