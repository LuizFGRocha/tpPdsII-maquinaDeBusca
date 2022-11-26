#include "indice_invertido.h"
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main() {
    Indice_Invertido google;

    setbuf(stdin, NULL);
    string entrada;
    getline(cin, entrada);

    set<string> x;
    try {
        x = google.pesquisa(entrada);
    } catch (excecaoPesquisaVazia e) {
        cerr << "A frase a ser pesquisada não contém caracteres alfabéticos." << endl;
    }
    
    int i = 1;
    for(auto docName : x){
        cout << i++ << ") " << docName << endl;
    }

    return 0;
}