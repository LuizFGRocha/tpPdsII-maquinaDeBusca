#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

/// @brief Exceção lançada quando o método pesquisa() identifica que a frase a
/// ser pesquisada não contém caracteres alfabéticos.
struct excecaoPesquisaVazia{};

class Indice_Invertido {

    public:

    /// @brief Constrói o índice invertido a partir dos documentos na pasta
    /// ./documentos. Cada palavra contida na pasta como um todo é associada
    /// a um conjunto formado pelos nomes dos documentos que a possuem.
    Indice_Invertido();
    
    /// @brief Busca os documentos em ./documentos que contenham dada palavra.
    /// @param palavra Palavra a ser procurada nos documentos.
    /// @return Retorna o conjunto de strings (set<string>) correspondentes aos
    /// nomes dos documentos que contêm as palavras.
    set<string> busca(string palavra);

    /// @brief Insere uma palavra e o arquivo que a pertence no índice. Para 
    /// finalidades de teste.
    /// @param palavra Palavra a ser inserida.
    /// @param documento Documento que contém a palavra.
    void inserir(string palavra, string documento);
    
    /// @brief Pesquisa a string fornecida.
    /// @param entrada String a ser pesquisada. Deve ter pelo menos uma palavra
    /// contendo pelo menos um caractere alfabético.
    /// @return Retorna um conjunto de strings contendo o nome dos documentos
    /// que contêm todas as palavras pesquisadas.
    set<string> pesquisa(string entrada); 

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

/// @brief Cria um conjunto responsável por armazenar os arquivos que
/// estejam associados às ocorrências das palavras pesquisadas. Exemplo de 
/// utilização nos testes.
/// @param setDocs Contém todos os arquivos associados a cada palavra pesquisada.
/// @param wordsAmount Quantidade total de palavras válidas pesquisadas.
set<string> intersecao(vector <string>& setDocs, int wordsAmount);
