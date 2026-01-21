#include "tabela.hpp"
#include <fstream>
#include "third_party/json.hpp"
#include <iostream>
#include <stdexcept>
#include <format>

using json = nlohmann::json;

std::vector<Element> LoadElements(const std::string& file) {
    std::vector<Element> elements;
    std::ifstream f(file);
    if (!f.is_open()) {
        throw std::runtime_error("Could not open file: " + file);
    }

    json j = json::parse(f);

    std::cout << "JSON parseado com sucesso. Primeiro elemento:\n"
          << j[0].dump(2) << std::endl;

    for (auto& el : j) {
        Element element;

        element.number              = el["numero"].get<int>();
        element.symbol              = el["simbolo"].get<std::string>();
        element.name                = el["nome"].get<std::string>();
        element.atomicMass          = el["massa"].get<double>();
        element.group               = el["grupo"].get<int>();
        element.period              = el["periodo"].get<int>();
        element.density             = el["densidade"].get<double>();
        element.fusionPoint         = el["pontoFusao"].get<double>();
        element.ebulitionPoint      = el["pontoEbulicao"].get<double>();
        element.atomicRadius        = el["raioAtomico"].get<double>();
        element.electronegativity   = el["eletronegatividade"].get<double>();
        element.eletronicConfiguration = el["configuracaoEletronica"].get<std::string>();
        element.semanticConfiguration  = el["configuracaoSemantica"].get<std::string>();

        // Isótopos – só um loop!
        if (el.contains("isotopos") && el["isotopos"].is_array()) {
            for (auto& iso : el["isotopos"]) {
                int massNumber = iso["massa"].get<int>();          // chave correta
                double abundance = iso["abundancia"].get<double>();
                element.isotopes.emplace_back(massNumber, abundance);
            }
        }

        elements.push_back(element);
    }

    return elements;
}

void showTable(const std::vector<Element>& elements) {
    std::cout << "\n=== Simple Periodic Table of Elements ===\n";
    std::cout << std::left;
    std::cout << std::format("{:>3} {:<3} {:12} {:>8}\n",
                             "No", "Sym", "Name", "Atomic Mass");
    std::cout << "-----------------------------------------------\n";

    for (const auto& e : elements) {
        std::cout << std::format("{:>3}  {:<3}  {:<12}  {:>8.3f}\n",
                                 e.number,
                                 e.symbol,
                                 e.name,
                                 e.atomicMass);
    }

    std::cout << "--------------------------------------------------\n";
    std::cout << "Total de elementos carregados: " << elements.size() << "\n\n";
}