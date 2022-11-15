#include "indice_invertido.h"
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main() {
    Indice_Invertido google;
    google.constroiIndice();

    setbuf(stdin, NULL);
    string entrada;
    getline(cin, entrada);

    set<string> x;
    try {
        x = google.pesquisa(entrada);
    } catch (excecaoPesquisaVazia e) {
        cout << "A frase a ser pesquisada não contém caracteres alfabéticos." << endl;
    }
    
    for(auto a : x){
        cout << a << endl;
    }

    return 0;
}