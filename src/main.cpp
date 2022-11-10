#include <iostream>
#include "indice_invertido.h"

using namespace std;

int main() {
    if (normalizar("AaEe---!!!???12354") == "aaee") {
        cout << "Correto" << endl;
    }
    return 0;
}