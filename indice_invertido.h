#include <map>
#include <set>
#include <string>

using namespace std;

class Indice_Invertido {

    public:

    // TODO: inserir método para inserir no índice.

    /// @brief Busca os documentos em ./documentos que contenham dada palavra.
    /// @param palavra Palavra a ser procurada nos documentos.
    /// @return Retorna o conjunto de strings (set<string>) correspondentes aos
    /// nomes dos documentos que contêm as palavras.
    set<string> busca(string palavra);

    private:
    
    /// @brief Mapeia cada palavra para o conjunto de arquivos
    /// que contêm essa palavra.
    map<string, set<string>> indice_;
};