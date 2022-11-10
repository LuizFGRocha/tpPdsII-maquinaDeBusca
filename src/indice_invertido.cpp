#include "indice_invertido.h"
#include <vector>
#include <filesystem>
#include <string>
#include <map>

using namespace std;

set<string> Indice_Invertido::busca(string palavra) {
    return indice_[palavra];
}

void Indice_Invertido::inserir(string palavra, string documento) {
    indice_[palavra].insert(documento);
}

string normalizar(string palavra) {
    string normalizada;
    for (char c : palavra) {
        if (tolower(c) >= 97 && tolower(c) <= 122) {
            normalizada.push_back(tolower(c));
        }
    }
    return normalizada;
}
