#include "indice_invertido.h"
#include <filesystem>
#include <string>
#include <map>
#include <fstream>

using namespace std;

set<string> Indice_Invertido::busca(string palavra) {
    return indice_[normalizar(palavra)];
}

void Indice_Invertido::inserir(string palavra, string documento) {
    indice_[palavra].insert(documento);
}

void Indice_Inverso::constroiIndice(){
    const filesystem::path documentos{"./documentos"};
    ifstream {documentos};
    string line;

    for (auto const& dir_entry : filesystem::directory_iterator{documentos}) {
        while(getline(dir_entry, line))
            for(auto palavra : line)
                inserir(palavra, dir_entry);
    }
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
