#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

const int MAX = 10000; 

//  Statička 
void dodajSortiranoStaticka(std::vector<int>& lista, int element) {
    auto pozicija = std::lower_bound(lista.begin(), lista.end(), element);
    lista.insert(pozicija, element);
}

//  Dinamička
struct Cvor {
    int vrijednost;
    Cvor* sljedeci;
};

void dodajSortiranoDinamicna(Cvor*& glava, int vrijednost) {
    Cvor* novi = new Cvor{vrijednost, nullptr};
    if (glava == nullptr || vrijednost < glava->vrijednost) {
        novi->sljedeci = glava;
        glava = novi;
        return;
    }
    Cvor* temp = glava;
    while (temp->sljedeci != nullptr && temp->sljedeci->vrijednost < vrijednost) {
        temp = temp->sljedeci;
    }
    novi->sljedeci = temp->sljedeci;
    temp->sljedeci = novi;
}

void ispisiPrvih100Staticka(const std::vector<int>& lista) {
    for (int i = 0; i < 100 && i < lista.size(); i++) {
        std::cout << lista[i] << " ";
    }
    std::cout << std::endl;
}

void ispisiPrvih100Dinamicna(Cvor* glava) {
    int brojac = 0;
    while (glava != nullptr && brojac < 100) {
        std::cout << glava->vrijednost << " ";
        glava = glava->sljedeci;
        brojac++;
    }
    std::cout << std::endl;
}

void obrisiListu(Cvor*& glava) {
    while (glava != nullptr) {
        Cvor* temp = glava;
        glava = glava->sljedeci;
        delete temp;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    std::vector<int> listaStaticka;
    Cvor* glavaDinamicna = nullptr;

    //  Statička  
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; i++) {
        int broj = rand() % 1000000;
        dodajSortiranoStaticka(listaStaticka, broj);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trajanjeStaticka = end1 - start1;

    std::cout << "[STATIČKA LISTA] Vrijeme ubacivanja: " << trajanjeStaticka.count() << " sekundi\n";
    std::cout << "Prvih 100 elemenata (statička):\n";
    ispisiPrvih100Staticka(listaStaticka);

    //  Dinamička  
    srand(static_cast<unsigned>(time(0))); // Reset seedova za iste brojeve
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; i++) {
        if (i % 1000 == 0) std::cout << "." << std::flush;
        int broj = rand() % 1000000;
        dodajSortiranoDinamicna(glavaDinamicna, broj);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trajanjeDinamicna = end2 - start2;

    std::cout << "\n[DINAMIČKA LISTA] Vrijeme ubacivanja: " << trajanjeDinamicna.count() << " sekundi\n";
    std::cout << "Prvih 100 elemenata (dinamička):\n";
    ispisiPrvih100Dinamicna(glavaDinamicna);

    obrisiListu(glavaDinamicna);

    std::cout << "\n=== ANALIZA ===\n";
    if (trajanjeStaticka < trajanjeDinamicna)
        std::cout << "Statička lista je bila brža.\n";
    else
        std::cout << "Dinamička lista je bila brža.\n";

    std::cout << "Statička: " << trajanjeStaticka.count() << " s, Dinamička: " << trajanjeDinamicna.count() << " s\n";

    return 0;
}
