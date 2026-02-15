//
// Created by Vanessza Tar on 29.04.2025.
//
#include "CSVBasketExporter.h"
#include <fstream>
#include <cstdlib>
#include "exceptions.h"

void CSVBasketExporter::exportBasket(const std::vector<TrenchCoat>& basket, const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw FileException("Could not open file");
    }
    fout << "Size, Colour, Price, Photograph\n";
    for (const auto& coat : basket) {
        fout << coat.getSize() << ","
             << coat.getColour() << ","
             << coat.getPrice() << ","
             << coat.getPhotograph() << "\n";
    }
    fout.close();
}

void CSVBasketExporter::openCSVInExcel(const std::string& filename) const{
    std::string command = "open " + filename;
    system(command.c_str());
}