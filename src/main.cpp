#include "indice_invertido.h"
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main() {
    string entrada;
    Indice_Invertido google;
    google.constroiIndice();
    setbuf(stdin, NULL);
    getline(cin, entrada);
    set<string> x = google.pesquisa(entrada);
    for(auto a : x){
        cout << a << endl;
    }
    return 0;
}