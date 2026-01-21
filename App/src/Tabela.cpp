#include "tabela.hpp"
#include <fstream>
#include <iostream>
#include <format>
#include <vector>

#include <third_party/json.hpp>  // Assumindo que está no include path; ajuste se for "third_party/json.hpp"

std::vector<Element> LoadElements(const std::string& filePath) {
    std::vector<Element> elements;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    nlohmann::json data = nlohmann::json::parse(file);  // Parsing explícito, mais robusto

    if (!data.is_array()) {
        throw std::runtime_error("Invalid JSON format: root must be an array");
    }

    for (const auto& item : data) {
        if (!item.is_object()) continue;

        Element elem;
        elem.number = item.value("number", 0);
        elem.symbol = item.value("symbol", "");
        elem.name = item.value("name", "");
        elem.atomicMass = item.value("atomicMass", 0.0);
        elem.group = item.value("group", 0);
        elem.period = item.value("period", 0);
        elem.density = item.value("density", 0.0);
        elem.fusionPoint = item.value("fusionPoint", 0.0);
        elem.ebulitionPoint = item.value("ebulitionPoint", 0.0);
        elem.atomicRadius = item.value("atomicRadius", 0.0);
        elem.electronegativity = item.value("electronegativity", 0.0);
        elem.eletronicConfiguration = item.value("eletronicConfiguration", "");
        elem.semanticConfiguration = item.value("semanticConfiguration", "");

        if (item.contains("isotopes") && item["isotopes"].is_array()) {
            for (const auto& iso : item["isotopes"]) {
                if (iso.is_object()) {
                    int massNum = iso.value("massNumber", 0);
                    double abund = iso.value("abundance", 0.0);
                    elem.isotopes.emplace_back(massNum, abund);
                }
            }
        }

        elements.push_back(std::move(elem));
    }

    return elements;
}

void showTable(const std::vector<Element>& elements) {
    if (elements.empty()) {
        std::cout << "No elements loaded.\n";
        return;
    }

    constexpr int COL_NO = 4;
    constexpr int COL_SYM = 5;
    constexpr int COL_NAME = 15;
    constexpr int COL_MASS = 12;

    std::cout << "\n=== Periodic Table ===\n\n";
    std::cout << std::format("{:>{}}  {:<{}}  {:<{}}  {:>{}}\n",
                             "No", COL_NO, "Sym", COL_SYM, "Name", COL_NAME, "Atomic Mass", COL_MASS);
    std::cout << std::string(COL_NO + COL_SYM + COL_NAME + COL_MASS + 3 * 2, '-') << '\n';  // Ajuste de separador

    for (const auto& e : elements) {
        std::cout << std::format("{:>{}}  {:<{}}  {:<{}}  {:>{}.3f}\n",
                                 e.number, COL_NO, e.symbol, COL_SYM, e.name, COL_NAME, e.atomicMass, COL_MASS);
    }

    std::cout << std::string(COL_NO + COL_SYM + COL_NAME + COL_MASS + 3 * 2, '-') << '\n';
    std::cout << "Total elements: " << elements.size() << "\n\n";
}