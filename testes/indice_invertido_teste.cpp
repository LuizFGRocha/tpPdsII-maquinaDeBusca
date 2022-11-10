#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <set>

#include "indice_invertido.h"

TEST_CASE("string normalizar(string palavra)") {
    CHECK(normalizar("Aa??::;.;.;Ee---!!!!??-84875461") == "aaee");
    CHECK(normalizar("546876513213!!!!!!???????????.,.,;.,;.,;.,") == "");
}

TEST_CASE("set<string> busca(string palavra)") {
    Indice_Invertido google;

    google.inserir("cachorro", "Documento 1");
    google.inserir("cachorro", "Documento 2");
    google.inserir("cachorro", "Documento 3");

    google.inserir("pato", "Documento 2");
    google.inserir("pato", "Documento 3");
    google.inserir("pato", "Documento 4");

    google.inserir("raposa", "Documento 2");
    google.inserir("raposa", "Documento 4");
    google.inserir("raposa", "Documento 7");

    CHECK(google.busca("cachorro") == set<string>{"Documento 1", "Documento 2", "Documento 3"});
    CHECK(google.busca("pato") == set<string>{"Documento 2", "Documento 3", "Documento 4"});
    CHECK(google.busca("raposa") == set<string>{"Documento 2", "Documento 4", "Documento 7"}); 
}