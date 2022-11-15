#include "indice_invertido.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <utility>

using namespace std;

set<string> Indice_Invertido::busca(string palavra) {
    return indice_[normalizar(palavra)];
}

void Indice_Invertido::inserir(string palavra, string documento) {
    indice_[palavra].insert(documento);
}

void Indice_Invertido::constroiIndice(){
    try {
        const filesystem::path documentos{"./documentos"};
        string palavra;

        for (auto const& dir_entry : filesystem::directory_iterator{documentos}) {
            ifstream fin(dir_entry.path());
            while(fin >> palavra)
                inserir(normalizar(palavra), dir_entry.path().filename());
        }
    } catch (filesystem::filesystem_error e) {
        cout << "Exceção ao abrir e explorar a pasta \"./documentos\":   " << e.what() << endl;
        exit(1);
    } catch (ifstream::failure e) {
        cout << "Exceção ao ler arquivo:   " << e.what() << endl;
        exit(2);
    }
}

string normalizar(string palavra) {
    string comAcentoOuCedilha = "ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç";
    string semAcentoOuCedilha = "aaaaaaaaaaaeeeeeeeeiiiiiiiioooooooooouuuuuuucc";

    string normalizada;
    int index;
    for (auto itr = palavra.begin(); itr != palavra.end(); itr++) {
        if (index = comAcentoOuCedilha.find(*itr) != string::npos) {
            normalizada.push_back(semAcentoOuCedilha[index]);
            itr++;
        } else if (tolower(*itr) >= 97 && tolower(*itr) <= 122){
            normalizada.push_back(tolower(*itr));
        }
    }

    return normalizada;
}

set <string> intersecao(vector <string>& setDocs, int wordsAmount){
    map <string, int> docs;
    set <string> setIntersecao;
    try {
        for (auto const& arquivo : filesystem::directory_iterator{"./documentos"})
            docs.insert(pair <string, int> (arquivo.path().filename(), 0));
            
        for(auto value : setDocs){
            for(auto it = docs.begin(); it != docs.end(); it++){
                if(it->first == value){
                    it->second++;
                    break;
                }
            }
        }
    } catch (filesystem::filesystem_error e) {
        cout << "Exceção ao abrir e explorar a pasta \"./documentos\":   " << e.what() << endl;
        exit(1);
    }

    for(auto it = docs.begin(); it != docs.end(); it++){
        if(it->second == wordsAmount)
            setIntersecao.insert(it->first);
    }
    return setIntersecao;
}

set<string> Indice_Invertido::pesquisa(string entrada){
    int nPalavras = 0;
    vector<string> palavraSepara;
    istringstream tokenizer { entrada };
    //string vazia para ser usada na comparação
    string token;

    while (tokenizer >> token){
    token = normalizar(token);
    if(token.size() > 0){
        nPalavras++;
        palavraSepara.push_back(token);
    }
    }
    if (nPalavras == 0)
        throw excecaoPesquisaVazia{};
    
    vector<set<string>> vConjuntos;
    vector<string> vDocumentos;
    for(string s : palavraSepara){
        auto z = busca(s);
        vConjuntos.push_back(z);
    }
    for (set<string> conjunto : vConjuntos) {
        for (string palavra : conjunto) {
            vDocumentos.push_back(palavra);
        }
    }
    auto resultado = intersecao(vDocumentos, nPalavras);

    return resultado;
}
