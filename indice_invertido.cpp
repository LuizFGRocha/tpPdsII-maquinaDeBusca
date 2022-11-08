#include <indice_invertido.h>

set<string> Indice_Invertido::busca(string palavra) {
    return indice_[palavra];
}