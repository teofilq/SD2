#include <iostream>
#include <algorithm>

class Nod {
public:
    int cheie;
    int inaltime;
    Nod* st;
    Nod* dr;

    Nod(int k) : cheie(k), inaltime(1), st(nullptr), dr(nullptr) {}
};

int getInaltime(Nod* nod) {
    if (nod == nullptr) return 0;
    return nod->inaltime;
}

int getBalans(Nod* nod) {
    if (nod == nullptr) return 0;
    return getInaltime(nod->st) - getInaltime(nod->dr);
}

Nod* rotatieDr(Nod* y) {
    Nod* x = y->st;
    Nod* T2 = x->dr;

    x->dr = y;
    y->st = T2;

    y->inaltime = std::max(getInaltime(y->st), getInaltime(y->dr)) + 1;
    x->inaltime = std::max(getInaltime(x->st), getInaltime(x->dr)) + 1;

    return x;
}

Nod* rotatieSt(Nod* x) {
    Nod* y = x->dr;
    Nod* T2 = y->st;

    y->st = x;
    x->dr = T2;

    x->inaltime = std::max(getInaltime(x->st), getInaltime(x->dr)) + 1;
    y->inaltime = std::max(getInaltime(y->st), getInaltime(y->dr)) + 1;

    return y;
}

Nod* inserare(Nod* nod, int cheie) {
    if (nod == nullptr) return new Nod(cheie);

    if (cheie < nod->cheie)
        nod->st = inserare(nod->st, cheie);
    else if (cheie > nod->cheie)
        nod->dr = inserare(nod->dr, cheie);
    else
        return nod;

    nod->inaltime = 1 + std::max(getInaltime(nod->st), getInaltime(nod->dr));
    int balance = getBalans(nod);

    if (balance > 1) {
        if (cheie < nod->st->cheie)
            return rotatieDr(nod);
        else {
            nod->st = rotatieSt(nod->st);
            return rotatieDr(nod);
        }
    }

    if (balance < -1) {
        if (cheie > nod->dr->cheie)
            return rotatieSt(nod);
        else {
            nod->dr = rotatieDr(nod->dr);
            return rotatieSt(nod);
        }
    }

    return nod;
}

Nod* valMinNod(Nod* node) {
    Nod* current = node;

    while (current->st != nullptr)
        current = current->st;

    return current;
}

Nod* stergere(Nod* rad, int cheie) {
    if (rad == nullptr)
        return rad;

    if (cheie < rad->cheie)
        rad->st = stergere(rad->st, cheie);
    else if (cheie > rad->cheie)
        rad->dr = stergere(rad->dr, cheie);
    else {
        if ((rad->st ==nullptr) || (rad->dr == nullptr)) {
            Nod* aux = rad->st ? rad->st : rad->dr;

            if (aux == nullptr) {
                aux = rad;
                rad = nullptr;
            } else
                *rad = *aux;
            delete aux;
        } else {
            Nod* temp = valMinNod(rad->dr);
            rad->cheie = temp->cheie;
            rad->dr = stergere(rad->dr, temp->cheie);
        }
    }

    if (rad == nullptr) return rad;

    rad->inaltime = 1 + std::max(getInaltime(rad->st), getInaltime(rad->dr));
    int balans = getBalans(rad);

    if (balans > 1) {
        if (getBalans(rad->st) >= 0)
            return rotatieDr(rad);
        else {
            rad->st = rotatieSt(rad->st);
            return rotatieDr(rad);
        }
    }

    if (balans < -1) {
        if (getBalans(rad->dr) <= 0)
            return rotatieSt(rad);
        else {
            rad->dr = rotatieDr(rad->dr);
            return rotatieSt(rad);
        }
    }

    return rad;
}

bool cautare(Nod* rad, int cheie) {
    if (rad == nullptr)
        return false;
    if (cheie == rad->cheie)
        return true;
    if (cheie < rad->cheie)
        return cautare(rad->st, cheie);
    return cautare(rad->dr, cheie);
}

void afisare(Nod* rad) {
    if (rad != nullptr) {
        afisare(rad->st);
        std::cout << rad->cheie << " ";
        afisare(rad->dr);
    }
}

int main() {
    Nod* rad = nullptr;

    rad = inserare(rad, 10);
    rad = inserare(rad, 20);
    rad = inserare(rad, 30);
    rad = inserare(rad, 40);
    rad = inserare(rad, 50);
    std::cout << "Cauta nodul 30: " << (cautare(rad, 30) ? "exista" : "nu exista") << std::endl;
    std::cout<< "Nodul 30 a fost sters."<<std::endl;
    rad = stergere(rad, 30);
    std::cout << "Afisare: ";
    afisare(rad);
    std::cout << std::endl;
    std::cout << "Cauta nodul 30: " << (cautare(rad, 30) ? "exista" : "nu exista") << std::endl;

    return 0;
}
