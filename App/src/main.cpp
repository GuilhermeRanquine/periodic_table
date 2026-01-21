#include <iostream>
#include <vector>
#include "Tabela.hpp"

int main() {
    std::string caminho = "data/elementos.json";
    std::cout << "Tentando carregar: " << caminho << std::endl;

    try {
        auto elementos = LoadElements(caminho);
        showTable(elementos);
    } catch (const std::exception& ex) {
        std::cerr << "Erro: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}