
#include <iostream>
#include <list>
#include<string>
#include <cstdlib>

using namespace std;
class HashTableChain {
private:
    int rozmiar;
    int rodzaj;
    int* TT = new int[rozmiar];
    list<int>* table;
    int Bucket;
    int func;
public:
    void hashFunction(int* tab, int n);
    void deleteElem(int key);
    int searchElem(int key);
    void printTable();
    void adresowanieLiniowe(int k, int* array, int elem, int i);
    void adresowanieKwadratowe(int k, int* array, int elem, int i);
    void haszowanieDwukrotne(int k, int* array, int elem, int i);
    void metodaLancuchowa(int* tab, int n);
    void display();
    void insert(int key);
    void deletee(int key);
    int search(int key);
    int size();
    HashTableChain(int x, int y, int func);
};
HashTableChain::HashTableChain(int x, int y, int func = 1) :rozmiar(x), rodzaj(y) {
};
int HashTableChain::size() { return rozmiar; }
void HashTableChain::hashFunction(int* tab, int n) {
    int k;
    int array[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        array[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        k = tab[i] % rozmiar;
        if (array[k] == -1) {
            array[k] = tab[i];
        }
        else {
            if (rodzaj == 2) {
                adresowanieLiniowe(k, array, tab[i], 1);
            }
            if (rodzaj == 3) {
                adresowanieKwadratowe(k, array, tab[i], 1);
            }
            if (rodzaj == 4) {
                haszowanieDwukrotne(k, array, tab[i], 1);
            }
        }
    }
    for (int i = 0; i < rozmiar; i++) {
        TT[i] = array[i];
    }
}

void HashTableChain::adresowanieLiniowe(int k, int* array, int elem, int i) {
    int h = (k + i) % rozmiar;
    if (array[h] == -1 || array[h] == -2) {
        array[h] = elem;
    }
    else {
        i++;
        adresowanieLiniowe(k, array, elem, i);
    }
}
void HashTableChain::adresowanieKwadratowe(int k, int* array, int elem, int i) {
    int h = (k + i + i * i) % rozmiar;
    if (array[h] == -1 || array[h] == -2) {
        array[h] = elem;
    }
    else {
        i++;
        adresowanieKwadratowe(k, array, elem, i);
    }
}
void HashTableChain::haszowanieDwukrotne(int k, int* array, int elem, int i) {
    int h = (k + i * ((elem % (rozmiar - 1)) + 1)) % rozmiar;
    if (array[h] == -1 || array[h] == -2) {
        array[h] = elem;
    }
    else {
        i++;
        haszowanieDwukrotne(k, array, elem, i);
    }
}

void HashTableChain::printTable() {
    cout << "[";
    for (int i = 0; i < rozmiar; i++) {
        if (i != rozmiar - 1) {
            if (TT[i] == -2) {
                cout << "Deleted, ";
            }
            else if (TT[i] == -1) {
                cout << "None, ";
            }
            else {
                cout << TT[i] << ", ";
            }
        }
        else {
            if (TT[i] == -2) {
                cout << "Deleted";
            }
            else if (TT[i] == -1) {
                cout << "None";
            }
            else {
                cout << TT[i];
            }
        }
    }
    cout << "]" << endl;
}
void HashTableChain::insert(int elem) {
    if (rodzaj == 1) {
        int k = elem % Bucket;
        table[k].push_front(elem);
        display();
    }
    else {
        int k;
        k = elem % rozmiar;

        if (TT[k] == -1 || TT[k] == -2) {
            TT[k] = elem;
        }
        else {
            if (rodzaj == 2) {
                adresowanieLiniowe(k, TT, elem, 1);
            }
            if (rodzaj == 3) {
                adresowanieKwadratowe(k, TT, elem, 1);
            }
            if (rodzaj == 4) {
                haszowanieDwukrotne(k, TT, elem, 1);
            }
        }
        printTable();
    }
}
int HashTableChain::searchElem(int elem) {
    for (int i = 0; i < rozmiar; i++) {
        if (TT[i] == elem) {
            return i;
        }
    }
    return -2;
}
void HashTableChain::deleteElem(int elem) {
    for (int i = 0; i < rozmiar; i++) {
        if (TT[i] == elem) {
            TT[i] = -2;
        }
    }
    printTable();
}
//-------------------------------------------------------------------
void HashTableChain::metodaLancuchowa(int* tab, int n) {
    int k;
    this->Bucket = rozmiar;
    table = new list<int>[Bucket];

    for (int i = 0; i < n; i++) {
        k = tab[i] % rozmiar;
        table[k].push_front(tab[i]);
    }
}

void HashTableChain::deletee(int key) {
    int k = key % Bucket;
    list<int>::iterator i;
    for (i = table[k].begin(); i != table[k].end(); i++) {
        if (*i == key) { break; }
    }
    if (i != table[k].end()) {
        table[k].erase(i);
    }
    display();
}
int HashTableChain::search(int key) {
    int k = key % Bucket;
    for (auto x : table[k]) {
        if (x == key) {
            return k;
        }
    }
    return -3;
}
void HashTableChain::display() {
    cout << "[";
    for (int i = 0; i < Bucket; i++) {
        if (i != Bucket - 1) {
            if (table[i].size() == 0) {
                cout << "None, ";
            }
            if (table[i].size() > 1) {
                cout << "[";
                for (auto x : table[i]) {
                    if (x == table[i].back()) {
                        cout << x;
                    }
                    else {
                        cout << x << ", ";
                    }
                }
                cout << "], ";
            }
            if (table[i].size() == 1) {
                for (auto x : table[i]) {
                    cout << x << ", ";
                }
            }
        }

        if (i == Bucket - 1) {
            if (table[i].size() == 0) {
                cout << "None";
            }
            if (table[i].size() > 1) {
                cout << "[";
                for (auto x : table[i]) {
                    if (x == table[i].back()) {
                        cout << x;
                    }
                    else {
                        cout << x << ", ";
                    }
                }
                cout << "]";
            }
            if (table[i].size() == 1) {
                for (auto x : table[i]) {
                    cout << x;
                }
            }
        }
    }
    cout << "]" << endl;
}
//-------------------------------------------------------------------
int main()
{
    string word;
    getline(cin, word);
    int counter = 0;
    int x = word.length();

    for (int i = 0; i < x; i++) {
        if (word[i] == ' ') {
            counter++;
        }
    }
    int amount = counter;
    int arr[amount];

    int j = 0;
    for (int i = 0; i < x; i++) {

        char tab[5] = {};
        int counter = 0;
        while (word[i] > 47 && word[i] < 58) {
            tab[counter] = word[i];
            counter++;
            i++;
        }
        if (i != 0) {
            arr[j] = atoi(tab);
            j++;
        }
    }
    int rozmiar = arr[0];
    int rodzaj = arr[1];
    int tablica[amount - 2];
    int y = 2;
    for (int i = 0; i < amount - 2; i++) {
        tablica[i] = arr[y];
        y++;
    }

    HashTableChain a(rozmiar, rodzaj);
    if (arr[1] == 1) {
        a.metodaLancuchowa(tablica, amount - 2);
        a.display();
    }
    else {
        a.hashFunction(tablica, amount - 2);
        a.printTable();
    }

    while (true) {
        string tabWybor;
        getline(cin, tabWybor);
        int count = 0;
        int z = tabWybor.length();

        for (int i = 0; i < z; i++) {
            if (tabWybor[i] == ' ') {
                count++;
            }
        }
        int aa = count + 1;
        int array[aa];

        int j = 0;
        for (int i = 0; i < z; i++) {

            char tab[5] = {};
            int count = 0;
            while (tabWybor[i] > 47 && tabWybor[i] < 58 || tabWybor[i] == '-') {
                tab[count] = tabWybor[i];
                count++;
                i++;
            }
            array[j] = atoi(tab);
            j++;
        }


        if (array[0] == -1) {
            exit(1);
        }
        if (array[0] == 0) {
            a.insert(array[1]);
        }
        if (array[0] == 1) {
            int t;
            if (arr[1] == 1) {
                t = a.search(array[1]);
            }
            if(arr[1]!=1){
                t = a.searchElem(array[1]);
            }
            cout << t << endl;
        }
        if (array[0] == 2) {
            if (arr[1] == 1) {
                a.deletee(array[1]);
            }
            else {
                a.deleteElem(array[1]);
            }
        }
    }
    return 0;
}
