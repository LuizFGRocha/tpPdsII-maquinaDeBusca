#include <map>
#include <set>
#include <string>

using namespace std;

class Indice_Invertido {

    public:
    
    /// @brief Busca os documentos em ./documentos que contenham dada palavra.
    /// @param palavra Palavra a ser procurada nos documentos.
    /// @return Retorna o conjunto de strings (set<string>) correspondentes aos
    /// nomes dos documentos que contêm as palavras.
    set<string> busca(string palavra);

    /// @brief Insere uma palavra e o arquivo que a pertenceno índice. Para 
    /// finalidades de teste.
    /// @param palavra Palavra a ser inserida.
    /// @param documento Documento que contém a palavra.
    void inserir(string palavra, string documento);

    /// @brief Constrói o índice invertido a partir dos documentos na pasta
    /// ./documentos. Cada palavra contida na pasta como um todo é associada
    /// a um conjunto formado pelos nomes dos documentos que a possuem.
    void constroiIndice();

    private:
    
    /// @brief Mapeia cada palavra para o conjunto de arquivos
    /// que contêm essa palavra.
    map<string, set<string>> indice_;
};

/// @brief Normaliza uma palavra, i.e, tira os caracteres não alfabéticos e deixa
/// todos as letras minúsculas.
/// @param palavra Palavra a ser normalizada.
/// @return Retorna uma string composta estritamente por letras minúsculas.
string normalizar(string palavra);
   