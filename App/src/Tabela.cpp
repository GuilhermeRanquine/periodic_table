#include "tabela.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>
#include <format>

using json = nlohmann::json;

std::vector<Element> LoadElements(const std::string& file) {
    std::vector<Element> elements; // empty vector to store the loaded elements
    std::ifstream f(file);
    if (!f.is_open()) {
        throw std::runtime_error("Could not open file: " + file);
    }
    json j = json::parse(f);
    for (auto& el : j) {
        Element element;
        element.number = el["number"].get<int>();
        element.symbol = el["symbol"].get<std::string>();
        element.name = el["name"].get<std::string>();
        element.atomicMass = el["atomicMass"].get<double>();
        element.group = el["group"].get<int>();
        element.period = el["period"].get<int>();
        element.density = el["density"].get<double>();
        element.fusionPoint = el["fusionPoint"].get<double>();
        element.ebulitionPoint = el["ebulitionPoint"].get<double>();
        element.atomicRadius = el["atomicRadius"].get<double>();
        element.electronegativity = el["electronegativity"].get<double>();
        element.eletronicConfiguration = el["eletronicConfiguration"].get<std::string>();
        element.semanticConfiguration = el["semanticConfiguration"].get<std::string>();
        for (auto& iso : el["isotopes"]) {
            int massNumber = iso["massNumber"].get<int>();
            double abundance = iso["abundance"].get<double>();
            element.isotopes.emplace_back(massNumber, abundance);
        }
        elements.push_back(element);

        for (auto& iso : el ["isotopes"]) {
            int mass = iso["massNumber"].get<double>();
            double abundance = iso["abundance"].get<double>();
            element.isotopes.push_back({mass, abundance});
         }
         elements.push_back(element);
    }
    return elements;
}