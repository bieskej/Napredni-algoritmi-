#include <iostream>
#include <cstring>

struct Cvor {
    char podatak[50];           
    Cvor* dijete;               
    Cvor* brat;                

    Cvor(const char* p) {
        strcpy(podatak, p);
        dijete = nullptr;
        brat = nullptr;
    }
};

void dodaj_dijete(Cvor* roditelj, Cvor* dijete) {
    if (roditelj->dijete == nullptr) {
        roditelj->dijete = dijete;  
    } else {
        Cvor* trenutni = roditelj->dijete;
        while (trenutni->brat != nullptr) {
            trenutni = trenutni->brat;  
        }
        trenutni->brat = dijete;  
    }
}

void ispis_stabla(Cvor* cvor, int razina) {
    if (cvor == nullptr) return;

    for (int i = 0; i < razina; i++) {
        std::cout << "  ";  
    }  
    std::cout << cvor->podatak << std::endl;

    ispis_stabla(cvor->dijete, razina + 1);
    ispis_stabla(cvor->brat, razina);
}

Cvor* pretraga(Cvor* cvor, const char* vrijednost) {
    if (cvor == nullptr) return nullptr;

    if (strcmp(cvor->podatak, vrijednost) == 0) {
        return cvor; 
    }

    Cvor* pronadjen = pretraga(cvor->dijete, vrijednost);
    if (pronadjen != nullptr) {
        return pronadjen;
    }
    return pretraga(cvor->brat, vrijednost);
}

void obrisi_stablo(Cvor* cvor) {
    if (cvor == nullptr) return;

    obrisi_stablo(cvor->dijete);  
    obrisi_stablo(cvor->brat);    

    delete cvor; 
}


int broj_cvorova(Cvor* cvor) {
    if (cvor == nullptr) return 0;

    return 1 + broj_cvorova(cvor->dijete) + broj_cvorova(cvor->brat);
}

int main() {
    Cvor* korijen = new Cvor("Root");

    Cvor* dijete1 = new Cvor("Child 1");
    Cvor* dijete2 = new Cvor("Child 2");
    Cvor* dijete3 = new Cvor("Child 3");

    dodaj_dijete(korijen, dijete1);
    dodaj_dijete(korijen, dijete2);
    dodaj_dijete(korijen, dijete3);

    Cvor* dijete4 = new Cvor("Child 1.1");
    Cvor* dijete5 = new Cvor("Child 1.2");
    dodaj_dijete(dijete1, dijete4);
    dodaj_dijete(dijete1, dijete5);
    Cvor* dijete6 = new Cvor("Child 1.3");
    dodaj_dijete(dijete1, dijete6);
    std::cout << "Ispis stabla:" << std::endl;
    ispis_stabla(korijen, 0);

    Cvor* rezultat = pretraga(korijen, "Child 1.1");
    if (rezultat != nullptr) {
        std::cout << "\nPronađen čvor: " << rezultat->podatak << std::endl;
    } else {
        std::cout << "\nČvor nije pronađen." << std::endl;
    }

    std::cout << "\nBroj čvorova u stablu: " << broj_cvorova(korijen) << std::endl;

    obrisi_stablo(korijen);

    return 0;
}
