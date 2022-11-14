#include "indice_invertido.h"
#include <filesystem>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

set<string> Indice_Invertido::busca(string palavra) {
    return indice_[normalizar(palavra)];
}

void Indice_Invertido::inserir(string palavra, string documento) {
    indice_[palavra].insert(documento);
}

void Indice_Invertido::constroiIndice(){
    const filesystem::path documentos{"./documentos"};
    string palavra;

    for (auto const& dir_entry : filesystem::directory_iterator{documentos}) {
        ifstream fin(dir_entry.path());
        while(fin >> palavra)
            inserir(normalizar(palavra), dir_entry.path().filename());
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