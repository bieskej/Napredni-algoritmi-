#include <iostream>
#include <chrono>
#include <cstdlib> // za rand()
#include <ctime>   // za time()

const int MAX = 1000000;

// Dodavanje sortiranog elementa u statičku listu
void dodajSortirano(int lista[], int &velicina, int element) {
    int i = velicina - 1;
    while (i >= 0 && lista[i] > element) {
        lista[i + 1] = lista[i];
        i--;
    }
    lista[i + 1] = element;
    velicina++;
}

// Ispis prvih 100 elemenata
void ispisiPrvih100(int lista[]) {
    for (int i = 0; i < 100; i++) {
        std::cout << lista[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::cout << "Program je pokrenut!" << std::endl;
    srand(time(0));

    int lista[MAX];
    int velicina = 0;

    // Generisanje i ubacivanje 1.000.000 elemenata
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < MAX; i++) {
        int broj = rand();
        dodajSortirano(lista, velicina, broj);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trajanje = end - start;

    std::cout << "Vrijeme ubacivanja u staticku listu: " << trajanje.count() << " sekundi\n";

    std::cout << "Prvih 100 elemenata:\n";
    ispisiPrvih100(lista);

    return 0;
}
