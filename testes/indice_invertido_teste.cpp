#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <set>
#include <string>
#include <vector>

#include "indice_invertido.h"

TEST_CASE("string normalizar(string palavra)") {
    CHECK(normalizar("Aa??::;.;.;Ee---!!!!??-84875461") == "aaee");
    CHECK(normalizar("546876513213!!!!!!???????????.,.,;.,;.,;.,") == "");
    CHECK(normalizar("Guarda-Chuva") == "guardachuva");
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

// Este teste assume que na pasta onde o teste é executado há uma pasta ./documentos
// idêntica à que foi usada durante a sua implementação.
TEST_CASE("set<string> intersecao(vector <string>& setDocs, int wordsAmount)") {
    Indice_Invertido google;
    google.constroiIndice();


    vector<set<string>> vConjuntos;
    vConjuntos.push_back(google.busca("anyone"));
    vConjuntos.push_back(google.busca("USA"));
    vConjuntos.push_back(google.busca("map"));
    // Só o documento d9 possui as três palavras

    vector<string> vDocumentos;
    for (set<string> conjunto : vConjuntos) {
        for (string documento : conjunto) {
            vDocumentos.push_back(documento);
        }
    }

    auto resultado = intersecao(vDocumentos, 3);

    CHECK(resultado == set<string>{"d9.txt"});


    vConjuntos.clear();
    vConjuntos.push_back(google.busca("anyone")); // d9, d11, d12, d17, d18, d21, d26, d30
    vConjuntos.push_back(google.busca("know")); // d3, d5, d9, d11, d12, d15, d17, d21, d22, d24
    // A interseção dos conjuntos é d9, d11, d12, d17 e d21

    vDocumentos.clear();
    for (set<string> conjunto : vConjuntos) {
        for (string documento : conjunto) {
            vDocumentos.push_back(documento);
        }
    }

    resultado = intersecao(vDocumentos, 2);

    CHECK(resultado == set<string>{"d9.txt", "d11.txt", "d12.txt", "d17.txt", "d21.txt"});
}

TEST_CASE("set<string> Indice_Invertido::pesquisa(string entrada)"){
    Indice_Invertido google;
    google.constroiIndice(); 

    //Testa se o programa lança uma exceção no caso de não haver nenhum caractere válido para a pesquisa
    CHECK_THROWS(google.pesquisa("- ! 9 8 7"));

    //Testa se o programa consegue pesquisar uma palavra corretamente
    auto resultado = google.pesquisa("hello");
    CHECK(resultado == set<string>{"d18.txt", "d20.txt"});

    //Testa se o programa lida bem com uma pesquisa de várias palavras(com caracteres inválidos também)
    resultado = google.pesquisa("If the world's an oyster, why am I allergic to Mollusks");
    CHECK(resultado == set<string>{"d5.txt"});

    //Testa se a pesquisa de palavras diferentes, mas com mesma normalização, ocorre corretamente
    resultado = google.pesquisa("hello");
    auto resultado2 = google.pesquisa("HeLLo12345");
    CHECK(resultado == resultado2);
}