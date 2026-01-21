#include <iostream>
#include <vector>
#include "Tabela.hpp"

int main() {
    try {
        auto elements = LoadElements("data/elementos.json");
        showTable(elements);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}