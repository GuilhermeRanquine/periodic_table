#pragma once

#include <vector>
#include <string>

struct Element {
    int number;
    std::string symbol;
    std::string name;
    double atomicMass;
    int group;
    int period;
    double density;
    double fusionPoint;
    double ebulitionPoint;
    double atomicRadius;
    double electronegativity;
    std::string eletronicConfiguration;
    std::string semanticConfiguration;
    std::vector<std::pair<int, double>> isotopes;
};

std::vector<Element> LoadElements(const std::string& filePath);

void showTable(const std::vector<Element>& elements);  // <- exato, sem const& no parâmetro aqui? Não, deve ter!