#pragma once
#include <vector>
#include <string>
#include "Element.hpp"
// Funções para manipulação da tabela periódica
std::vector<Element> LoadElements(const std::string& file); // carrega os elementos de um arquivo
void showTable(const std::vector<Element>& elements); // mostra a tabela periódica
Element findNumber(const std::vector<Element>& elements, int num); // encontra um elemento pelo número atômico
void showDetailsElement(const Element& e); //para mostrar os detalhes do elemento
void viewOrbitals(const Element& e); // para mostrar os orbitais do elemento
void mainMenu(std::vector<Element>& elements); // menu principal