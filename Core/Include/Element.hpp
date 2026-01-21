#pragma once
#include <string>
#include <vector>

struct Element
{
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
