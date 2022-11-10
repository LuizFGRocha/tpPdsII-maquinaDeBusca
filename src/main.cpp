#include "indice_invertido.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    Indice_Invertido google;
    google.constroiIndice();
    auto resultados = google.busca("apartamento");
    for (string documento : resultados) {
        cout << documento << endl;
    }
    return 0;
}