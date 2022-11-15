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
                inserir(normalizar(palavra), dir_entry.path().filename().string());
        }
    } catch (filesystem::filesystem_error e) {
        cerr << "Exceção ao abrir e explorar a pasta \"./documentos\":   " << e.what() << endl;
        exit(1);
    } catch (ifstream::failure e) {
        cerr << "Exceção ao ler arquivo:   " << e.what() << endl;
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
            docs.insert(pair <string, int> (arquivo.path().filename().string(), 0));
            
        for(auto value : setDocs){
            for(auto it = docs.begin(); it != docs.end(); it++){
                if(it->first == value){
                    it->second++;
                    break;
                }
            }
        }
    } catch (filesystem::filesystem_error e) {
        cerr << "Exceção ao abrir e explorar a pasta \"./documentos\":   " << e.what() << endl;
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
    //String vazia para ser usada na comparação
    string aux;
    //Separa a frase em palavras e insere no vetor palavraSepara
    while (tokenizer >> aux){
    aux = normalizar(aux);
    if(aux.size() > 0){
        nPalavras++;
        palavraSepara.push_back(aux);
    }
    }
    //Se não há palavras válidas, lança uma exceção
    if (nPalavras == 0)
        throw excecaoPesquisaVazia{};
    
    vector<set<string>> vConjuntos;
    vector<string> vDocumentos;
    //Para cada palavra do vetor, busca seu índice invertido
    for(string palavraChave : palavraSepara){
        auto indiceChave = busca(palavraChave);
        vConjuntos.push_back(indiceChave);
    }
    for (set<string> conjunto : vConjuntos) {
        for (string palavra : conjunto) {
            vDocumentos.push_back(palavra);
        }
    }
    //O resultado são todos os documentos que possuem todas as palavras pesquisadas
    auto resultado = intersecao(vDocumentos, nPalavras);

    return resultado;
}
